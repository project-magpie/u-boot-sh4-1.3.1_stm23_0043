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
