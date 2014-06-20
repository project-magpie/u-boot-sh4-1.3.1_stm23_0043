/********************************************************************
 *
 * Unless otherwise specified, Copyright (C) 2004-2005 Barco Control Rooms
 *
 * $Source: D:/STB_BASE_HAL/u-boot-sh4-1.3.1_stm23_0043/board/barco/barco_svc.h,v $
 * $Revision: 1.1.1.1 $
 * $Author: d22cj $
 * $Date: 2010/01/20 05:04:10 $
 *
 * Last ChangeLog Entry
 * $Log: barco_svc.h,v $
 * Revision 1.1.1.1  2010/01/20 05:04:10  d22cj
 * 1、U-Boot首次导入
 * 2、修改启动参数
 * 3、修改进入菜单的方法：只能用ESC或者键盘进入
 *
 * Revision 1.1.1.1  2009/07/08 08:48:28  d02sh
 * ST初始代码：U-BOOT版本1.3.1
 *
 * Revision 1.2  2005/02/21 12:48:58  mleeman
 * update of copyright years (feedback wd)
 *
 * Revision 1.1  2005/02/14 09:31:07  mleeman
 * renaming of files
 *
 * Revision 1.1  2005/02/14 09:23:46  mleeman
 * - moved 'barcohydra' directory to a more generic barco; since we will be
 *   supporting and adding multiple boards
 *
 * Revision 1.1  2005/02/08 15:40:19  mleeman
 * modified and added platform files
 *
 * Revision 1.2  2005/01/25 08:05:04  mleeman
 * more cleanup of the code
 *
 * Revision 1.1  2004/07/20 08:49:55  mleeman
 * Working version of the default and nfs kernel booting.
 *
 *
 *******************************************************************/

#ifndef _LOCAL_BARCOHYDRA_H_
#define _LOCAL_BARCOHYDRA_H_

#include <flash.h>
#include <asm/io.h>

/* Defines for the barcohydra board */
#ifndef CFG_FLASH_ERASE_SECTOR_LENGTH
#define CFG_FLASH_ERASE_SECTOR_LENGTH (0x10000)
#endif

#ifndef CFG_DEFAULT_KERNEL_ADDRESS
#define CFG_DEFAULT_KERNEL_ADDRESS (CFG_FLASH_BASE + 0x30000)
#endif

#ifndef CFG_WORKING_KERNEL_ADDRESS
#define CFG_WORKING_KERNEL_ADDRESS (0xFFE00000)
#endif


typedef struct SBootInfo {
	unsigned int address;
	unsigned int size;
	unsigned char state;
}TSBootInfo;

/* barcohydra.c */
int checkboard(void);
long int initdram(int board_type);
void pci_init_board(void);
void check_flash(void);
int write_flash(char *addr, char value);
TSBootInfo* find_boot_info(void);
void final_boot(void);
#endif
