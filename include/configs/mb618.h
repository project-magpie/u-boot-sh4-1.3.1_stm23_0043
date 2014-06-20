/*
 * (C) Copyright 2008 STMicroelectronics.
 *
 * Sean McGoogan <Sean.McGoogan@st.com>
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
#define CONFIG_CPU_SUBTYPE_SH4_3XX	/* it is an SH4-300		*/

/* This should really be replaced with something which uses bd->...	*/
#define CONFIG_MENUKEY ' '
// YWDRIVER_MODI sqy 2008/12/2 begin
#define START_UPDATE_CHAR   1           //SOH
#define BOOT_UPDATE_CHAR    17          //DC1
#define KERNEL_UPDATE_CHAR  18          //DC2
#define FS_UPDATE_CHAR      19          //DC3
#define ALL_UPDATE_CHAR     20          //DC4
#define FINISH_UPDATE_CHAR  24          //CAN
#define FAIL_UPDATE_CHAR    27          //ESC
#define P_CLOCK_RATE	    87500000	/* clock rate for CSP		*/

#define	RAW_KEY_MENU	    128
#define	RAW_KEY_OK		    8
#define	RAW_KEY_UP			4
#define	RAW_KEY_DOWN		32
#define	RAW_KEY_LEFT		2
#define	RAW_KEY_RIGHT		16
#define	RAW_KEY_POWER		64

#ifdef CONFIG_CMD_NAND
//#    define CFG_BOOT_FROM_NAND
#endif

/*-----------------------------------------------------------------------
 * Start addresses for the final memory configuration
 * Assume we run out of uncached memory for the moment
 */

#ifdef CONFIG_SH_SE_MODE
#define CFG_FLASH_BASE		0xA0000000	/* FLASH (uncached) via PMB */
#define CFG_SE_PHYSICAL_BASE	0x40000000	/* LMI Physical Address */
#define CFG_SDRAM_BASE		0x80000000      /* LMI    Cached addr via PMB */
#define CFG_SE_UNACHED_BASE	0x90000000	/* LMI UN-cached addr via PMB */
#define CFG_SE_SDRAM_WINDOW	(CFG_SDRAM_SIZE-1)
#else
#define CFG_FLASH_BASE		0xA0000000	/* FLASH in P2 region */
#define CFG_SDRAM_BASE		0x8C000000      /* SDRAM in P1 region */
#endif

#define CFG_SDRAM_SIZE		0x08000000	/* 128 MiB of LMI SDRAM */

//#define CFG_MONITOR_LEN		0x00040000	/* Reserve 256 KiB for Monitor */
//#define CFG_MONITOR_LEN		0x00060000	/* Reserve 384 KiB for Monitor */
#define CFG_MONITOR_LEN		0x00080000	/* Reserve 512 KiB for Monitor */
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

#define BOARD mb618

#define CONFIG_BOARD_VERSION_STRING "YW 1.0.023 Rel"

//YWDRIVER_MODI d48zm 2010/3/23 modify
#if CFG_MONITOR_LEN == 0x00008000		/* 32 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa0007fff"
#elif CFG_MONITOR_LEN == 0x00010000		/* 64 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa000ffff"
#elif CFG_MONITOR_LEN == 0x00018000		/* 96 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa0017fff"
#elif CFG_MONITOR_LEN == 0x00020000		/* 128 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa001ffff"
#elif CFG_MONITOR_LEN == 0x00040000		/* 256 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa003ffff"
#elif CFG_MONITOR_LEN == 0x00060000		/* 384 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa005ffff"
#elif CFG_MONITOR_LEN == 0x00080000		/* 512 KiB */
#	define MONITOR_SECTORS	"0xa0000000    0xa007ffff"
#else						/* unknown */
#	error "Unable to determine sectors for monitor"
#endif
//YWDRIVER_MODI d48zm 2010/3/23 modify end

//YWDRIVER_MODI D02SH 2009/07/20 add begin
//Description:check the kernel start addr
#ifdef 	CONFIG_SH_SE_MODE
#define CFG_KERNEL_START 0x80000000
#else
#define CFG_KERNEL_START 0x8C000000
#endif
//YWDRIVER_MODI D02SH 2009/07/20 add end

//YWDRIVER_MODI D02SH 2009/07/20 add start
// add some env for kernel parms
//YWDRIVER_MODI d48zm 2010/4/29 modify

#define CFG_YW_KERNEL_LENGTH_HEX    0x00700000
#define CFG_YW_KERNEL_BASE_HEX	    0xa0080000
//#define CFG_YW_KERNEL_END_HEX	    (CFG_YW_KERNEL_BASE_HEX + CFG_YW_KERNEL_LENGTH_HEX - 1)

//#define CFG_YW_KERNEL_SEC		" "XSTR(CFG_YW_KERNEL_BASE_HEX)" "XSTR(CFG_YW_KERNEL_END_HEX)" "
#define CFG_YW_KERNEL_SEC		" a0080000 a077ffff "
#define CFG_YW_KERNEL_LEN		" "XSTR(CFG_YW_KERNEL_LENGTH_HEX)" "
#define CFG_YW_KERNEL_BASE		" "XSTR(CFG_YW_KERNEL_BASE_HEX)" "

#define CFG_YW_ROOTFS_BASE      0xa0800000
#define CFG_YW_ROOTFS_SEC       "a0800000 a1ffffff"

#define CFG_YW_BOOTCMD 			"bootm " CFG_YW_KERNEL_BASE
#define	MAGIC_VERSION			"1.7"	// must change when upgrade u-boot
#define	NAND_CHIPSIZE			0x20000000	// 512MB
#define	NAND_ERASEBLOCK			0x40000		// 256KB

//#define CFG_YW_UPDATE_KERNEL "nand erase " CFG_YW_KERNEL_BASE CFG_YW_KERNEL_LEN ";"
//		"nand write.i " XSTR(CFG_LOAD_ADDR) CFG_YW_KERNEL_BASE CFG_YW_KERNEL_LEN

#define CFG_YW_UPDATE_KERNEL \
		"protect off " CFG_YW_KERNEL_SEC ";" \
		"erase " CFG_YW_KERNEL_SEC ";" \
		"cp.b " XSTR(CFG_LOAD_ADDR) CFG_YW_KERNEL_BASE CFG_YW_KERNEL_LEN ";" \
		"protect on " CFG_YW_KERNEL_SEC

#define CFG_SPARK_PATH              "spark"
#define CFG_SPARK_KERNEL_NAME       "mImage"
#define CFG_SPARK_USERFS_NAME       "userfsub.img"

#define CFG_SPARK_KERNEL_FULLNAME   CFG_SPARK_PATH"/"CFG_SPARK_KERNEL_NAME
#define CFG_SPARK_USERFS_FULLNAME   CFG_SPARK_PATH"/"CFG_SPARK_USERFS_NAME

#define CFG_ENIGMA2_PATH            "enigma2"
#define CFG_ENIGMA2_KERNEL_NAME     "uImage"
#define CFG_ENIGMA2_USERFS_NAME     "e2jffs2.img"

#define CFG_ENIGMA2_KERNEL_FULLNAME CFG_ENIGMA2_PATH"/"CFG_ENIGMA2_KERNEL_NAME
#define CFG_ENIGMA2_USERFS_FULLNAME CFG_ENIGMA2_PATH"/"CFG_ENIGMA2_USERFS_NAME

#define CONFIG_EXTRA_ENV_SETTINGS \
		"board=" XSTR(BOARD) "\0" \
		"monitor_base=" XSTR(CFG_MONITOR_BASE) "\0" \
		"monitor_len=" XSTR(CFG_MONITOR_LEN) "\0" \
		"monitor_sec=" MONITOR_SECTORS "\0" \
		"load_addr=" XSTR(CFG_LOAD_ADDR) "\0" \
		"unprot=" \
        "protect off $monitor_sec\0" \
        "update=" \
        "protect off $monitor_sec;erase $monitor_sec;" \
        "cp.b $load_addr $monitor_base $monitor_len;" \
        "protect on $monitor_sec\0" \
        "erase_env=" \
        "protect off 0xa0060000 0xa007ffff;" \
        "erase 0xa0060000 0xa007ffff;" \
        "protect on 0xa0060000 0xa007ffff\0" \
        "HOSTNAME=LINUX7109\0" \
		"ethaddr=FF:FF:FF:FF:FF:FF\0" \
		"ipaddr=192.168.40.63\0" \
		"netmask=255.255.255.0\0" \
		"gatewayip=192.168.3.1\0" \
		"serverip=192.168.40.19\0" \
		"bootcmd=" CFG_YW_BOOTCMD "\0" \
        "kernel_base=" CFG_YW_KERNEL_BASE "\0" \
		"kernel_base_spark=" CFG_YW_KERNEL_BASE "\0" \
		"kernel_base_enigma2=0x18000000\0" \
        "kernel_sec=" CFG_YW_KERNEL_SEC "\0" \
        "kernel_len=" CFG_YW_KERNEL_LEN "\0" \
        "update_kernel=" CFG_YW_UPDATE_KERNEL "\0" \
        "rootfs_base=" XSTR(CFG_YW_ROOTFS_BASE) "\0" \
        "rootfs_sec=" CFG_YW_ROOTFS_SEC "\0" \
		"menucmd=update\0" \
		"tftp_kernel_name="CFG_SPARK_KERNEL_NAME"\0" \
		"tftp_kernel_name_spark="CFG_SPARK_KERNEL_NAME"\0" \
		"tftp_kernel_name_enigma2="CFG_ENIGMA2_KERNEL_NAME"\0" \
		"tftp_userfs_name="CFG_SPARK_USERFS_NAME"\0" \
		"tftp_userfs_name_spark="CFG_SPARK_USERFS_NAME"\0" \
		"tftp_userfs_name_enigma2="CFG_ENIGMA2_USERFS_NAME"\0" \
		"kernel_name="CFG_SPARK_KERNEL_FULLNAME"\0" \
		"kernel_name_spark="CFG_SPARK_KERNEL_FULLNAME"\0" \
		"kernel_name_enigma2="CFG_ENIGMA2_KERNEL_FULLNAME"\0" \
		"userfs_name="CFG_SPARK_USERFS_FULLNAME"\0" \
		"userfs_name_spark="CFG_SPARK_USERFS_FULLNAME"\0" \
		"userfs_name_enigma2="CFG_ENIGMA2_USERFS_FULLNAME"\0" \
		"userfs_base=800000\0" \
		"userfs_base_spark=800000\0" \
		"userfs_base_enigma2=18800000\0" \
		"userfs_len=17800000\0" \
		"userfs_len_spark=17800000\0" \
		"userfs_len_enigma2=7700000\0" \
		"kernelnfspath=192.168.40.19:/opt/target\0" \
		"rootfs_name=UserFS\0" \
		"rootfsnfspath=192.168.40.19:/home/d22cj/workspace/target\0" \
		"uboot_name=u-boot.bin\0" \
		"ubootnfspath=192.168.40.19:/home/d22cj/workspace/target\0" \
		"bootfromnfs=nfs a4000000 $kernelnfspath/$kernel_name;bootm a4000000\0" \
		"bootargs_nfs=console=ttyAS1,115200 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:61 " \
		"stmmaceth=msglvl:0,phyaddr:1:watchdog:5000 root=/dev/nfs nfsroot=" \
		"192.168.40.19:/opt/target,nfsvers=2,rsize=4096," \
		"wsize=8192,tcp rw ip=192.168.40.61:192.168.40.19:192.168.3.1:255.255.0.0:" \
		"LINUX7109:eth0:off bigphysarea=4000\0" \
		"bootargs_flash=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.3.119:192.168.3.1:255.255.0.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=4000\0" \
		"bootargs=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.0.119:192.168.0.1:255.255.255.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=4000\0" \
		"bootargs_spark=console=ttyAS1,115200 rw ramdisk_size=6144 init=/linuxrc " \
		"root=/dev/ram0 nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:69 ip=192.168.0.69" \
		":192.168.3.119:192.168.3.1:255.255.0.0:lh:eth0:off stmmaceth=msglvl:0,phyaddr:1," \
		"watchdog:5000 bigphysarea=4000\0" \
		"bootargs_enigma2=console=ttyAS1,115200 root=/dev/mtdblock6 rootfstype=jffs2 " \
		"rw init=/bin/devinit coprocessor_mem=4m@0x40000000,4m@0x40400000 printk=1 " \
		"nwhwconf=device:eth0,hwaddr:00:80:E1:12:40:61 rw ip=172.100.100.249:172.100.100.174:" \
		"172.100.100.174:255.255.0.0:LINUX7109:eth0:off bigphysarea=6000 stmmaceth=msglvl:0,phyaddr:2,watchdog:5000\0" \
		"boot_system=spark\0"	\
		"magic_version=" MAGIC_VERSION "\0"
//YWDRIVER_MODI D02SH 2009/07/20 add end

/*--------------------------------------------------------------
 * Command line configuration.
 */

#include <config_cmd_default.h>

#define CONFIG_CMD_NET
#define CONFIG_CMD_DFL
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_NFS
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_CMD_UPDATE

/*--------------------------------------------------------------
 * Serial console info
 */

/*
 * We can use one of two methods for the "serial" console.
 * We can either use the (normal hardware) internal ST ASC UART;
 * OR we can use STMicroelectronics' DTF (Data Transfer Format)
 * mechanism over a JTAG link to a remote GDB debugger.
 */
#ifndef CONFIG_YW_BURNER
#	define CONFIG_STM_ASC_SERIAL	/* use a ST ASC UART */
#else
#	define CONFIG_STM_DTF_SERIAL	/* use DTF over JTAG */
#endif

/* choose which ST ASC UART to use */
#if 1
#	define CFG_STM_ASC_BASE		0xfd032000ul	/* UART2 */
#else
#	define CFG_STM_ASC_BASE		0xfd033000ul	/* UART3 */
#endif

/*---------------------------------------------------------------
 * Ethernet driver config
 */

/*
 * There are 2 options for ethernet, both use the on-chip ST-GMAC.
 * The choice in PHYs are:
 *    The on-board SMSC LAN8700
 *    External PHY connected via the MII off-board connector.
 */

/* are we using the internal ST GMAC device ? */
#define CONFIG_DRIVER_NET_STM_GMAC //d02sh 20090708

/*
 * Select the appropriate base address for the GMAC.
 * Also, choose which PHY to use.
 */
#ifdef CONFIG_DRIVER_NET_STM_GMAC
#	define CFG_STM_STMAC_BASE	 0xfd110000ul	/* MAC = STM GMAC0 */
#	define CONFIG_STMAC_LAN8700			/* PHY = SMSC LAN8700 */
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

/*  If this board does not have eeprom for ethernet address so allow the user
 *  to set it in the environment
 */
#define CONFIG_ENV_OVERWRITE


/*---------------------------------------------------------------
 * USB driver config
 */

/* Choose if we want USB Mass-Storage Support */
#define CONFIG_SH_STB7100_USB

#ifdef CONFIG_SH_STB7100_USB
#	define CONFIG_CMD_USB
#	define CONFIG_CMD_FAT
#	define CONFIG_USB_OHCI_NEW
#	define CONFIG_USB_STORAGE
#	define CFG_USB_OHCI_CPU_INIT
#	define CFG_USB_BASE			0xfe100000
#	define CFG_USB_OHCI_REGS_BASE		(CFG_USB_BASE+0xffc00)
#	define CFG_USB_OHCI_SLOT_NAME		"ohci"
#	define CFG_USB_OHCI_MAX_ROOT_PORTS	1
#	define LITTLEENDIAN
#endif	/* ifdef CONFIG_SH_STB7100_USB */

/*---------------------------------------------------------------
 * IDE driver config
 */

#if defined(CONFIG_SH_STB7100_USB)
#	define CFG_64BIT_LBA
#	define CONFIG_LBA48
#	define CONFIG_DOS_PARTITION
#	define CONFIG_CMD_EXT2
#endif

/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */

#define CFG_HUSH_PARSER		1
#define CFG_AUTO_COMPLETE	1
#define CFG_LONGHELP		1		/* undef to save memory		*/
#define CFG_PROMPT		"MB618> "	/* Monitor Command Prompt	*/
#define CFG_PROMPT_HUSH_PS2	"> "
#define CFG_CBSIZE		1024
#define CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16) /* Print Buffer Size	*/
#define CFG_MAXARGS		16		/* max number of command args	*/
#define CFG_HZ			(P_CLOCK_RATE/1024) /* HZ for timer ticks	*/
#define CFG_LOAD_ADDR		CFG_SDRAM_BASE	/* default load address		*/
#define CFG_BOOTMAPSZ		(16 << 20)	/* initial linux memory size	*/
#define CONFIG_BOOTDELAY	3//10		/* default delay before executing bootcmd */
#define CONFIG_ZERO_BOOTDELAY_CHECK

#define CONFIG_CMDLINE_EDITING

/*-----------------------------------------------------------------------
 * FLASH organization
 */

/* Whether the hardware supports NOR or NAND Flash depends on J34.
 * One ONE of these may be present at any one time. Each hides the other.
 * In position 1-2 CSA selects NAND, in position 2-3 is selects NOR.
 * Note that J30A must also be in position 2-3 to select the
 * on-board Flash (for either the on-board NOR or NAND flash).
 *
 * i.e.		ON-board NOR FLASH:	J30A:2-3, J34:2-3
 *	 	ON-board NAND FLASH:	J30A:2-3, J34:1-2
 */
//#define CONFIG_CMD_NAND		/* define for NAND flash */

/*-----------------------------------------------------------------------
 * NOR FLASH organization
 */

/* M58LT256GT: 32MiB 259 blocks, 128 KiB block size */
#ifndef CFG_BOOT_FROM_NAND	//CONFIG_CMD_NAND				/* NOR flash present ? */
#	define CONFIG_CMD_JFFS2			/* enable JFFS2 support */
#	define CFG_FLASH_CFI_DRIVER
#	define CFG_FLASH_CFI
#	define CONFIG_FLASH_PROTECT_SINGLE_CELL
#	define CFG_FLASH_PROTECTION	1	/* use hardware flash protection	*/
#	define CFG_MAX_FLASH_BANKS	1	/* max number of memory banks		*/
#	define CFG_MAX_FLASH_SECT	259	/* max number of sectors on one chip	*/
#	define CFG_FLASH_EMPTY_INFO		/* test if each sector is empty		*/
#define MTDPARTS_DEFAULT						\
	"mtdparts="							\
	"physmap-flash:"	/* First NOR flash device */		\
		"256k(U-Boot)"		/* first partition */		\
		",128k(Environment)"					\
		",4M(Kernel)"						\
		",-(RestOfNor)"		/* last partition */
#define MTDIDS_DEFAULT							\
	"nor0=physmap-flash"	/* First NOR flash device */
#endif	/* CONFIG_CMD_NAND */

/*-----------------------------------------------------------------------
 * NAND FLASH organization
 */

/* NAND512W3A: 64MiB  8-bit, 4096 Blocks (16KiB+512B) of 32 Pages (512+16) */
/* NAND512W4A: 64MiB 16-bit, 4096 Blocks (16KiB+512B) of 32 Pages (512+16) */
#ifdef CONFIG_CMD_NAND				/* NAND flash present ? */
#	define CONFIG_CMD_JFFS2			/* enable JFFS2 support */
#	define CFG_MAX_NAND_DEVICE	1
#	define NAND_MAX_CHIPS		CFG_MAX_NAND_DEVICE
#	define CFG_NAND0_BASE		0xA4000000//CFG_FLASH_BASE	/* Occludes NOR flash */
#	define CFG_NAND_BASE_LIST	{ CFG_NAND0_BASE }
#define	CFG_NAND_FLEX_CSn_MAP {1}

#ifdef CFG_BOOT_FROM_NAND
#	undef CONFIG_CMD_FLASH			/* NOR-flash specific */
#	undef CONFIG_CMD_IMLS			/* NOR-flash specific */
#	define CFG_NO_FLASH			/* no NOR-flash when using NAND-flash */
#define MTDPARTS_DEFAULT						\
	"mtdparts="							\
	"gen_nand.1:"		/* First NAND flash device */		\
		"128k(Environment)"	/* first partition */		\
		",4M(Kernel)"						\
		",32M(rootfs)"						\
		",-(RestOfNand)"	/* last partition */
#define MTDIDS_DEFAULT							\
	"nand0=gen_nand.1"	/* First NAND flash device */
#endif

//YWDRIVER_MODI d48zm 2010/3/10 add
/*
	 * Currently, there are 2 main modes to read/write from/to
	 * NAND devices on STM SoCs:
	 *	a) "bit-banging" (can NOT be used in boot-from-NAND)
	 *	b) FLEX-mode (only supported means for boot-from-NAND)
	 * If CFG_NAND_FLEX_MODE is defined, then FLEX-mode will be
	 * used, otherwise, "bit-banging" will be used.
	 */
#	define CFG_NAND_FLEX_MODE	/* define to use NAND FLEX-MODE */
	/*
	 * Do we want to read/write NAND Flash compatible with the ST40's
	 * NAND Controller H/W IP block for "boot-mode"? If we want
	 * to read/write NAND flash that is meant to support booting
	 * from NAND, then we need to use 3 bytes of ECC per 128 byte
	 * record.  If so, then define the "CFG_NAND_ECC_HW3_128" macro.
	 */
#ifdef CFG_BOOT_FROM_NAND
#	define CFG_NAND_ECC_HW3_128	/* define for "boot-from-NAND" compatibility */
#endif
	/*
	 * If using CFG_NAND_ECC_HW3_128, then we must also define
	 * where the (high watermark) boundary is. That is, the
	 * NAND offset, below which we are in "boot-mode", and
	 * must use 3 bytes of ECC for each 128 byte record.
	 * For this offset (and above) we can use any supported
	 * ECC configuration (e.g 3/256 S/W, or 3/512 H/W).
	 */
#	define CFG_NAND_STM_BOOT_MODE_BOUNDARY (1ul << 20)	/* 1 MiB */

	/*
	 * If we want to store the U-boot environment variables in
	 * the NAND device, then we also need to specify *where* the
	 * environment variables will be stored. Typically this
	 * would be immediately after the U-boot monitor itself.
	 * However, that *may* be a bad block. Define the following
	 * to place the environment in an appropriate good block.
	 */
#	define CFG_NAND_ENV_OFFSET	 (1ul << 20)		/* first 1MiB reserve for u-boot */
#	define YW_CFG_NAND_ENV_BOUND (CFG_NAND_ENV_OFFSET + 0x100000)	/*  reserve 1MiB for env to skip bad block */
//YWDRIVER_MODI d48zm 2010/3/10 add end
#endif	/* CONFIG_CMD_NAND */

/*-----------------------------------------------------------------------
 * Addresss, size, & location of U-boot's Environment Sector
 */

//#ifdef CONFIG_CMD_NAND				/* NAND flash present ? */
#ifdef CFG_BOOT_FROM_NAND
#	define CFG_ENV_IS_IN_NAND		/* enviroment in NAND flash */
//YWDRIVER_MODI d48zm 2010/3/11 modify
#if 1
#	define CFG_ENV_OFFSET	CFG_NAND_ENV_OFFSET
#else
#	define CFG_ENV_OFFSET	0		/* begining of NAND flash */
#endif
//YWDRIVER_MODI end
#else
#	define CFG_ENV_IS_IN_FLASH		/* environment in NOR flash */
/***** YWDRIVER_MODI 2010-10-11 D26LF Modi:
    Description:防止Uboot使用512k是把环境变量也内置
*/
#if 1
#	define CFG_ENV_OFFSET	(CFG_MONITOR_LEN - 0x20000)	/* After u-boot.bin */
#else
#	define CFG_ENV_OFFSET	CFG_MONITOR_LEN /* After u-boot.bin */
#endif
/***** 2010-10-11 D26LF Modi end ****/
#endif	/* CONFIG_CMD_NAND */
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + CFG_ENV_OFFSET)
#define CFG_ENV_SIZE		0x20000
#define CFG_ENV_SECT_SIZE	0x20000

/*----------------------------------------------------------------------
 * JFFS2 support
 */

#if defined(CONFIG_CMD_JFFS2)
#	ifdef CONFIG_CMD_NAND			/* NAND flash present ? */
#		define CONFIG_JFFS2_NAND	/* JFFS2 support on NAND Flash */
#	endif	/* CONFIG_CMD_NAND */
#	define CONFIG_JFFS2_CMDLINE		/* mtdparts command line support */
#endif	/* CONFIG_CMD_JFFS2 */
//YWDRIVER_MODI start
//ps for some special function
//vfd
#define YW_CONFIG_VFD
#ifndef CONFIG_SOFT_I2C
#define CONFIG_SOFT_I2C
#endif
#ifdef CONFIG_SOFT_I2C
#include <asm/stx7111reg.h>
#define CONFIG_CMD_I2C
#define CFG_I2C_SPEED 1000000
#define CFG_I2C_SLAVE 0x00
#define I2C_DA_PORT 3
#define I2C_CL_PORT 3
#define I2C_DA_PIN  1
#define I2C_CL_PIN  0
#define I2C_INIT	{SET_PIO_PIN(PIO_PORT(3), I2C_CL_PIN, STPIO_OUT);\
						SET_PIO_PIN(PIO_PORT(3), I2C_DA_PIN, STPIO_OUT);}
#define	I2C_READ	STPIO_GET_PIN(I2C_DA_PORT,I2C_DA_PIN)
#define	I2C_SDA(x)	{if(x) \
                        STPIO_SET_PIN(PIO_PORT(3),I2C_DA_PIN,1);\
                     else \
                        STPIO_SET_PIN(PIO_PORT(3),I2C_DA_PIN,0);}
#define	I2C_SCL(x)	{if(x) \
                        STPIO_SET_PIN(PIO_PORT(3),I2C_CL_PIN,1);\
                     else \
                        STPIO_SET_PIN(PIO_PORT(3),I2C_CL_PIN,0);}

#define I2C_TRISTATE	SET_PIO_PIN(PIO_PORT(3), I2C_DA_PIN, STPIO_BIDIR)
#define I2C_DELAY 	udelay(40)//最高精度16us 所以模拟I2C的最大速率应该为1s/(16us*4)=15625<16K
#define I2C_ACTIVE		SET_PIO_PIN(PIO_PORT(3), I2C_DA_PIN, STPIO_OUT)
#define I2C_INPUT		SET_PIO_PIN(PIO_PORT(3), I2C_DA_PIN, STPIO_IN)
#endif //CONFIG_SOFT_I2C

#define CONFIG_SH_NO_EPLD
//YWDRIVER_MODI end


#endif	/* __CONFIG_H */
