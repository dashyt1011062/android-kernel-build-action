# Build a tiny module with KCFI enabled even when the stock DDK config omits it.
ccflags-y += -fsanitize=kcfi
ccflags-y += -Wno-error=unused-command-line-argument

obj-m += hello-ko-kcfi.o
