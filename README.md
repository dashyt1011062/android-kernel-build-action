# Android Kernel Build Action v2

该Action使用`dddk`镜像编译Android ACK ARM64外部内核模块，不再同步和编译整套Android内核源码。

## 输入

| 参数 | 必填 | 默认值 | 说明 |
|---|---|---|---|
| `tag` | 是 | `android13-5.15` | `dddk`内核目标 |
| `arch` | 是 | `aarch64` | 保留原参数，接受`aarch64`或`arm64` |
| `module-path` | 是 | 无 | 上游上传的模块源码artifact名称 |
| `module-name` | 是 | 无 | 模块目录名、`.c`文件名和`.ko`文件名 |

支持的`tag`：`android13-5.15`、`android14-5.15`、`android14-6.1`、`android15-6.1`、`android15-6.6`、`android16-6.6`、`android16-6.12`、`android17-6.12`、`android17-6.18`。

模块artifact解压后必须包含：

```text
MODULE_NAME/
├── Makefile
└── MODULE_NAME.c
```

## 使用

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

产物沿用原命名：artifact为`Image-TAG-ARCH`，其中包含`TAG_MODULE_NAME.ko`。

## License

[GPL-3.0-or-later](LICENSE)
