/*
 * (C) Copyright 2004 STMicroelectronics.
 *
 * Andy Sturges <andy.sturges@st.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */

#define CONFIG_SH4	1		/* This is an SH4 CPU		*/
#define CONFIG_CPU_SUBTYPE_SH4_2XX	/* its an SH4-202		*/

#ifndef INPUT_CLOCK_RATE
#warning Assuming 30MHz clock input
#define INPUT_CLOCK_RATE 30
#endif

//for update define something ,for details to look at cmd_update.c
//2008-03-07 LinFan Add for bootmenu
#define CONFIG_MENUKEY ' '

// YWDRIVER_MODI sqy 2008/12/2 begin 
//  zww 2009/3/24 begin 
#define START_UPDATE_CHAR 1         //SOH
#define BOOT_UPDATE_CHAR 17         //DC1
#define KERNEL_UPDATE_CHAR 18      //DC2
#define FS_UPDATE_CHAR 19              //DC3
#define ALL_UPDATE_CHAR 20             //DC4 
#define FINISH_UPDATE_CHAR 24       //CAN
//#define READY_UPDATE_CHAR 26
#define FAIL_UPDATE_CHAR 27            //ESC
//  zww 2009/3/24 end

#define P_CLOCK_RATE	66000000	/* clock rate for CSP		*/

/*-----------------------------------------------------------------------
 * Start addresses for the final memory configuration
 * Assume we run out of uncached memory for the moment
 */

#ifdef CONFIG_SH_SE_MODE
#define CFG_FLASH_BASE		0xA0000000	/* FLASH (uncached) via PMB */
#define CFG_SDRAM_BASE		0x80000000      /* LMI-Sys via PMB */
#define CFG_SE_PHYSICAL_BASE	0x40000000	/* LMI-Sys Physical Address */
#define CFG_SE_UNACHED_BASE	0x90000000	/* LMI-Sys un-cached addr via PMB */
#define CFG_SE_SDRAM_WINDOW	(CFG_SDRAM_SIZE-1)
#else
#define CFG_FLASH_BASE		0xA0000000	/* FLASH in P2 region */
#define CFG_SDRAM_BASE		0x84000000      /* SDRAM in P1 region */
#endif

#define CFG_SDRAM_SIZE		0x08000000	/* 64 MiB of LMI-Sys SDRAM */

#define CFG_MONITOR_LEN		0x00040000	/* Reserve 128 / 256 KiB for Monitor */
#define CFG_MONITOR_BASE        CFG_FLASH_BASE
#define CFG_MALLOC_LEN		(1 << 23)	/* Reserve 1 MiB for malloc */
#define CFG_BOOTPARAMS_LEN	(128 << 10)
#define CFG_GBL_DATA_SIZE	1024		/* Global data structures */

#define CFG_MEMTEST_START	CFG_SDRAM_BASE
#define CFG_MEMTEST_END		(CFG_SDRAM_BASE + CFG_SDRAM_SIZE - (3 << 20))

#define CONFIG_BAUDRATE		115200
#define CFG_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define XSTR(s) STR(s)
#define STR(s) #s

#define BOARD mb442

//YWDRIVER_MODI d48zm 2010/3/24 modify
#if CFG_MONITOR_LEN == 0x00020000		/* 128 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa001ffff"		
#elif CFG_MONITOR_LEN == 0x00040000		/* 256 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa003ffff"		
#else						/* unknown */
#	error "Unable to determine sectors for monitor"
#endif
//YWDRIVER_MODI d48zm 2010/3/24 modify end

#ifdef 	CONFIG_SH_SE_MODE
#define CFG_KERNEL_START 0x80000000
#else
#define CFG_KERNEL_START 0xa0060000
#endif
#define CONFIG_EXTRA_ENV_SETTINGS \
		"board=" XSTR(BOARD) "_" XSTR(INPUT_CLOCK_RATE) "\0" \
		"monitor_base=" XSTR(CFG_MONITOR_BASE) "\0" \
		"monitor_len=" XSTR(CFG_MONITOR_LEN) "\0" \
		"monitor_sec=" MONITOR_SECTORS "\0" \
		"load_addr=" XSTR(CFG_LOAD_ADDR) "\0" \
        "unprot=" \
		"protect off $monitor_sec\0" \
        "update=" \
 		"erase $monitor_sec;" \
		"cp.b $load_addr $monitor_base $monitor_len;"\
		"protect on $monitor_sec\0" \
		"HOSTNAME=LINUX7109\0" \
		"ethaddr=00:80:E1:12:06:38\0" \
		"ipaddr=192.168.3.38\0" \
		"netmask=255.255.255.0\0" \
		"gatewayip=192.168.3.1\0" \
		"serverip=192.168.3.120\0" \
		"bootcmd=bootm $kernel_base\0" \
        "kernel_base=a0060000\0" \
        "kernel_sec=a0060000 a05fffff\0" \
        "rootfs_base=a0600000\0" \
        "rootfs_sec=a0600000 a07fffff\0" \
		"menucmd=update\0" \
		"kernel_name=mImage\0" \
		"kernelnfspath=192.168.3.119:/opt/STM/STLinux-2.3/devkit/sh4/target/root\0" \
		"rootfs_name=UserFS\0" \
		"rootfsnfspath=192.168.3.119:/opt/STM/STLinux-2.3/devkit/sh4/target/root\0" \
		"uboot_name=u-boot.bin\0" \
		"ubootnfspath=192.168.3.120:/home/d22cj/workspace/target\0" \
		"bootfromnfs=nfs a4000000 $kernelnfspath/$kernel_name;bootm a4000000\0" \
		"bootargs_nfs=console=ttyAS0,115200 nwhwconf=device:eth0,hwaddr:00:80:E1:12:06:45 " \
		"stmmaceth=msglvl:0,phyaddr:2,watchdog:5000 root=/dev/nfs nfsroot=" \
		"192.168.3.119:/opt/STM/STLinux-2.3/devkit/sh4/target,nfsvers=2,rsize=4096," \
		"wsize=8192,tcp rw ip=192.168.3.45:192.168.3.119:192.168.3.1:255.255.255.0:" \
		"LINUX7109:eth0:off bigphysarea=200 mem=48m\0" \
		"bootargs_flash=console=ttyAS0,115200 rw ramdisk_size=5120 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:06:45 ip=192.168.3.45" \
		":192.168.3.119:192.168.3.1:255.255.255.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:2," \
		"watchdog:5000 bigphysarea=200 mem=48m\0" \
		"bootargs=console=ttyAS0,115200 rw ramdisk_size=5120 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:06:45 ip=192.168.3.45" \
		":192.168.3.119:192.168.3.1:255.255.255.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:2," \
		"watchdog:5000 bigphysarea=200 mem=48m\0" 

        
/*--------------------------------------------------------------
 * Command line configuration.
 */

#include <config_cmd_default.h>

//#define CONFIG_CMD_DFL
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_NFS
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_IDE
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_UPDATE
//#define CONFIG_CMD_NAND

/*--------------------------------------------------------------
 * Serial console info
 */

/*
 * We can use one of two methods for the "serial" console.
 * We can either use the (normal hardware) internal ST ASC UART;
 * OR we can use STMicroelectronics' DTF (Data Transfer Format)
 * mechanism over a JTAG link to a remote GDB debugger.
 */
#if 1
#	define CONFIG_STM_ASC_SERIAL	/* use a ST ASC UART */
#else
#	define CONFIG_STM_DTF_SERIAL	/* use DTF over JTAG */
#endif

/* choose which ST ASC UART to use */
#if 1
#	define CFG_STM_ASC_BASE		0xb8032000ul	/* UART2 */
#else
#	define CFG_STM_ASC_BASE		0xb8033000ul	/* UART3 */
#endif

/*---------------------------------------------------------------
 * Ethernet driver config
 */

/*
 * There are 2 options for ethernet:
 *    The on-board SMSC LAN91C111
 *    for STb7109, the on-chip STMAC & on-board PHY
 */

#if 0 //YWDRIVER_MODI d02sh 2009.6.15 1->0
	/* Config for SMSC LAN91C111 (combined MAC+PHY) */
#	define CONFIG_DRIVER_SMC91111
#ifdef CONFIG_SH_SE_MODE
#	define CONFIG_SMC91111_BASE	0xb2000300ul
#else	/* CONFIG_SH_SE_MODE */
#	define CONFIG_SMC91111_BASE	0xa2000300ul
#endif	/* CONFIG_SH_SE_MODE */
#else
	/* Config for on-chip STMAC + STE10xP PHY */
#	define CONFIG_DRIVER_NETSTMAC
#	define CFG_STM_STMAC_BASE	0xb8110000ul
#	define CONFIG_STMAC_STE10XP
#	define CONFIG_CMD_MII
#endif


/*  If this board does not have eeprom for ethernet address so allow the user
 *  to set it in the environment
 */

#define CONFIG_ENV_OVERWRITE


/*---------------------------------------------------------------
 * USB driver config
 */

/* Choose if we want USB Mass-Storage Support */
//#define CONFIG_SH_STB7100_USB

#ifdef CONFIG_SH_STB7100_USB
#	define CONFIG_CMD_USB
#	define CONFIG_CMD_FAT
#	define CONFIG_USB_OHCI_NEW
#	define CONFIG_USB_STORAGE
#	define CFG_USB_OHCI_CPU_INIT
#	define CFG_USB_BASE			0xb9100000
#	define CFG_USB_OHCI_REGS_BASE		(CFG_USB_BASE+0xffc00)
#	define CFG_USB_OHCI_SLOT_NAME		"ohci"
#	define CFG_USB_OHCI_MAX_ROOT_PORTS	1
#	define LITTLEENDIAN
#endif	/* ifdef CONFIG_SH_STB7100_USB */

/*---------------------------------------------------------------
 * IDE driver config
 */

/* Choose one of the the following two: */
//#define CONFIG_SH_STB7100_IDE
#define CONFIG_SH_STB7100_SATA

#ifdef CONFIG_SH_STB7100_IDE
#	define CFG_PIO_MODE		4
#	define CFG_IDE_MAXBUS		1
#	define CFG_IDE_MAXDEVICE	1
#ifdef CONFIG_SH_SE_MODE
#	define CFG_ATA_BASE_ADDR	0xB2800000
#else	/* CONFIG_SH_SE_MODE */
#	define CFG_ATA_BASE_ADDR	0xA2800000
#endif	/* CONFIG_SH_SE_MODE */
#	define CFG_ATA_IDE0_OFFSET	0x00200000
#	define CFG_ATA_REG_OFFSET	0
#	define CFG_ATA_DATA_OFFSET	0
#	define CFG_ATA_STRIDE		0x00020000
#	define CFG_ATA_ALT_OFFSET	-0x0100000
#endif	/* CONFIG_SH_STB7100_IDE */

#ifdef CONFIG_SH_STB7100_SATA
#	define CFG_PIO_MODE		4
#	define CFG_IDE_MAXBUS		1
#	define CFG_IDE_MAXDEVICE	1
#	define CFG_ATA_BASE_ADDR	0xB9209800
#	define CFG_ATA_IDE0_OFFSET	0x0
#	define CFG_ATA_REG_OFFSET	0x0
#	define CFG_ATA_DATA_OFFSET	0x0
#	define CFG_ATA_STRIDE		0x4
#	define CFG_ATA_ALT_OFFSET	0x8
#endif	/* CONFIG_SH_STB7100_SATA */

#if defined(CONFIG_SH_STB7100_IDE)  ||	\
    defined(CONFIG_SH_STB7100_SATA) ||	\
    defined(CONFIG_SH_STB7100_USB)
#	define CFG_64BIT_LBA
#	define CONFIG_LBA48
#	define CONFIG_DOS_PARTITION
#	define CONFIG_CMD_EXT2
#endif

/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */

#define CFG_HUSH_PARSER		1
#define CFG_LONGHELP		1		/* undef to save memory		*/
#define CFG_PROMPT		"MB442> "	/* Monitor Command Prompt	*/
#define CFG_PROMPT_HUSH_PS2	"> "
#define CFG_CBSIZE		1024
#define CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16) /* Print Buffer Size	*/
#define CFG_MAXARGS		16		/* max number of command args	*/
#define CFG_HZ			(P_CLOCK_RATE/1024) /* HZ for timer ticks	*/
#define CFG_LOAD_ADDR		CFG_SDRAM_BASE	/* default load address		*/
#define CFG_BOOTMAPSZ		(16 << 20)	/* initial linux memory size	*/
#define CONFIG_BOOTDELAY	3		/* default delay before executing bootcmd */
#define CONFIG_ZERO_BOOTDELAY_CHECK

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE       1

/*-----------------------------------------------------------------------
 * NOR FLASH organization
 */

/* STb7100 reference board organised as 8 MiB flash with 128 KiB blocks */
#define CFG_FLASH_CFI_DRIVER
#define CFG_FLASH_CFI
#define CFG_FLASH_PROTECTION	1	/* use hardware flash protection	*/
#define CFG_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#define CFG_MAX_FLASH_SECT	1024	/* max number of sectors on one chip	*/

#define CFG_FLASH_EMPTY_INFO		/* test if each sector is empty		*/

/*-----------------------------------------------------------------------
 * Addresss, size, & location of U-boot's Environment Sector
 */

#define CFG_ENV_IS_IN_FLASH	1
#define CFG_ENV_OFFSET		CFG_MONITOR_LEN
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + CFG_ENV_OFFSET)
#define CFG_ENV_SIZE		0x20000
#define CFG_ENV_SECT_SIZE	0x20000


//YWDRIVER_MODI D02SH 2009/07/20 add begin
//Description:add for nand flash & VFD
//vfd
#define YW_CONFIG_VFD 
#ifndef CONFIG_SOFT_I2C
#define CONFIG_SOFT_I2C
#endif
#ifdef CONFIG_SOFT_I2C
#define CONFIG_CMD_I2C
#define CFG_I2C_SPEED 1000000
#define CFG_I2C_SLAVE 0x00
#define I2C_DA_PORT 4
#define I2C_CL_PORT 4
#define I2C_DA_PIN  1
#define I2C_CL_PIN  0
#define	I2C_READ	STPIO_GET_PIN(I2C_DA_PORT,I2C_DA_PIN)
#define	I2C_SDA(x)	{if(x) \
                        STPIO_SET_PIN(PIO_PORT(4),I2C_DA_PIN,1);\
                     else \
                        STPIO_SET_PIN(PIO_PORT(4),I2C_DA_PIN,0);}
#define	I2C_SCL(x)	{if(x) \
                        STPIO_SET_PIN(PIO_PORT(4),I2C_CL_PIN,1);\
                     else \
                        STPIO_SET_PIN(PIO_PORT(4),I2C_CL_PIN,0);}

#define I2C_TRISTATE
#define I2C_DELAY udelay(40)//最高精度16us 所以模拟I2C的最大速率应该为1s/(16us*4)=15625<16K
#define I2C_ACTIVE
#endif //CONFIG_SOFT_I2C
//for nand flash 
#ifdef CONFIG_SH_SE_MODE
#define CFG_NAND_BASE           0xB2000000
#else
#define CFG_NAND_BASE           0xA2000000
#endif

#define CFG_MAX_NAND_DEVICE     1    /* Max number of NAND devices        */
#define NAND_MAX_CHIPS          1

#define CFG_NAND_PAGE_SIZE	2048		/* NAND chip page size		*/
#define CFG_NAND_4_ADDR_CYCLE	1		/* Fourth addr used (>32MB)	*/
//YWDRIVER_MODI D02SH 2009/07/20 add end


#endif	/* __CONFIG_H */
