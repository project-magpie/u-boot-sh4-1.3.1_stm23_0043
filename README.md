# Loading U-Boot via ST40 SH4 GDB

Turn off your box with the switch on the back. Connect your STB via serial line to a Terminal Emulater like minicom and start minicom.
You may test your minicom set-up with the original bootloader first.

##Start sh4-gdb
    export LD_LIBRARY_PATH=/opt/STM/STMCR1.6.0/lib:/opt/STM/ST40R5.1.0/lib
    export PATH=/opt/STM/ST40R5.1.0/bin:/opt/STM/STMCR1.6.0/bin:$PATH
    $ killall -9 sh4gdb sh4sdistmclite
    $ sh4gdb

After gdb has started and the box is turned on:

    (gdb) sh4tp STMCLT1000_A:sat7111:st40,debug=2
    (gdb) load /data/src/u-boot-sh4-1.3.1_stm23_0043/u-boot
    (gdb) continue

**ATTENTION:** On linux the _STMCLT1000\_A_ is needed instead of the _STMCLT1000A_ on Windows. My primary plattform is linux so
you will mostly read _STMCLT1000\_A_.

Here is a full session log:

    (gdb) sh4tp STMCLT1000_A:sat7111:st40,debug=2
    The target is assumed to be little endian
    The target architecture is assumed to be sh4
    sat7111 connect start - parameters {'debug': '2'}
    Initialization TCK frequency set to 3000000 Hz
    Device id  0x2d43b041
    tapmux connect(): boot mode single core setup
    tapmux setup to bypass to core st40, channel 1
    sat7111 initialization start ...
    sat7111_setup - parameters {'debug': '2', 'tapmux_bypass_init': u'st40', 'reset_low_period': 360000}
    Chip infos
      Device ID = 0x2D43B041 ==> STi7111 cut 3.0
      Mode pins = 0x00003928 ==> [1:0] ClockgenA ref: SYSA_CLKIN/FE OSC
                                 [10:9] Boot mode . : ST40 first
                                 [17:16] Boot device: NOR flash
                                 [14] Boot port size: 16-bits
                                 [11] Nand page size: 2048 bytes
    Clock frequencies
      CKGA_PLL0 HS/LS = 900.0/450.0 MHz
      CKGA_PLL1       = 800.0 MHz
      ST40 ICK        = 450.0 MHz
      LX DMU          = 450.0 MHz
      LX AUD          = 450.0 MHz
      FDMA0           = 400.0 MHz
      FDMA1           = 400.0 MHz
      STNOC           = 400.0 MHz
      IC_BDISP_200    = 200.0 MHz
      IC_DISP_200     = 200.0 MHz
      IC_TS_200       = 200.0 MHz
      IC_COMPO_200    = 200.0 MHz
      IC_IF_200       = 200.0 MHz
      IC_IF_100       = 100.0 MHz
      DISP_PIPE_200   = 200.0 MHz
      BLIT_PROC       = 266.7 MHz
      IC_DELTA_200    = 266.7 MHz
      ETHERNET        = 25.0 MHz
      PCI             = 66.7 MHz
      EMI MASTER      = 100.0 MHz
      LMI2X           = 800.0 MHz
    Info: correcting interco reset setup
    chip_init complete
    stx7111: booted video companion
    stx7111: booted audio companion
    TCK frequency set to 10000000 Hz
    tapmux complete_connect(): single core setup
    sat7111 initialization complete
    0xa0000000 in ?? ()
    (gdb)
    (gdb) load /data/src/u-boot-sh4-1.3.1_stm23_0043/u-boot
    Loading section .text, size 0x26ec0 lma 0x93f00000
    Loading section .text.unlikely, size 0x18 lma 0x93f26ec0
    Loading section .rodata, size 0x1298 lma 0x93f26ed8
    Loading section .rodata.str1.4, size 0x9ef0 lma 0x93f28170
    Loading section .data, size 0x2038 lma 0x93f32060
    Loading section .u_boot_cmd, size 0x6d8 lma 0x93f34098
    Start address 0x93f00000, load size 214896
    Transfer rate: 235 KB/sec, 35816 bytes/write.
    (gdb) continue
    Continuing.




## On the minicom console

Your serial Port have to use the following setting:

- Baudrate    :  115200 Baud
- Data        :       8 Bit
- Parity      :    none
- Flow Control:    none

```
Board: STx7111-Mboard (MB618)  [29-bit mode]
info: Disregarding any EPLD


U-Boot 1.3.1-g13a70f75-dirty (Jun 28 2014 - 17:12:16) - stm23_0099 - YW 1.0.023 Rel

DRAM:  128 MiB
NOR:     8 MiB
In:    serial
Out:   serial
Err:   serial
IdentID : 09 00 07 00 00 46 d1
Hit ESC to stop autoboot:  0
```

# Reloading a new image

During development it may will become usefull to load a u-boot and make some test recompile some stuff and reload this new binary. You can interrut your GDB session by pressing **CTRL-C** loading the new image and write continue in the console. This will load the new u-boot into RAM and executes this new image. This is nice during development of new u-boot features.

# Building under Yocto

Before you can start building with SH4 Toolchain generated for Yocto you may apply this Patch

``` diff
diff --git a/Makefile b/Makefile
index c70d0b0..d406e09 100755
--- a/Makefile
+++ b/Makefile
@@ -258,7 +258,8 @@ LIBS := $(addprefix $(obj),$(LIBS))
 .PHONY : $(LIBS)

 # Add GCC lib
-PLATFORM_LIBS += -L $(shell dirname `$(CC) $(CFLAGS) -print-libgcc-file-name`) -lgcc
+#PLATFORM_LIBS += -L $(shell dirname `$(CC) $(CFLAGS) -print-libgcc-file-name`) -lgcc
+PLATFORM_LIBS += -L /opt/poky/1.5.1/sysroots/sh4-poky-linux/usr/lib/sh4-poky-linux/4.7.2 -lgcc

 # The "tools" are needed early, so put this first
 # Don't include stuff already done in $(LIBS)
diff --git a/cpu/sh/config.mk b/cpu/sh/config.mk
index 5cc8f25..6896faa 100755
--- a/cpu/sh/config.mk
+++ b/cpu/sh/config.mk
@@ -21,4 +21,4 @@
 # MA 02111-1307 USA
 #

-PLATFORM_CPPFLAGS += -m4 -m4-nofpu -U__sh3__
+PLATFORM_CPPFLAGS += -m4 -U__sh3__
diff --git a/include/configs/mb618.h b/include/configs/mb618.h
index cd4399a..ea26760 100755
--- a/include/configs/mb618.h
+++ b/include/configs/mb618.h
@@ -363,7 +363,7 @@
 #define CFG_HZ			(P_CLOCK_RATE/1024) /* HZ for timer ticks	*/
 #define CFG_LOAD_ADDR		CFG_SDRAM_BASE	/* default load address		*/
 #define CFG_BOOTMAPSZ		(16 << 20)	/* initial linux memory size	*/
-#define CONFIG_BOOTDELAY	3//10		/* default delay before executing bootcmd */
+#define CONFIG_BOOTDELAY	10		/* default delay before executing bootcmd */
 #define CONFIG_ZERO_BOOTDELAY_CHECK

 #define CONFIG_CMDLINE_EDITING
diff --git a/sh_config.mk b/sh_config.mk
index b77a8e8..545e8f0 100755
--- a/sh_config.mk
+++ b/sh_config.mk
@@ -27,7 +27,7 @@
 # for actual build number, in the following identifier.
 # Regular Expression for string is:
 # 	"stm[2-9][0-9]-[2-9][0-9][0-9][0-9]-[01][0-9]-[0-3][0-9]"
-SH_IDENT_STRING="\"stm23_0043\""
+SH_IDENT_STRING="\"stm23_0099\""

 PLATFORM_CPPFLAGS += -DCONFIG_SH4 -D__SH4__ -DCONFIG_IDENT_STRING=$(SH_IDENT_STRING)
 PLATFORM_LDFLAGS  += -n
```

# Compilation with Yocto/OE Toolchain

The u-boot source can be compiled in this way with the yocto toolchain:

```bash
$ source /opt/poky/1.5.1/environment-setup-sh4-poky-linux
# For  more details on this please read:
# http://www.denx.de/wiki/view/ELDK-5/FrequentlyAskedQuestionsAndAnswers#Compiling_U_Boot_or_Linux_fails
$ unset LDFLAGS
$ export CROSS_COMPILE=sh4-poky-linux-
$ make distclean
$ make mb618_config
$ make
```
# 29 Bit vs. 32 Bit Adress Mode

The SH40-300 core used in the Fulan Spark 71xx Receivers provide by default the 29 Bit Adress mode. Within this mode 512MB of Memory can be addressed.

    2^29 = 512 MB

But they also provide the 32 Bit space enhanced mode (SE). To load a u-boot compiled for SE mode you also have to use the GDB SE config flag:

     sh4tp STMCLT1000_A:sat7111:st40,debug=2,se=1

To compile your binary in 32 Bit SE mode you have to run the following command for activating

```bash
$ source /opt/poky/1.5.1/environment-setup-sh4-poky-linux
# For  more details on this please read:
# http://www.denx.de/wiki/view/ELDK-5/FrequentlyAskedQuestionsAndAnswers#Compiling_U_Boot_or_Linux_fails
$ unset LDFLAGS
$ export CROSS_COMPILE=sh4-poky-linux-
$ make distclean
$ make mb618se_config
$ make
```

I hope you have noticed the lower-case **se** at config stage. As a result you can see the output of the loaded u-Boot also tells you that you are using 32 Bit mode.

```
Board: STx7111-Mboard (MB618)  [32-bit mode]
info: Disregarding any EPLD


U-Boot 1.3.1-gda1a2b22-dirty (Jun 30 2014 - 17:36:41) - stm23_0099 - YW 1.0.023 Rel

DRAM:  128 MiB
NOR:     8 MiB
NAND:  512 MiB
In:    serial
Out:   serial
Err:   serial
IdentID : 09 00 07 00 00 46 d1
STB     : GoldenMedia GM990
Hit ESC to stop autoboot:  0
MB618>
```

If you are using your version of u-boot only for reflashing your bricket STB with the original one it should make no difference if you are using 29Bit or 32Bit one. But if you want to write it onto flash you should use 32 Bit one.

Because there is a [check](https://github.com/project-magpie/u-boot-sh4-1.3.1_stm23_0043/blob/master/lib_sh/sh_linux.c) wether the Linux Kernel is compiled for 29 Bit or 32Bit.

```C

  /* try and detect if the kernel is incompatible with U-boot */
  if ((*SE_MODE & 0xFFFFFF00) != 0x53453F00)  /* 'SE?.' */
  {
    printf("\nWarning: Unable to determine if kernel is built for 29- or 32-bit mode!\n");
  }
  else if ((*SE_MODE & 0xFF) != CURRENT_SE_MODE)
  {
    printf("\n"
      "Error: A %2u-bit Kernel is incompatible with this %2u-bit U-Boot!\n"
      "Please re-configure and re-build vmlinux or u-boot.\n"
      "Aborting the Boot process - Boot FAILED.  (SE_MODE=0x%08x)\n",
      CURRENT_SE_MODE ^ (32 ^ 29),
      CURRENT_SE_MODE,
      *SE_MODE);
    return;
  }
  ```

