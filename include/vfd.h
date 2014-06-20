#ifndef	__VFD_H__
#define	__VFD_H__

#ifndef BOOL
#define BOOL int
#endif

//-------------------VFD Ïà¹Øº¯Êý¡¡SH
extern void YWVFD_ROOTFS_P(int pro_rate);
extern void YWVFD_U_BOOT(void);
extern void YWVFD_U_Kernel(void);
extern void YWVFD_Warn(char*  str);
extern void YWVFD_U_MENU(void);
extern void YWVFD_BOOT_P(int pro_rate);
extern void YWVFD_KERNEL_P(int pro_rate);
extern void YWVFD_Print(char* str);
extern int YWVFD_GetScanKey(int *key);
extern BOOL YWVFD_HasKeyPress(int *pKey);
extern BOOL YWVFD_HasKeyPressJudge(void);
extern void YWVFD_WaitKeyRelease(void);
extern void YWVFD_WaitKeyPress(int *pKey);
extern BOOL YWVFD_WaitNewKeyPress(int *pKey);
extern BOOL YWVFD_GetScanKeyUntilRelease(int *pKey);

#endif
