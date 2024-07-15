# ch32x035


An open source development environment (tooling, headers, examples) for the [CH32x035](https://www.wch-ic.com/products/CH32X035.html). All the examples are taken from [openwch/ch32x035](https://github.com/openwch/ch32x035)


## Getting Started

### GCC

These examples uses the customised  [MRS_Toolchain](http://file-oss.mounriver.com/tools/MRS_Toolchain_Linux_x64_V1.91.tar.xz) gcc compiler which supports customized hardware stacking function,

```
 __attribute__((interrupt("WCH-Interrupt-fast"))).
```
This statement tells GCC to perform a hardware push operation.

### Build

```
cd examples/gpio
make
make flash
```

## FLASHING

The elf can be flashed to the CH32X035 using [wchisp](https://github.com/ch32-rs/wchisp). (Enter the CH32X035 bootloader by holding down BOOT when connecting it using USB).\
The SDK for CH32X035 from the openwch EVT is vendored under ``sdk/``. (Encoding has been changed from gbk to utf-8). 

### Footnotes/links

https://www.wch-ic.com/products/CH32X035.html
https://github.com/openwch/chch32x035592
https://www.wch.cn/downloads/CH32X035RM_PDF.html
https://www.wch.cn/downloads/CH32X035DS0_PDF.html
http://www.wch-ic.com/downloads/QingKeV4_Processor_Manual_PDF.html