# Post Reboot Analysis: hello-ko load panic

Date: 2026-07-30

## Device

- `uname -a`: `Linux localhost 6.6.66-android15-8-g29d86c5fc9dd-abogki428889875-4k #1 SMP PREEMPT Wed Jul 29 01:13:16 CST 2026 aarch64 Android`
- Boot reason after reboot:
  - `sys.boot.reason`: `kernel_panic,ooas_`
  - `ro.boot.bootreason`: `kernel_panic,ooas_`
- Saved evidence:
  - `artifacts/panic-after-reboot/console-ramoops-0.bin`
  - `artifacts/panic-after-reboot/proc-config.gz`

## Built artifact

- GitHub Actions run: `https://github.com/dashyt1011062/android-kernel-build-action/actions/runs/30535435610`
- Local artifact: `artifacts/run-30535435610/Image-android15-6.6-aarch64/android15-6.6_hello-ko.ko`
- `modinfo`:
  - `name`: `hello_ko`
  - `vermagic`: `6.6.142-4k-g72d9552a905a-dirty SMP preempt mod_unload modversions aarch64`
- Compiler comment:
  - `Android (9352603, based on r450784d1) clang version 14.0.7`

## Panic evidence

`console-ramoops-0` contains a CFI panic during module init:

- `CFI failure at do_init_module+0xd4/0x360`
- target: `init_module+0x0 [hello_ko]`
- expected type includes `0x36b1c5a6`
- `Kernel panic - not syncing: OOAs CFI Fatal exception`
- task in the dump was `insmod`

This means the module reached the init path, but the kernel's CFI check rejected the module init function entry.

## Local kernel config signals

From `/proc/config.gz`:

- `CONFIG_CFI_CLANG=y`
- `# CONFIG_CFI_PERMISSIVE is not set`
- `CONFIG_LTO_NONE=y`
- `CONFIG_MODVERSIONS=y`
- `CONFIG_MODULE_SIG=y`
- `# CONFIG_MODULE_SIG_FORCE is not set`
- `CONFIG_KPROBES=y`
- `CONFIG_KPROBE_EVENTS=y`
- `CONFIG_HAVE_HW_BREAKPOINT=y`
- `CONFIG_PERF_EVENTS=y`

## Vendor module comparison

Example vendor module:

- `/vendor_dlkm/lib/modules/test-kit.ko`
- compiler comment: `Android (11368308, +pgo, +bolt, +lto, +mlgo, based on r510928) clang version 18.0.0`
- `init_module` symbol starts at offset `0x4`, with the 32-bit CFI type word at `.init.text+0x0`.

The generated `hello_ko` has `init_module` at offset `0x0` and no matching CFI type word before it. That matches the CFI panic: `do_init_module` checks the word before the target function pointer and panics when it does not match.

## Conclusion

The current `feicong/android-kernel-build-action` stock `android15-6.6` target can produce a `.ko`, but this artifact is not safe to load on this device. It is built against a different ACK kernel/toolchain and lacks the CFI entry layout expected by this kernel.

The next build attempt should use this device's kernel config and a matching Android clang 18/r510928 toolchain, with `CONFIG_CFI_CLANG` module CFI enabled so `init_module` has the expected type word at `function - 4`.
