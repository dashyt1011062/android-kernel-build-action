# Android Kernel Build Action v2

This action builds Android ACK ARM64 external kernel modules with `dddk`. It no longer synchronizes or builds a complete Android kernel tree.

## Inputs

| Input | Required | Default | Description |
|---|---|---|---|
| `tag` | Yes | `android13-5.15` | Droid DDK kernel target |
| `arch` | Yes | `aarch64` | Preserved v1 input; accepts `aarch64` or `arm64` |
| `module-path` | Yes | None | Name of the module source artifact uploaded by an earlier job |
| `module-name` | Yes | None | Module directory, `.c` file, and `.ko` file name |

Supported `tag` values are `android13-5.15`, `android14-5.15`, `android14-6.1`, `android15-6.1`, `android15-6.6`, `android16-6.6`, `android16-6.12`, `android17-6.12`, and `android17-6.18`.

The extracted module artifact must have this layout:

```text
MODULE_NAME/
|-- Makefile
`-- MODULE_NAME.c
```

## Usage

```yaml
jobs:
  upload-module:
    runs-on: ubuntu-24.04
    steps:
      - uses: actions/checkout@v6
      - uses: actions/upload-artifact@v7
        with:
          name: hello-ko
          path: path/to/hello-ko

  build-module:
    needs: upload-module
    runs-on: ubuntu-24.04
    steps:
      - uses: feicong/android-kernel-build-action@v2
        with:
          tag: android17-6.18
          arch: aarch64
          module-path: hello-ko
          module-name: hello-ko
```

The original artifact naming is preserved: `Image-TAG-ARCH` contains `TAG_MODULE_NAME.ko`.

## License

[GPL-3.0-or-later](LICENSE)
