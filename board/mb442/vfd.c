/*$Source: D:/STB_BASE_HAL/u-boot-sh4-1.3.1_stm23_0043/board/mb442/vfd.c,v $*/
/*****************************文件头部注释*************************************/
//
//			Copyright (C), 2009-2014, AV Frontier Tech. Co., Ltd.
//
//
// 文 件 名：	$RCSfile: vfd.c,v $
//
// 创 建 者：	D02SH
//
// 创建时间：	2009.01.09
//
// 最后更新：	$Date: 2010/01/20 05:03:56 $
//
//				$Author: d22cj $
//
//				$Revision: 1.1.1.1 $
//
//				$State: Exp $
//
// 文件描述：	将VFD内容独立出来
//
/******************************************************************************/

//#ifdef YW_CONFIG_VFD
/********************************  文件包含************************************/
#include <common.h>
#include <command.h>
#include <asm/stb7100reg.h>
#include <asm/io.h>
#include <asm/pio.h>
#ifdef COMBO
#include <i2c.h>
#endif
/********************************  常量定义************************************/
//需要显示的内容
static char show_p_boot[]="!BOOT-";
static char show_p_kern[]="!KERN-";
static char show_p_root[]="!ROOT-";

extern void VFD_ROOTFS_P(int pro_rate);
extern void VFD_U_BOOT(void);
extern void VFD_U_Kernel(void);
extern void VFD_Warn(char* str);
extern void VFD_U_MENU(void);
extern void VFD_BOOT_P(int pro_rate);
extern void VFD_KERNEL_P(int pro_rate);
extern void VFD_Print(char * str);

/********************************  数据结构************************************/
typedef struct SegAddrVal_s{
	int Segaddr1;
	int Segaddr2;
	int CurrValue1;
	int CurrValue2;
}SegAddrVal_T; 

static SegAddrVal_T VfdSegAddr[15];

typedef enum SegNum_e{
	SEGNUM1 = 0,
	SEGNUM2
}SegNum_T;
int CharLib[49][2] = 
{
	{0xF1, 0x38},	//A
	{0x74, 0x72},	//B
	{0x01, 0x68},	//C
	{0x54, 0x72},	//D
	{0xE1, 0x68},	//E
	{0xE1, 0x28},	//F
	{0x71, 0x68},	//G
	{0xF1, 0x18},	//H
	{0x44, 0x62},	//I
	{0x45, 0x22},	//J
	{0x46, 0x06},	//K
	{0x01, 0x48},	//L
	{0x51, 0x1D},	//M
	{0x53, 0x19},	//N
	{0x11, 0x78},	//O
	{0xE1, 0x38},	//P
	{0x13, 0x78},	//Q
	{0xE3, 0x38},	//R
	{0xF0, 0x68},	//S
	{0x44, 0x22},	//T
	{0x11, 0x58},	//U
	{0x49, 0x0C},	//V
	{0x5B, 0x18},	//W
	{0x4A, 0x05},	//X
	{0x44, 0x05},	//Y
	{0x48, 0x64},	//Z
	/* A--Z  */	
	{0x01, 0x68},	
	{0x42, 0x01},	
	{0x10, 0x70},	//
	{0x43, 0x09},	//
	{0xE0, 0x00},	//
	{0xEE, 0x07},	//
	{0xE4, 0x02},	//
	{0x50, 0x00},	//
	{0xE0, 0x00},	//
	{0x05, 0x00},	//
	{0x48, 0x04},	//
	
	{0x11, 0x78},	//
	{0x44, 0x02},	//
	{0xE1, 0x70},	//
	{0xF0, 0x70},	//
	{0xF0, 0x18},	//
	{0xF0, 0x68},	//
	{0xF1, 0x68},	//
	{0x10, 0x30},	//
	{0xF1, 0x78},	//
	{0xF0, 0x78},	//
	/* 0--9  */
	{0x00, 0x00},//space
	//{0x4a, 0x40}  //升级专用{0x4e,0x40}
	{0xe4, 0x58}
};

int NumLib[11][2] = 
{
	{0x77, 0x77},	//{01110111, 01110111},
	{0x24, 0x22},	//{00100100, 00010010},
	{0x6B, 0x6D},	//{01101011, 01101101},
	{0x6D, 0x6B},	//{01101101, 01101011},
	{0x3C, 0x3A},	//{00111100, 00111010},
	{0x5D, 0x5B},	//{01011101, 01011011},
	{0x5F, 0x5F},	//{01011111, 01011111},
	{0x64, 0x62},	//{01100100, 01100010},
	{0x7F, 0x7F},	//{01111111, 01111111},
	{0x7D, 0x7B}, 	//{01111101, 01111011},
	{0x00, 0x00}    //space
};

#define LOG_OFF     0
#define LOG_ON      1

typedef enum LogNum_e
{
/*----------------------------------11G-------------------------------------*/
	PLAY_FASTBACKWARD = 11*15+1,
	PLAY_HEAD,
	PLAY_LOG,
	PLAY_TAIL,
	PLAY_FASTFORWARD,
	PLAY_PAUSE,
    REC1,
    MUTE,
    CYCLE,
    DUBI,
    CA,
    CI,
    USB,
    DOUBLESCREEN,
    REC2,
/*----------------------------------12G-------------------------------------*/
    HDD_A8 = 12*15+1,
    HDD_A7,
    HDD_A6,
    HDD_A5,
    HDD_A4,
    HDD_A3,
    HDD_FULL,
    HDD_A2,
    HDD_A1,
    MP3,
    AC3,
    TVMODE_LOG,
    AUDIO,
    ALERT,
    HDD_A9,
/*----------------------------------13G-------------------------------------*/
    CLOCK_PM = 13*15+1,
    CLOCK_AM,
    CLOCK,
    TIME_SECOND, /*时与分之间的点*/
    DOT2,
    STANDBY,
    TER,
    DISK_S3,
    DISK_S2,
    DISK_S1,
    DISK_S0,
    SAT,
    TIMESHIFT,
    DOT1,
    CAB,	
  /*----------------------------------end-------------------------------------*/  
    LogNum_Max
}LogNum_T;
#ifndef COMBO
/********************************  宏 定 义************************************/
#define VFD_CS_CLR() {udelay(10);STPIO_SET_PIN(PIO_PORT(3), 5, 0);}
#define VFD_CS_SET() {udelay(10);STPIO_SET_PIN(PIO_PORT(3), 5, 1);}

/********************************  变量定义************************************/
#define PIO_BASE  0xb8020000  
#define PIO2_BASE  0xb8024000 

/********************************  变量引用************************************/

/********************************  函数声明************************************/

/********************************  函数定义************************************/

/*************************************************************
    函数名称:	YW_VFD_WR
    函数说明:	VFD写data
    算法说明:	NA
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.01        D02SH         新建
*************************************************************/
void YW_VFD_WR(int data)
{
    int i = 0; 
    
	for(i = 0; i < 8; i++)
	{
        STPIO_SET_PIN(PIO_PORT(3), 4, 0);
        udelay(1);
		if(data & 0x01)
		{
            STPIO_SET_PIN(PIO_PORT(3), 2, 1);            
		}
		else
		{			
            STPIO_SET_PIN(PIO_PORT(3), 2, 0);				
		}
        STPIO_SET_PIN(PIO_PORT(3), 4, 1);		
        udelay(1);
		data >>= 1;
	}
}

/*************************************************************
    函数名称:	YWPANEL_VFD_RD
    函数说明:	通过PIO模拟SPI读BYTE
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.20        D02SH         新建
*************************************************************/
int  YW_VFD_RD(void)
{
    int i;
    int val = 0 ;
    SET_PIO_PIN(PIO_PORT(3), 2, STPIO_IN);
    for (i = 0; i < 8; i++)
    {
        //val >>= 1;
        STPIO_SET_PIN(PIO_PORT(3), 4, 0);
        udelay(1); 
        val |= (STPIO_GET_PIN(3, 2) << i);
        STPIO_SET_PIN(PIO_PORT(3), 4, 1);     
        udelay(1); 
    }
    udelay(1); 
    SET_PIO_PIN(PIO_PORT(3), 2, STPIO_OUT);
    return val;
}
/*************************************************************
    函数名称:	SegAddrInit
    函数说明:	初始化相应的地址
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.01        D02SH         新建
*************************************************************/
void SegAddrInit(void)
{
	int i = 0, addr = 0xC0;
	for(i = 0; i < 13; i++)
	{
		VfdSegAddr[i + 1].CurrValue1 = 0;
		VfdSegAddr[i + 1].CurrValue2 = 0;
		VfdSegAddr[i + 1].Segaddr1 = addr;
		VfdSegAddr[i + 1].Segaddr2 = addr + 1;
		addr += 3;
	}
} 
/*************************************************************
    函数名称:	SetDigAndSeg
    函数说明:	设置dig和seg的值 注意CS的设置
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.19        D02SH         新建
*************************************************************/
void SetDigAndSeg(int dignum, SegNum_T segnum, int val)
{
    int  addr=0;    
    VFD_CS_CLR();
    if(segnum == SEGNUM1)
	{
        addr = VfdSegAddr[dignum].Segaddr1;
        VfdSegAddr[dignum].CurrValue1 = val ;
	}
    else if(segnum == SEGNUM2)
    {
        addr = VfdSegAddr[dignum].Segaddr2;
        VfdSegAddr[dignum].CurrValue2 = val ;
    }
    YW_VFD_WR(addr); 
    udelay(10);
    YW_VFD_WR(val);
    VFD_CS_SET();
}
/*************************************************************
    函数名称:	ShowContent
    函数说明:	显示开
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.19        D02SH         新建
*************************************************************/
void ShowContent(void)
{
    VFD_CS_CLR(); 
    YW_VFD_WR(0x8F);
    VFD_CS_SET(); 
}

/*************************************************************
    函数名称:	VFD_ClearAll
    函数说明:	清空显示缓存内容
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.21        D02SH         新建
*************************************************************/
void VFD_ClearAll(void)
{
 	int i = 0;
 	for(i = 0; i < 13; i++)
	{
        SetDigAndSeg(i + 1,SEGNUM1,0x00);
        ShowContent();
		VfdSegAddr[i + 1].CurrValue1 = 0x00;
        SetDigAndSeg(i + 1,SEGNUM2,0x00);
        ShowContent();
		VfdSegAddr[i + 1].CurrValue2 = 0;
    }	
}

/*************************************************************
    函数名称:	VFDDrawChar
    函数说明:	在相应位置写字符_基本可用
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.20        D02SH         新建
*************************************************************/
void VFDDrawChar(char c, int position)
{
	if(position < 1 || position > 8)
	{
//		printf("char position error! %d\n", position);
		return;
	}
	if(c >= 65 && c <= 95)
		c = c - 65;
	else if(c >= 97 && c <= 122)
		c = c - 97;
	else if(c >= 42 && c <= 57)
		c = c - 11;
	else if(c == 32)
		c = 47;
	else if(c == 33)
        c = 48;
    else
	{
//		printf("unknown char!\n");
		return;
	}
	SetDigAndSeg(position, SEGNUM1, CharLib[(int)c][0]);
	SetDigAndSeg(position, SEGNUM2, CharLib[(int)c][1]);

    ShowContent();
}

/*************************************************************
    函数名称:	VFDDrawNum
    函数说明:	相应位置写数字_基本可用
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.20        D02SH         新建
*************************************************************/
void VFDDrawNum(int c, int position)
{
	int dignum = 0;
	
	if(position < 1 || position > 4)
	{
//		printf( "num position error! %d\n", position);
		return;
	}
    if(c > 9)
	{
//		printf( "unknown num!\n");
		return;
	}
	dignum =10 - position / 3;
	if(position % 2 == 1)
	{
		if(NumLib[c][1] & 0x01)
			SetDigAndSeg(dignum, SEGNUM1, VfdSegAddr[dignum].CurrValue1 | 0x80);
		else
			SetDigAndSeg(dignum, SEGNUM1, VfdSegAddr[dignum].CurrValue1 & 0x7F);
    		VfdSegAddr[dignum].CurrValue2 = VfdSegAddr[dignum].CurrValue2 & 0x40;//sz
    		SetDigAndSeg(dignum, SEGNUM2, (NumLib[c][1] >> 1) | VfdSegAddr[dignum].CurrValue2);		
	}
	else if(position % 2 == 0)
	{
	   if((NumLib[c][0] & 0x01))
        {
            SetDigAndSeg(dignum, SEGNUM2, VfdSegAddr[dignum].CurrValue2 | 0x40);// SZ  08-05-30
	   	}
	   else
			SetDigAndSeg(dignum, SEGNUM2, VfdSegAddr[dignum].CurrValue2 & 0x3F);
    		VfdSegAddr[dignum].CurrValue1 = VfdSegAddr[dignum].CurrValue1 & 0x80;
    		SetDigAndSeg(dignum, SEGNUM1, (NumLib[c][0] >>1 ) | VfdSegAddr[dignum].CurrValue1 );
	}
    ShowContent();
}

/*************************************************************
    函数名称:	VFD_SHOW_Time
    函数说明:	show time
    算法说明:	NA
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.01        D02SH         新建
*************************************************************/
void VFD_SHOW_Time(int hh,int mm)
{
    
    if( (hh > 24) && (mm > 60))
    {
//        printf("BAD ERROR!");
       return ;
    }
    VFDDrawNum((hh/10), 1);
    VFDDrawNum((hh%10), 2);
    VFDDrawNum((mm/10), 3);
    VFDDrawNum((mm%10), 4);
}
/*************************************************************
    函数名称:	VFD_ShowString
    函数说明:	显示字符串
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.20        D02SH         新建
*************************************************************/
void VFD_Show_String(char* str)
{
	int lenth = 0;
 	int i = 0;
 	lenth = strlen(str);
    if (lenth > 8)
    {
//        printf("BAD ARG!");
        lenth = 8;
    }
  	for(i = 0; i < 8; i++)
	{
        if(i < lenth)
        {
    	 	VFDDrawChar(*str, i + 1);
    		str++;
        }
        else
        {
            VFDDrawChar(' ', i + 1);
        }
	}
 }
/******************************显示小图标相关**********************************************/

/*************************************************************
    函数名称:	VFD_SHOW_LOG
    函数说明:	显示小图标LOG
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	log_num为需要显示的图标
                log_stat图标的状态
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.21        D02SH         新建
*************************************************************/
void VFD_SHOW_LOG(LogNum_T log_num,int log_stat)
{
    int dig_num = 0,seg_num = 0;
    SegNum_T seg_part = 0;
    int  seg_offset = 0;
    int  addr = 0,val = 0;
    //--------------------参数过滤---------------------
    if(log_num >= LogNum_Max)
    {
//        printf("BAD ARG!");
        return;
    }
    dig_num = log_num/15;
    seg_num = log_num%15;
    seg_part = seg_num/9;       
    VFD_CS_CLR();
    if(seg_part == SEGNUM1)
	{        
        seg_offset = 0x01 << ((seg_num%9) - 1);
        addr = VfdSegAddr[dig_num].Segaddr1;
        if(log_stat == LOG_ON)
        {
           VfdSegAddr[dig_num].CurrValue1 |= seg_offset;
        }
        if(log_stat == LOG_OFF)
        {
           VfdSegAddr[dig_num].CurrValue1 &= (0xFF-seg_offset);
        }
        val = VfdSegAddr[dig_num].CurrValue1 ;
	}
    else if(seg_part == SEGNUM2)
    {        
        seg_offset = 0x01 << ((seg_num%8) - 1);
        addr = VfdSegAddr[dig_num].Segaddr2;
        if(log_stat == LOG_ON)
        {
           VfdSegAddr[dig_num].CurrValue2 |= seg_offset;
        }
        if(log_stat == LOG_OFF)
        {
           VfdSegAddr[dig_num].CurrValue2 &= (0xFF-seg_offset);
        }
        val = VfdSegAddr[dig_num].CurrValue2 ;
    }
    YW_VFD_WR(addr); 
    udelay(10);
    YW_VFD_WR(val);
    VFD_CS_SET();  
    ShowContent();    
}
/*************************************************************
    函数名称:	VFD_CLEAR_Time
    函数说明:	清除时间显示
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.02        D02SH         新建
*************************************************************/
void VFD_CLEAR_Time(void)
{   
    SetDigAndSeg(9, SEGNUM1, 0x00);
    SetDigAndSeg(9, SEGNUM2, 0x00);
    SetDigAndSeg(10, SEGNUM1, 0x00);
    SetDigAndSeg(10, SEGNUM2, 0x00);
}

/*************************************************************
    函数名称:	VFD_POWER_ON
    函数说明:	上电需要显示内容
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.02        D02SH         新建
*************************************************************/
void VFD_POWER_ON(void)
{
    VFD_Show_String("POWER ON");
    //显示时间标志
    VFD_SHOW_LOG(CLOCK_AM,LOG_ON);
    VFD_SHOW_LOG(CLOCK_PM,LOG_ON);
    VFD_SHOW_LOG(CLOCK,LOG_ON);
    //显示tuner
    VFD_SHOW_LOG(SAT, LOG_ON);  
}

/*************************************************************
    函数名称:	YWPANEL_VFD_SetMode
    函数说明:	Dyata setting 设置数据传输模式
                VFDWRITEMODE Writes data to display memory
                VFDREADMODE Reads key data
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.11.19        D02SH         新建
*************************************************************/
typedef enum VFDMode_e{
    VFDWRITEMODE,
    VFDREADMODE
}VFDMode_T;

int YWPANEL_VFD_SetMode(VFDMode_T mode)
{

    int      ST_ErrCode = 0x0;
    int      data = 0;
    //模式不同对CS要求不同
    if(mode == VFDWRITEMODE)
    {
        data = 0x44; 
        VFD_CS_CLR();
        YW_VFD_WR(data);
        VFD_CS_SET();
    }
    else if(mode == VFDREADMODE)
    {
        data = 0x46;
        YW_VFD_WR(data);
        udelay(5);
    }
    return ST_ErrCode;
}

/*****************************************************************************/
//	函数名称:	YWPANEL_VFD_GetScanKey
//	函数说明:	add for GPIO scan fp key
//	算法说明:	NA
//	输入参数:	NA
//	输出参数:	NA
//	返 回 值:	NA
//	修改记录:	日       期      作      者       修 定
//           	---------       ----------      -------
//           	2009.09.11        D02SH          新 建
/*****************************************************************************/
int YWPANEL_VFD_GetScanKey(int *key)
{
    int key_val[6] ;
    int i = 0;
    VFD_CS_CLR();
    YWPANEL_VFD_SetMode(VFDREADMODE);
 
    for (i = 0; i < 6; i++)
    {
    	key_val[i] = YW_VFD_RD();
        //printf("Key_val[%d] = [0x%2x] \n",i,key_val[i]);
    }
    VFD_CS_SET();
    //---------转回写显示区模式
    YWPANEL_VFD_SetMode(VFDWRITEMODE);
    *key = key_val[5] ;
    return 0;
}

/*************************************************************
    函数名称:	YW_VFD_Init
    函数说明:	VFD初始化
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.01        D02SH         新建
*************************************************************/
void YW_VFD_Init(void)
{
//    printf("Not combo!!\n");
     //设置为13dig ----15seg
    VFD_CS_CLR(); 
    YW_VFD_WR(0x0C);
    VFD_CS_SET();
    //初始化为写模式
    VFD_CS_CLR();
    YW_VFD_WR(0x44);
    VFD_CS_SET();
    //初始化地址值
    SegAddrInit();
     //清空显示缓存
    VFD_ClearAll(); 
    ShowContent();
    VFD_Show_String("BOOT");  
}

/*************************************************************
    函数名称:	VFD_U_MENU
    函数说明:	进入升级菜单
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.02        D02SH         新建
*************************************************************/
void VFD_U_MENU(void)
{
    //VFD_ClearAll();
    VFD_Show_String("UP-MENU");
}
/*************************************************************
    函数名称:	VFD_U_BOOT
    函数说明:	升级ＵＢＯＯＴ显示的内容
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.02        D02SH         新建
*************************************************************/
void VFD_U_BOOT(void)
{
    //VFD_ClearAll();
    VFD_Show_String("U-BOOT");
}
/*************************************************************
    函数名称:	VFD_U_Kernel
    函数说明:	升级内核需要显示的内容
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.02        D02SH         新建
*************************************************************/
void VFD_U_Kernel(void)
{
    //VFD_ClearAll();
    VFD_Show_String("U-KERNEL");    
}
/*************************************************************
    函数名称:	VFD_Warn
    函数说明:	警告时需要显示的内容
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.02        D02SH         新建
*************************************************************/
void VFD_Warn(char* str)
{
    VFD_SHOW_LOG(ALERT,LOG_ON);
    VFD_Show_String(str);
    udelay(5000);
    VFD_SHOW_LOG(ALERT,LOG_OFF);
    udelay(5000);
    VFD_SHOW_LOG(ALERT,LOG_ON);
}

/*************************************************************
    函数名称:	VFD_Print
    函数说明:	ＶＦＤ打印函数
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.03        D02SH         新建
*************************************************************/
void VFD_Print(char* str)
{
    VFD_Show_String(str);
}
/*************************************************************
    函数名称:	VFD_BOOT_P
    函数说明:	显示升级ＵＢＯＯＴ的相应进度
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.03        D02SH         新建
*************************************************************/
void VFD_BOOT_P(int pro_rate)
{
    char str[16];
    sprintf(str, "%s%d",show_p_boot,pro_rate);    
    VFD_Show_String(str);
}

void VFD_KERNEL_P(int pro_rate)
{
    char str[16];
    sprintf(str, "%s%d",show_p_kern,pro_rate);
    VFD_Show_String(str);
}

void VFD_ROOTFS_P(int pro_rate)
{
    char str[16];
    sprintf(str, "%s%d",show_p_root,pro_rate);
    VFD_Show_String(str);
}
#else
/* data type definitions */
#define U32 unsigned long
#define S32 signed long
#define I32 long
#define U16 unsigned short
#define S16 signed short
#define I16 short
#define U8 unsigned char
#define S8 signed char
#define I8 char
#define BOOL int

typedef enum YWPANEL_DataType_e
{
    YWPANEL_DATATYPE_LBD = 0x01,
    YWPANEL_DATATYPE_LCD,
    YWPANEL_DATATYPE_LED,
    YWPANEL_DATATYPE_VFD,
    YWPANEL_DATATYPE_SCANKEY,
    YWPANEL_DATATYPE_IRKEY,

    YWPANEL_DATATYPE_GETVERSION,
    
    YWPANEL_DATATYPE_GETCPUSTATE,
    YWPANEL_DATATYPE_SETCPUSTATE,
// D02SH 2009/05/21 add begin
//Description:add for vfd state
    YWPANEL_DATATYPE_GETVFDSTATE,
    YWPANEL_DATATYPE_SETVFDSTATE,

    YWPANEL_DATATYPE_GETPOWERONSTATE,
    YWPANEL_DATATYPE_SETPOWERONSTATE,
    
    YWPANEL_DATATYPE_SETSTARTUPSTATE,
    
// D02SH 2009/05/21 add end
   
    
    YWPANEL_DATATYPE_GETSTBYKEY1,
    YWPANEL_DATATYPE_GETSTBYKEY2,
    YWPANEL_DATATYPE_GETSTBYKEY3,
    YWPANEL_DATATYPE_GETSTBYKEY4,
    YWPANEL_DATATYPE_GETSTBYKEY5,
    YWPANEL_DATATYPE_SETSTBYKEY1,
    YWPANEL_DATATYPE_SETSTBYKEY2,
    YWPANEL_DATATYPE_SETSTBYKEY3,
    YWPANEL_DATATYPE_SETSTBYKEY4,
    YWPANEL_DATATYPE_SETSTBYKEY5,
    
// D02SH 2009/05/20 add begin
//Description:for blue key
    YWPANEL_DATATYPE_GETBLUEKEY1,
    YWPANEL_DATATYPE_GETBLUEKEY2,
    YWPANEL_DATATYPE_GETBLUEKEY3,
    YWPANEL_DATATYPE_GETBLUEKEY4,
    YWPANEL_DATATYPE_GETBLUEKEY5,
    YWPANEL_DATATYPE_SETBLUEKEY1,
    YWPANEL_DATATYPE_SETBLUEKEY2,
    YWPANEL_DATATYPE_SETBLUEKEY3,
    YWPANEL_DATATYPE_SETBLUEKEY4,
    YWPANEL_DATATYPE_SETBLUEKEY5,
// D02SH 2009/05/20 add end

    YWPANEL_DATATYPE_GETIRCODE,
    YWPANEL_DATATYPE_SETIRCODE,

    YWPANEL_DATATYPE_GETENCRYPTMODE,    /*读取加密模式*/
    YWPANEL_DATATYPE_SETENCRYPTMODE,    /*设置加密模式*/
    YWPANEL_DATATYPE_GETENCRYPTKEY,       /*读取加密密钥*/
    YWPANEL_DATATYPE_SETENCRYPTKEY,       /*设置加密密钥*/  

    YWPANEL_DATATYPE_GETVERIFYSTATE,     /*读取校验状态*/
    YWPANEL_DATATYPE_SETVERIFYSTATE,     /*读取校验状态*/

    YWPANEL_DATATYPE_GETTIME,                    /*读取面板时间*/
    YWPANEL_DATATYPE_SETTIME,                    /*设置面板时间*/
    YWPANEL_DATATYPE_CONTROLTIMER,          /*控制计时器开始计时or 停止计时*/
    
    YWPANEL_DATATYPE_SETPOWERONTIME,           /*设置待机时间(设置为0xffffffff时为关闭计时)*/ 
    YWPANEL_DATATYPE_GETPOWERONTIME,

    YWPANEL_DATATYPE_NUM
}YWPANEL_DataType_t;

typedef struct YWPANEL_LBDData_s
{
    U8  value; /*8位分别代表各个灯*/
}YWPANEL_LBDData_t;

typedef struct YWPANEL_LEDData_s
{
    U8  led1; 
    U8  led2;
    U8  led3;
    U8  led4;
}YWPANEL_LEDData_t;

typedef struct YWPANEL_LCDData_s
{
    U8  value; 
}YWPANEL_LCDData_t;

typedef enum YWPANEL_VFDDataType_e
{
    YWPANEL_VFD_SETTING = 0x1,
    YWPANEL_VFD_DISPLAY,
    YWPANEL_VFD_READKEY,
    YWPANEL_VFD_DISPLAYSTRING

}YWPANEL_VFDDataType_t;


typedef struct YWPANEL_VFDData_s
{
    YWPANEL_VFDDataType_t  type; /*1- setting  2- display 3- readscankey  4-displaystring*/ 

    U8 setValue;   //if type == YWPANEL_VFD_SETTING
    
    U8 address[16];  //if type == YWPANEL_VFD_DISPLAY
    U8 DisplayValue[16];

    U8 key;  //if type == YWPANEL_VFD_READKEY
    
}YWPANEL_VFDData_t;

typedef struct YWPANEL_IRKEY_s
{
    U32 customCode;
    U32 dataCode;
}YWPANEL_IRKEY_t;

typedef struct YWPANEL_SCANKEY_s
{
    U32 keyValue;
}YWPANEL_SCANKEY_t;
typedef enum YWPANEL_CPUSTATE_s
{
    YWPANEL_CPUSTATE_UNKNOW,
    YWPANEL_CPUSTATE_RUNNING = 0x01,
    YWPANEL_CPUSTATE_STANDBY,    
}YWPANEL_CPUSTATE_t; 

typedef struct YWPANEL_CpuState_s
{
    YWPANEL_CPUSTATE_t state; 
    
}YWPANEL_CpuState_t;

typedef struct YWPANEL_StandByKey_s
{
    U32     key; 
    
}YWPANEL_StandByKey_t;

typedef enum YWPANEL_IRCODE_e
{
    YWPANEL_IRCODE_NONE,
    YWPANEL_IRCODE_NEC = 0x01,
    YWPANEL_IRCODE_RC5,
    YWPANEL_IRCODE_RC6,
    YWPANEL_IRCODE_PILIPS
}YWPANEL_IRCODE_T;

typedef struct YWPANEL_IRCode_s
{
    YWPANEL_IRCODE_T    code;
}YWPANEL_IRCode_t;


typedef enum YWPANEL_ENCRYPEMODE_e
{
    YWPANEL_ENCRYPEMODE_NONE =0x00,
    YWPANEL_ENCRYPEMODE_ODDBIT,             /*奇位取反*/
    YWPANEL_ENCRYPEMODE_EVENBIT,            /*偶位取反*/
    YWPANEL_ENCRYPEMODE_RAMDONBIT ,     /*随机位取反*/
}YWPANEL_ENCRYPEMODE_T;


typedef struct YWPANEL_EncryptMode_s
{
    YWPANEL_ENCRYPEMODE_T    mode;
    
}YWPANEL_EncryptMode_t;

typedef struct YWPANEL_EncryptKey_s
{
    U32       key;
}YWPANEL_EncryptKey_t;

typedef enum YWPANEL_VERIFYSTATE_e
{
    YWPANEL_VERIFYSTATE_NONE =0x00,
    YWPANEL_VERIFYSTATE_CRC16 ,
    YWPANEL_VERIFYSTATE_CRC32 ,
    YWPANEL_VERIFYSTATE_CHECKSUM ,

}YWPANEL_VERIFYSTATE_T;

typedef struct YWPANEL_VerifyState_s
{
    YWPANEL_VERIFYSTATE_T       state;
}YWPANEL_VerifyState_t;

typedef struct YWPANEL_Time_s
{
    U32       second;                       /*从1970年1月1日00点00分开始的秒数*/
}YWPANEL_Time_t;

typedef struct YWPANEL_ControlTimer_s
{
    BOOL            startFlag;                          // 0 - stop  1-start                    
}YWPANEL_ControlTimer_t;

typedef enum YWPANEL_LBDType_e
{
    YWPANEL_LBD_TYPE_POWER        =  ( 1 << 0 ),            /*  前面板Power灯 */
    YWPANEL_LBD_TYPE_SIGNAL        =  ( 1 << 1 ) ,           /*  前面板 Signal灯 */
    YWPANEL_LBD_TYPE_MAIL        =  ( 1 << 2 ),            /*  前面板Mail灯 */
    YWPANEL_LBD_TYPE_AUDIO        =  ( 1 << 3 )         /*  前面板Audio灯 */
}YWPANEL_LBDType_T;

typedef enum YWPAN_FP_MCUTYPE_E
{
    YWPANEL_FP_MCUTYPE_UNKNOW = 0x00,
    YWPANEL_FP_MCUTYPE_AVR_ATTING48,       //AVR MCU
    YWPANEL_FP_MCUTYPE_AVR_ATTING88,

    YWPAN_FP_MCUTYPE_MAX 
}YWPAN_FP_MCUTYPE_T;

typedef struct YWPANEL_Version_s
{
    YWPAN_FP_MCUTYPE_T  CpuType;
    
    U8  DisplayInfo;
    U8  scankeyNum;
    U8  swMajorVersion;     
    U8  swSubVersion;
    
}YWPANEL_Version_t;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef struct YWPANEL_FPData_s
{
    YWPANEL_DataType_t          dataType;

    union
    {
        YWPANEL_Version_t           version;   
        YWPANEL_LBDData_t           lbdData;
        YWPANEL_LEDData_t           ledData;
        YWPANEL_LCDData_t           lcdData;
        YWPANEL_VFDData_t           vfdData;
        YWPANEL_IRKEY_t               IrkeyData;
        YWPANEL_SCANKEY_t          ScanKeyData;
        YWPANEL_CpuState_t          CpuState;
        YWPANEL_StandByKey_t      stbyKey;
        YWPANEL_IRCode_t             irCode;
        YWPANEL_EncryptMode_t     EncryptMode;
        YWPANEL_EncryptKey_t       EncryptKey;
        YWPANEL_VerifyState_t       verifyState;
        YWPANEL_Time_t                 time;
        YWPANEL_ControlTimer_t     TimeState;
    }data;

    BOOL                                 ack;

}YWPANEL_FPData_t;


U8 YWPANEL_CharArray[]=
{
	0x7B,0x11,0x76,0x75,0x1D,0x6D,0x6F,0x31,0xFF,0x7D/* 0~9*/
};
enum 
{
    YWPANEL_INIT_INSTR_GETVERSION= 0x50,


    YWPANEL_INIT_INSTR_GETCPUSTATE = 0x52,
    YWPANEL_INIT_INSTR_SETCPUSTATE ,
    
    YWPANEL_INIT_INSTR_GETSTBYKEY1 ,
    YWPANEL_INIT_INSTR_GETSTBYKEY2 ,
    YWPANEL_INIT_INSTR_GETSTBYKEY3 ,
    YWPANEL_INIT_INSTR_GETSTBYKEY4 ,
    YWPANEL_INIT_INSTR_GETSTBYKEY5 ,

    YWPANEL_INIT_INSTR_SETSTBYKEY1 ,
    YWPANEL_INIT_INSTR_SETSTBYKEY2 ,
    YWPANEL_INIT_INSTR_SETSTBYKEY3 ,
    YWPANEL_INIT_INSTR_SETSTBYKEY4 ,
    YWPANEL_INIT_INSTR_SETSTBYKEY5 ,

    YWPANEL_INIT_INSTR_GETIRCODE , /*0x5e*/
    YWPANEL_INIT_INSTR_SETIRCODE,

    
    YWPANEL_INIT_INSTR_GETENCRYPTMODE,       /*0x60*/
    YWPANEL_INIT_INSTR_SETENCRYPTMODE,
    
    YWPANEL_INIT_INSTR_GETENCRYPTKEY,       /*0x62*/
    YWPANEL_INIT_INSTR_SETENCRYPTKEY,

    
    YWPANEL_INIT_INSTR_GETVERIFYSTATE ,       /*0x64*/
    YWPANEL_INIT_INSTR_SETVERIFYSTATE,

    YWPANEL_INIT_INSTR_GETTIME,                 /*0x66*/
    YWPANEL_INIT_INSTR_SETTIME,                 /*0x67*/
    YWPANEL_INIT_INSTR_CONTROLTIMER,                 /*0x68*/
    YWPANEL_INIT_INSTR_POWERONTIME,         /*0x69*/
    YWPANEL_INIT_INSTR_GETPOWERONTIME,         /*0x6a*/

    YWPANEL_INIT_INSTR_GETVFDSTANDBYSTATE,      /*0x6b*/
    YWPANEL_INIT_INSTR_SETVFDSTANDBYSTATE,      /*0x6c*/

    YWPANEL_INIT_INSTR_GETBLUEKEY1 ,    /*0x6d*/
    YWPANEL_INIT_INSTR_GETBLUEKEY2 ,
    YWPANEL_INIT_INSTR_GETBLUEKEY3 ,
    YWPANEL_INIT_INSTR_GETBLUEKEY4 ,    /*0x70*/
    YWPANEL_INIT_INSTR_GETBLUEKEY5 ,

    YWPANEL_INIT_INSTR_SETBLUEKEY1 ,    /*0x72*/
    YWPANEL_INIT_INSTR_SETBLUEKEY2 ,
    YWPANEL_INIT_INSTR_SETBLUEKEY3 ,
    YWPANEL_INIT_INSTR_SETBLUEKEY4 ,
    YWPANEL_INIT_INSTR_SETBLUEKEY5 ,    /*0x76*/

    YWPANEL_INIT_INSTR_GETPOWERONSTATE,      /*0x77*/
    YWPANEL_INIT_INSTR_SETPOWERONSTATE,      /*0x78*/

    YWPANEL_INIT_INSTR_GETSTARTUPSTATE,      /*0x79*/
    
};
enum YWPANL_READ_INSTR_e
{
    YWPANEL_READ_INSTR_ACK = 0x10, 
    YWPANEL_READ_INSTR_SCANKEY = 0x11,
    YWPANEL_READ_INSTR_IRKEY = 0x12,
    YWPANEL_READ_INSTR_VFDKEY = 0x13,

};

enum YWPANL_WRITE_INSTR_e
{
    YWPANEL_DISPLAY_INSTR_LBD = 0x30,
    YWPANEL_DISPLAY_INSTR_LED,
    YWPANEL_DISPLAY_INSTR_LCD,
    YWPANEL_DISPLAY_INSTR_VFD

};
#define YWPANEL_FP_INFO_MAX_LENGTH         (10)             /*读指令最大长度*/
#define YWPANEL_FP_DATA_MAX_LENGTH        (38)             /*写指令最大长度*/

typedef struct YWPANEL_I2CData_s
{
    U8                                          writeBuffLen;
    U8                                          writeBuff[YWPANEL_FP_DATA_MAX_LENGTH];
    
    U8                                          readBuff[YWPANEL_FP_INFO_MAX_LENGTH]; /*I2C返回的缓冲*/

}YWPANEL_I2CData_t;

// 注意：因最高位一定为“1”，故略去
const U16 cnCRC_16 = 0x8005;
// CRC-16 = X16 + X15 + X2 + X0
const U16 cnCRC_CCITT = 0x1021;
// CRC-CCITT = X16 + X12 + X5 + X0，据说这个 16 位 CRC 多项式比上一个要好

U32 Table_CRC[256]; // CRC 表
// 构造 16 位 CRC 表
void YWPANEL_BuildTable16( U16 aPoly )
{
    U16 i, j;
    U16 nData;
    U16 nAccum;
    for ( i = 0; i < 256; i++ )
    {
        nData = ( U16 )( i << 8 );
        nAccum = 0;
        for ( j = 0; j < 8; j++ )
        {
            if ( ( nData ^ nAccum ) & 0x8000 )
                nAccum = ( nAccum << 1 ) ^ aPoly;
            else
                nAccum <<= 1;
            nData <<= 1;
        }
        Table_CRC[i] = ( U32 )nAccum;
     }
}
// 计算 16 位 CRC 值，CRC-16 或 CRC-CCITT
U16 YWPANEL_GenerateCRC16( U8 * buffer, U32 bufLength )
{
    U32 i;
    U16 nAccum = 0;
    YWPANEL_BuildTable16( cnCRC_CCITT ); // or cnCRC_CCITT
    for ( i = 0; i < bufLength; i++ )
        nAccum = ( nAccum << 8 ) ^ ( U16 )Table_CRC[( nAccum >> 8 ) ^ *buffer++];
    return nAccum;
}

BOOL YWPANEL_FP_SetI2cData(YWPANEL_FPData_t  *data,YWPANEL_I2CData_t   *I2CData)
{
    U16             usCRC16 = 0;

    if((data == NULL) 
        ||(I2CData == NULL)
        ||(data->dataType < YWPANEL_DATATYPE_LBD)
        ||(data->dataType > YWPANEL_DATATYPE_NUM))
    {
//        printf("bad parameter\n");
        return FALSE;
    }
//    //printf(TRACE_INFO,"%s::date->dateType=[0x%x]\n",__FUNCTION__,data->dataType);
    /*设置指令类型*/
    switch(data->dataType)
    {
        case YWPANEL_DATATYPE_LBD:
        {
            I2CData->writeBuff[0] = YWPANEL_DISPLAY_INSTR_LBD;
        }
        break;
        
        case YWPANEL_DATATYPE_LCD:
        {
            I2CData->writeBuff[0] = YWPANEL_DISPLAY_INSTR_LED;
        }
        break;
        
        case YWPANEL_DATATYPE_LED:
        {
            I2CData->writeBuff[0] = YWPANEL_DISPLAY_INSTR_LCD;
        }
        break;
    
        case YWPANEL_DATATYPE_VFD:
        {
            I2CData->writeBuff[0] = YWPANEL_DISPLAY_INSTR_VFD;
        }
        break;
        
        case YWPANEL_DATATYPE_SCANKEY:
        {
            I2CData->writeBuff[0] = YWPANEL_READ_INSTR_SCANKEY;
        }
        break;
        
        case YWPANEL_DATATYPE_IRKEY:
        {
            I2CData->writeBuff[0] = YWPANEL_READ_INSTR_IRKEY;
        }
        break;
        
        case  YWPANEL_DATATYPE_GETVERSION:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETVERSION;
        }
        break;

        case  YWPANEL_DATATYPE_GETCPUSTATE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETCPUSTATE;
        }
        break;
        
        case  YWPANEL_DATATYPE_SETCPUSTATE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETCPUSTATE;
        }
        break;
        
        case  YWPANEL_DATATYPE_SETSTARTUPSTATE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETSTARTUPSTATE;
        }
        break;
        case  YWPANEL_DATATYPE_GETVFDSTATE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETVFDSTANDBYSTATE;
        }
        break;
        
        case  YWPANEL_DATATYPE_SETVFDSTATE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETVFDSTANDBYSTATE;
        }
        break;

        case  YWPANEL_DATATYPE_GETPOWERONSTATE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETPOWERONSTATE;
        }
        break;
        
        case  YWPANEL_DATATYPE_SETPOWERONSTATE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETPOWERONSTATE;
        }
        break;

        case YWPANEL_DATATYPE_GETSTBYKEY1:
        case YWPANEL_DATATYPE_GETSTBYKEY2:
        case YWPANEL_DATATYPE_GETSTBYKEY3:
        case YWPANEL_DATATYPE_GETSTBYKEY4:
        case YWPANEL_DATATYPE_GETSTBYKEY5:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETSTBYKEY1 + (data->dataType - YWPANEL_DATATYPE_GETSTBYKEY1);
        }
        break;
        
        case    YWPANEL_DATATYPE_SETSTBYKEY1:
        case    YWPANEL_DATATYPE_SETSTBYKEY2:
        case    YWPANEL_DATATYPE_SETSTBYKEY3:
        case    YWPANEL_DATATYPE_SETSTBYKEY4:
        case    YWPANEL_DATATYPE_SETSTBYKEY5:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETSTBYKEY1+data->dataType - YWPANEL_DATATYPE_SETSTBYKEY1;
        }        
        break;
 //add for blue key      
        case YWPANEL_DATATYPE_GETBLUEKEY1:
        case YWPANEL_DATATYPE_GETBLUEKEY2:
        case YWPANEL_DATATYPE_GETBLUEKEY3:
        case YWPANEL_DATATYPE_GETBLUEKEY4:
        case YWPANEL_DATATYPE_GETBLUEKEY5:
        {
          I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETBLUEKEY1 + (data->dataType - YWPANEL_DATATYPE_GETBLUEKEY1);
        }
        break;

        case    YWPANEL_DATATYPE_SETBLUEKEY1:
        case    YWPANEL_DATATYPE_SETBLUEKEY2:
        case    YWPANEL_DATATYPE_SETBLUEKEY3:
        case    YWPANEL_DATATYPE_SETBLUEKEY4:
        case    YWPANEL_DATATYPE_SETBLUEKEY5:
        {
          I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETBLUEKEY1+data->dataType - YWPANEL_DATATYPE_SETBLUEKEY1;
        }        
        break;
//add end
        case    YWPANEL_DATATYPE_GETIRCODE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETIRCODE;
        }
        break;

          
        case    YWPANEL_DATATYPE_SETIRCODE:
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETIRCODE;
        }
        break;

        case    YWPANEL_DATATYPE_GETENCRYPTMODE:    /*读取加密模式*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETENCRYPTMODE;
        }
        break;

        case    YWPANEL_DATATYPE_SETENCRYPTMODE:  /*设置加密模式*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETENCRYPTMODE;
        }
        break;
   
        case    YWPANEL_DATATYPE_GETENCRYPTKEY:      /*读取加密密钥*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETENCRYPTKEY;
        }
        break;

        case    YWPANEL_DATATYPE_SETENCRYPTKEY:       /*设置加密密钥*/  
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETENCRYPTKEY;
        }
        break;

        case   YWPANEL_DATATYPE_GETVERIFYSTATE:     /*读取校验状态*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETVERIFYSTATE;
        }
        break;

        case    YWPANEL_DATATYPE_SETVERIFYSTATE:    /*读取校验状态*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETVERIFYSTATE;
        }
        break;

        case    YWPANEL_DATATYPE_GETTIME:                    /*读取面板时间*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETTIME;
        }
        break;
        
        case    YWPANEL_DATATYPE_SETTIME:                  /*设置面板时间*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_SETTIME;
        }
        break;
        
        case    YWPANEL_DATATYPE_CONTROLTIMER:         /*控制计时器开始计时or 停止计时*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_CONTROLTIMER;
        }
        break;
        
        case    YWPANEL_DATATYPE_SETPOWERONTIME:         /*设置定时关机的时间*/
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_POWERONTIME;
        }
        break;
        case    YWPANEL_DATATYPE_GETPOWERONTIME:         
        {
            I2CData->writeBuff[0] = YWPANEL_INIT_INSTR_GETPOWERONTIME;
        }
        break;
        default:
        break;
        
    }

    /*设置指令的长度*/   
    switch(data->dataType)
    {
        case YWPANEL_DATATYPE_VFD:
        {
            if(data->data.vfdData.type == YWPANEL_VFD_DISPLAYSTRING)
            {
                I2CData->writeBuff[1] = 0x22;     /*指令的长度 = 数据长度+指令类型长度*/
            }
            else
            {
                I2CData->writeBuff[1] = 0x4;     
            }
        }
        break;
        
        default:
        {
            I2CData->writeBuff[1] = 0x4;
        }
        break;
    }
    /*设置指令数据*/
    switch(data->dataType)
    {
        case YWPANEL_DATATYPE_LBD:
        {
            I2CData->writeBuff[2] = data->data.lbdData.value;
        }
        break;
        
        case YWPANEL_DATATYPE_LCD:
        {
            I2CData->writeBuff[2] = data->data.lcdData.value;
        }
        break;
        
        case YWPANEL_DATATYPE_LED:
        {
            I2CData->writeBuff[2] = data->data.ledData.led1;
            I2CData->writeBuff[3] = data->data.ledData.led2;
            I2CData->writeBuff[4] = data->data.ledData.led3;
            I2CData->writeBuff[5] = data->data.ledData.led4;
        }
        break;
    
        case YWPANEL_DATATYPE_VFD:
        {
            I2CData->writeBuff[2] = data->data.vfdData.type;
            switch(data->data.vfdData.type)
            {
                case YWPANEL_VFD_SETTING:
                {
                    I2CData->writeBuff[3] = data->data.vfdData.setValue;
                }
                break;
                case YWPANEL_VFD_DISPLAY:
                {
                    I2CData->writeBuff[3] = data->data.vfdData.address[0];
                    I2CData->writeBuff[4] = data->data.vfdData.DisplayValue[0];
                }
                break;
                case YWPANEL_VFD_READKEY:
                {
                    I2CData->writeBuff[3] = data->data.vfdData.key;
                }
                break;
                case YWPANEL_VFD_DISPLAYSTRING:
                {
                    int i;
                    for(i=0; i<16;i++)
                    {
                        I2CData->writeBuff[4+2*i] = data->data.vfdData.address[i];
                        I2CData->writeBuff[4+2*i+1] = data->data.vfdData.DisplayValue[i];
                    }
                }
                break;
            }
        }
        break;

        case YWPANEL_DATATYPE_SETCPUSTATE:
        {
            I2CData->writeBuff[2] = data->data.CpuState.state;
        }
        break;
        
        case YWPANEL_DATATYPE_SETSTARTUPSTATE:
        {
            I2CData->writeBuff[2] = data->data.CpuState.state;
        }
        break;
        
        case YWPANEL_DATATYPE_SETVFDSTATE:
        {
           I2CData->writeBuff[2] = data->data.CpuState.state;
        }
        break;
        
        case YWPANEL_DATATYPE_SETPOWERONSTATE:
        {
            I2CData->writeBuff[2] = data->data.CpuState.state;
        }
        break;

        case YWPANEL_DATATYPE_SETSTBYKEY1:
        case YWPANEL_DATATYPE_SETSTBYKEY2:
        case YWPANEL_DATATYPE_SETSTBYKEY3:
        case YWPANEL_DATATYPE_SETSTBYKEY4:
        case YWPANEL_DATATYPE_SETSTBYKEY5:
        {
            I2CData->writeBuff[2] = (U8) ((data->data.stbyKey.key>>24)&0xff);
            I2CData->writeBuff[3] = (U8) ((data->data.stbyKey.key >>16)&0xff);
            I2CData->writeBuff[4] = (U8) ((data->data.stbyKey.key >>8)&0xff);
            I2CData->writeBuff[5] = (U8) (data->data.stbyKey.key&0xff);
        }
        break;
//add for blue key        
        case YWPANEL_DATATYPE_SETBLUEKEY1:
        case YWPANEL_DATATYPE_SETBLUEKEY2:
        case YWPANEL_DATATYPE_SETBLUEKEY3:
        case YWPANEL_DATATYPE_SETBLUEKEY4:
        case YWPANEL_DATATYPE_SETBLUEKEY5:
        {
            I2CData->writeBuff[2] = (U8) ((data->data.stbyKey.key>>24)&0xff);
            I2CData->writeBuff[3] = (U8) ((data->data.stbyKey.key >>16)&0xff);
            I2CData->writeBuff[4] = (U8) ((data->data.stbyKey.key >>8)&0xff);
            I2CData->writeBuff[5] = (U8) (data->data.stbyKey.key&0xff);
        }
        break;
//add end
        case YWPANEL_DATATYPE_SETIRCODE:
        {
            I2CData->writeBuff[2] =  data->data.irCode.code;
        }
        break;

        case YWPANEL_DATATYPE_SETENCRYPTMODE:
        {
            I2CData->writeBuff[2] =  data->data.EncryptMode.mode;
        }
        break;

        case YWPANEL_DATATYPE_SETENCRYPTKEY:
        {
            I2CData->writeBuff[2] = (U8) ((data->data.EncryptKey.key>>24)&0xff);
            I2CData->writeBuff[3] = (U8) ((data->data.EncryptKey.key >>16)&0xff);
            I2CData->writeBuff[4] = (U8) ((data->data.EncryptKey.key >>8)&0xff);
            I2CData->writeBuff[5] = (U8) (data->data.EncryptKey.key&0xff);
        }
        break;

        case YWPANEL_DATATYPE_SETVERIFYSTATE:
        {
            I2CData->writeBuff[2] = data->data.verifyState.state;
        }
        break;

        case YWPANEL_DATATYPE_SETTIME:
        {            
            I2CData->writeBuff[2] = (U8) ((data->data.time.second>>24)&0xff);
            I2CData->writeBuff[3] = (U8) ((data->data.time.second >>16)&0xff);
            I2CData->writeBuff[4] = (U8) ((data->data.time.second >>8)&0xff);
            I2CData->writeBuff[5] = (U8) (data->data.time.second&0xff);
        }
        break;

        case YWPANEL_DATATYPE_CONTROLTIMER:
        {            
            I2CData->writeBuff[2] = data->data.TimeState.startFlag;
        }
        break;

        case YWPANEL_DATATYPE_SETPOWERONTIME:
        {
            I2CData->writeBuff[2] = (U8) ((data->data.time.second>>24)&0xff);
            I2CData->writeBuff[3] = (U8) ((data->data.time.second >>16)&0xff);
            I2CData->writeBuff[4] = (U8) ((data->data.time.second >>8)&0xff);
            I2CData->writeBuff[5] = (U8) (data->data.time.second&0xff);
        }
        break;

        default:
        break;   
    }

    /*设置CRC16 连指令ID一起校验*/
    switch(data->dataType)
    {
        case YWPANEL_DATATYPE_VFD:
        {
            if(data->data.vfdData.type == YWPANEL_VFD_DISPLAYSTRING)
            {
                usCRC16 = YWPANEL_GenerateCRC16(I2CData->writeBuff, 36);
                I2CData->writeBuff[36] =  (usCRC16 &0xff);
                I2CData->writeBuff[37] =  ((usCRC16>>8) &0xff);
                I2CData->writeBuffLen = 38;
            }
            else
            {
                usCRC16 = YWPANEL_GenerateCRC16(I2CData->writeBuff, 6);
                I2CData->writeBuff[6] =  (usCRC16 &0xff);
                I2CData->writeBuff[7] =  ((usCRC16>>8) &0xff);
                I2CData->writeBuffLen = 8;
            }
        }
        break;
        
        default:
        {
            usCRC16 = YWPANEL_GenerateCRC16(I2CData->writeBuff, 6);
            I2CData->writeBuff[6] =  (usCRC16 &0xff);
            I2CData->writeBuff[7] =  ((usCRC16>>8) &0xff);
            I2CData->writeBuffLen = 8;
        }
        break;
    }

    return TRUE;
}

BOOL YWPANEL_FP_ParseI2cData(YWPANEL_FPData_t  *data,YWPANEL_I2CData_t   *I2CData)
{
    U16     crc16Code = 0;
    U16     receiveCode = 0;

    U8       dataType;
    U8       datalength;

    if((data == NULL) ||(I2CData == NULL))
    {
//        printf("%s::error @%d\n",__FUNCTION__,__LINE__);
        return FALSE;
    }
    receiveCode =((U16)(I2CData->readBuff[7]<<8)&0xff00) |((U16)(I2CData->readBuff[6])&0xff);
    crc16Code = YWPANEL_GenerateCRC16(I2CData->readBuff, 6);

    if(receiveCode != crc16Code )
    {
        //printf("check crc16 is wrong! at %d \n",__LINE__);
        //return FALSE;
    }
    
//    //printf(TRACE_INFO,"%s::date->dateType=[0x%x]\n",__FUNCTION__,data->dataType);
    dataType = I2CData->readBuff[0];    
    datalength = I2CData->readBuff[1];
    
	//zy 2008-10-07
	switch(data->dataType)
    {
        case YWPANEL_DATATYPE_LBD:
        case YWPANEL_DATATYPE_LCD:
        case YWPANEL_DATATYPE_LED:
        case YWPANEL_DATATYPE_SCANKEY:
        case YWPANEL_DATATYPE_SETCPUSTATE:
        case YWPANEL_DATATYPE_SETVFDSTATE: 
        case YWPANEL_DATATYPE_SETPOWERONSTATE:    
        case YWPANEL_DATATYPE_SETSTBYKEY1:
        case YWPANEL_DATATYPE_SETSTBYKEY2:
        case YWPANEL_DATATYPE_SETSTBYKEY3:
        case YWPANEL_DATATYPE_SETSTBYKEY4:
        case YWPANEL_DATATYPE_SETSTBYKEY5:
//add for blue key
        case YWPANEL_DATATYPE_SETBLUEKEY1:
        case YWPANEL_DATATYPE_SETBLUEKEY2:
        case YWPANEL_DATATYPE_SETBLUEKEY3:
        case YWPANEL_DATATYPE_SETBLUEKEY4:
        case YWPANEL_DATATYPE_SETBLUEKEY5: 
//add end            
        case YWPANEL_DATATYPE_SETIRCODE:
        case YWPANEL_DATATYPE_SETENCRYPTMODE:    /*设置加密模式*/
        case YWPANEL_DATATYPE_SETENCRYPTKEY:       /*设置加密密钥*/  
        case YWPANEL_DATATYPE_SETVERIFYSTATE:     /*读取校验状态*/
        case YWPANEL_DATATYPE_SETTIME:                   /*设置面板时间*/
        case YWPANEL_DATATYPE_CONTROLTIMER:          /*控制计时器开始计时or 停止计时*/
        case YWPANEL_DATATYPE_SETPOWERONTIME:           /*设置待机时间(设置为0xffffffff时为关闭计时)*/ 
        {
            if(dataType != YWPANEL_READ_INSTR_ACK)
            {                
//                printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                return FALSE;
            }
        }
        break;
        
        case YWPANEL_DATATYPE_VFD:
        {
            if(data->data.vfdData.type == YWPANEL_VFD_READKEY)
            {
                if(dataType != YWPANEL_READ_INSTR_VFDKEY)
                {
//                    printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                    return FALSE;
                }
            }
            else 
            {
                if(dataType != YWPANEL_READ_INSTR_ACK)
                {
//                    printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                    return FALSE;
                }
            }
        }
        break;

        case YWPANEL_DATATYPE_GETSTBYKEY1:
        case YWPANEL_DATATYPE_GETSTBYKEY2:
        case YWPANEL_DATATYPE_GETSTBYKEY3:
        case YWPANEL_DATATYPE_GETSTBYKEY4:
        case YWPANEL_DATATYPE_GETSTBYKEY5:
        {
            if(dataType != (YWPANEL_INIT_INSTR_GETSTBYKEY1+ data->dataType -YWPANEL_DATATYPE_GETSTBYKEY1))
            {
//                printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                return FALSE;
            } 
        }
        break;
       
		case YWPANEL_DATATYPE_GETBLUEKEY1:
        case YWPANEL_DATATYPE_GETBLUEKEY2:
        case YWPANEL_DATATYPE_GETBLUEKEY3:
        case YWPANEL_DATATYPE_GETBLUEKEY4:
        case YWPANEL_DATATYPE_GETBLUEKEY5:
        {
            if(dataType != (YWPANEL_INIT_INSTR_GETBLUEKEY1+ data->dataType -YWPANEL_DATATYPE_GETBLUEKEY1))
            {
//                printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                return FALSE;
            } 
        }
        break;
        case YWPANEL_DATATYPE_GETTIME:
        {
            if(dataType != YWPANEL_INIT_INSTR_GETTIME)
            {
//                printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                return FALSE;
            } 
        }
        break;
        case YWPANEL_DATATYPE_GETPOWERONTIME:     
        {
            if(dataType != YWPANEL_INIT_INSTR_GETPOWERONTIME)
            {   
//                printf("dateType=[0x%x]###\n",dataType);
//                printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                return FALSE;
            } 
        }
        break;
        
        default:
        break;
    }

    
    switch(dataType)
    {
        case YWPANEL_READ_INSTR_ACK:  //ACK
        {
            data->ack = TRUE;
        }
        break;

        case YWPANEL_READ_INSTR_SCANKEY:  //scan key
        {
            data->data.ScanKeyData.keyValue= I2CData->readBuff[2];
            data->ack = TRUE;
        }
        break;

        case YWPANEL_READ_INSTR_IRKEY:
        {
            data->data.IrkeyData.customCode = ((I2CData->readBuff[3] <<8)&0xff00)|(I2CData->readBuff[2]);
            data->data.IrkeyData.dataCode = ((I2CData->readBuff[5] <<8)&0xff00)|(I2CData->readBuff[4]);
            data->ack = TRUE;
        }
        break;
        
        case YWPANEL_READ_INSTR_VFDKEY:
        {
            data->data.vfdData.key = I2CData->readBuff[2];
            data->ack = TRUE;
        }
        break;    

        case YWPANEL_INIT_INSTR_GETVERSION: /*get version */
        {
            if(data->dataType != YWPANEL_DATATYPE_GETVERSION)
            {                
//                printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                return FALSE;
            }
            data->data.version.CpuType = I2CData->readBuff[2];
            data->data.version.DisplayInfo = (I2CData->readBuff[3]>>4)&0x0f;
            data->data.version.scankeyNum = I2CData->readBuff[3]&0x0f;
            data->data.version.swMajorVersion = I2CData->readBuff[4];
            data->data.version.swMajorVersion = I2CData->readBuff[5];

            data->ack = TRUE;
        }
        break;  

        case YWPANEL_INIT_INSTR_GETCPUSTATE: /*get cpu state*/
        {
            if(data->dataType == YWPANEL_DATATYPE_GETCPUSTATE)
            {
                data->data.CpuState.state= I2CData->readBuff[2];
                data->ack = TRUE;
            }
            else
            {
//                printf("%s::error @%d\n",__FUNCTION__,__LINE__);
                return FALSE;
            }
        }
        break;        

        case YWPANEL_INIT_INSTR_GETVFDSTANDBYSTATE: /*get vfd state*/
        {
           if(data->dataType == YWPANEL_DATATYPE_GETVFDSTATE)
           {
               data->data.CpuState.state= I2CData->readBuff[2];
               data->ack = TRUE;
           }
           else
           {
//               printf("%s::error @%d\n",__FUNCTION__,__LINE__);
               return FALSE;
           }
        }
        break;    
        case YWPANEL_INIT_INSTR_GETPOWERONSTATE: /*get power on  state*/
        {
           if(data->dataType == YWPANEL_DATATYPE_GETPOWERONSTATE)
           {
               data->data.CpuState.state= I2CData->readBuff[2];
               data->ack = TRUE;
           }
           else
           {
//               printf("%s::error @%d\n",__FUNCTION__,__LINE__);
               return FALSE;
           }
        }
        break;  

        
        case YWPANEL_INIT_INSTR_GETSTBYKEY1: /*get standby key*/
        case YWPANEL_INIT_INSTR_GETSTBYKEY2: /*get standby key*/
        case YWPANEL_INIT_INSTR_GETSTBYKEY3: /*get standby key*/
        case YWPANEL_INIT_INSTR_GETSTBYKEY4: /*get standby key*/
        case YWPANEL_INIT_INSTR_GETSTBYKEY5: /*get standby key*/
        {
            data->data.stbyKey.key = ((I2CData->readBuff[2]<<24)&0xff000000)
                                                |((I2CData->readBuff[3]<<16)&0xff0000)
                                                |((I2CData->readBuff[4]<<8)&0xff00)
                                                |((I2CData->readBuff[5])&0xff);
            data->ack = TRUE;
        }
        break;    
        case YWPANEL_INIT_INSTR_GETBLUEKEY1: /*get blue key*/
        case YWPANEL_INIT_INSTR_GETBLUEKEY2: /*get blue key*/
        case YWPANEL_INIT_INSTR_GETBLUEKEY3: /*get blue key*/
        case YWPANEL_INIT_INSTR_GETBLUEKEY4: /*get blue key*/
        case YWPANEL_INIT_INSTR_GETBLUEKEY5: /*get blue key*/
        {
            data->data.stbyKey.key = ((I2CData->readBuff[2]<<24)&0xff000000)
                                                |((I2CData->readBuff[3]<<16)&0xff0000)
                                                |((I2CData->readBuff[4]<<8)&0xff00)
                                                |((I2CData->readBuff[5])&0xff);
            data->ack = TRUE;
        }
        break;  
        case YWPANEL_INIT_INSTR_GETIRCODE: /*get ir protocoll*/
        {
            data->data.irCode.code = I2CData->readBuff[2];
        }
        break;

        case YWPANEL_INIT_INSTR_GETENCRYPTMODE: /*get encrypt mode */
        {
            data->data.EncryptMode.mode = I2CData->readBuff[2];
        }
        break;

        case YWPANEL_INIT_INSTR_GETENCRYPTKEY: /*get encrypt key */
        {
            data->data.EncryptKey.key = (U32)I2CData->readBuff[2] |(U32) I2CData->readBuff[3]<<8
                                                 |(U32)I2CData->readBuff[4]<<16 |(U32)I2CData->readBuff[5]<<24;
        }
        break;

        case YWPANEL_INIT_INSTR_GETVERIFYSTATE: /*get verify state */
        {
            data->data.verifyState.state = I2CData->readBuff[2];
        }
        break;
        case YWPANEL_INIT_INSTR_GETPOWERONTIME:
        case YWPANEL_INIT_INSTR_GETTIME:
        {
            data->data.time.second = ((I2CData->readBuff[2]<<24)&0xff000000)
                                    |((I2CData->readBuff[3]<<16)&0xff0000)
                                    |((I2CData->readBuff[4]<<8)&0xff00)
                                    |((I2CData->readBuff[5])&0xff);
            data->ack = TRUE;
        }
        break;
            
        default:
        {
//            printf("%s::error @%d\n",__FUNCTION__,__LINE__);
            return FALSE;
        }
    }

    return TRUE;
}
#define COMBO_I2C_ADDR (0x50 >> 1)
#define COMBO_I2C_OK 0
#define msleep(a) udelay(a*1000)
static BOOL YWPANEL_FPWriteDataToI2c(	U8 * writeBufer,U32 writeBufLen,
										U8 *readBuffer,	U32 readBufLen)
{
    BOOL           ret = 0;

    ret = i2c_write(COMBO_I2C_ADDR,0,0, writeBufer, writeBufLen);
    if (ret != COMBO_I2C_OK)
    {
//        printf("I2C write error for %d at %d\n",ret,__LINE__);
        return FALSE;
    }

	msleep(1);  
    
    ret = i2c_read(COMBO_I2C_ADDR,0,0 ,readBuffer,readBufLen);
    if (ret != COMBO_I2C_OK)
    {        
//        printf("I2C read error for %d at %d\n",ret,__LINE__);
        return FALSE;
    }

    return TRUE;
}

BOOL YWPANEL_FP_SendData(YWPANEL_FPData_t  *data)
{
    BOOL                ret = FALSE;
    YWPANEL_I2CData_t   I2CData;

    if(data == NULL)
    {
//        printf("bad parameter @ %d\n",__LINE__);
        return FALSE;
    }

    memset(&I2CData, 0, sizeof(I2CData));
    if(YWPANEL_FP_SetI2cData(data,&I2CData) != TRUE)
    {
//        printf("SetI2cData @ %d\n",__LINE__);
        return FALSE;
    }
    
    ret = YWPANEL_FPWriteDataToI2c( I2CData.writeBuff, I2CData.writeBuffLen,  
                                    I2CData.readBuff, YWPANEL_FP_INFO_MAX_LENGTH);
    if(ret != TRUE)
    {
//        printf("YWPANEL_FPWriteDataToI2c @ %d\n",__LINE__);
        return FALSE;
    }    
    ret = YWPANEL_FP_ParseI2cData(data, &I2CData);
    if(ret != TRUE)
    {
//        printf("YWPANEL_FP_ParseI2cData @ %d\n",__LINE__);
        return FALSE;
    } 
    return ret;
}
int YWPANEL_VFD_ShowTime(U8 hh,U8 mm)                                               
{
    int 		ret = 0;
    YWPANEL_FPData_t    data;
    U8                  digitNum1,digitNum2,temp;
//show hour
    {
        memset(&data, 0, sizeof(YWPANEL_FPData_t));

        data.dataType = YWPANEL_DATATYPE_VFD;

        digitNum2 = YWPANEL_CharArray[hh/10 ];
        digitNum1 = YWPANEL_CharArray[hh%10];

        temp = digitNum2;
        digitNum2 = (digitNum2&0xbf)|(digitNum1&0x40); 
        digitNum1 = (digitNum1&0x3c)|((temp&0x40)<<1)|((digitNum1&0x01)<<1)|((digitNum1&0x02)>>1);
        

        data.data.vfdData.type = YWPANEL_VFD_DISPLAY;
        data.data.vfdData.address[0] = VfdSegAddr[10].Segaddr2;

        data.data.vfdData.DisplayValue[0] = digitNum2;
        VfdSegAddr[10].CurrValue2 = data.data.vfdData.DisplayValue[0];

        if(YWPANEL_FP_SendData(&data) != TRUE)
        {
//            printf("YWPANEL_FP_SendData not seccussfully!![%d]\n",__LINE__);
            ret = -1;
        }

        data.data.vfdData.address[0] = VfdSegAddr[10].Segaddr1;

        data.data.vfdData.DisplayValue[0] = digitNum1;
        VfdSegAddr[10].CurrValue1= data.data.vfdData.DisplayValue[0];

        if(YWPANEL_FP_SendData(&data) != TRUE)
        {
//            printf("YWPANEL_FP_SendData not seccussfully!![%d]\n",__LINE__);
            ret = -2;
        }
    }
//show minite
    {
        
        memset(&data, 0, sizeof(YWPANEL_FPData_t));    
        data.dataType = YWPANEL_DATATYPE_VFD;
        digitNum2 = YWPANEL_CharArray[mm/10 ];
        digitNum1 = YWPANEL_CharArray[mm%10];

        temp = digitNum2;
        digitNum2 = (digitNum2&0xbf)|(digitNum1&0x40); 
        digitNum1 = (digitNum1&0x3c)|((temp&0x40)<<1)|((digitNum1&0x01)<<1)|((digitNum1&0x02)>>1);
        data.data.vfdData.type = YWPANEL_VFD_DISPLAY;
        data.data.vfdData.address[0] = VfdSegAddr[9].Segaddr2;

        data.data.vfdData.DisplayValue[0] = digitNum2;
        VfdSegAddr[9].CurrValue2 = data.data.vfdData.DisplayValue[0];

        if(YWPANEL_FP_SendData(&data) != TRUE)
        {
//            printf("YWPANEL_FP_SendData not seccussfully!![%d]\n",__LINE__);
            ret = -3;
        } 

        data.data.vfdData.address[0] = VfdSegAddr[9].Segaddr1;

        data.data.vfdData.DisplayValue[0] = digitNum1;
        VfdSegAddr[9].CurrValue1= data.data.vfdData.DisplayValue[0];

        if(YWPANEL_FP_SendData(&data) != TRUE)
        {
//            printf("YWPANEL_FP_SendData not seccussfully!![%d]\n",__LINE__);
            ret = -4;
        }
    }
    return ret;
}
int YWPANEL_VFD_SetBrightness(int level)
{
    int 		ret = 0;
    YWPANEL_FPData_t    data;    

    if(level <=0)
        level = 0;
    else if(level >= 7)
        level = 7;
    data.dataType = YWPANEL_DATATYPE_VFD;    
    data.data.vfdData.type = YWPANEL_VFD_SETTING;
    data.data.vfdData.setValue = level+0x88;
    if(YWPANEL_FP_SendData(&data) != TRUE)
    {
//        printf("SetBrightness wrong!!\n");   
        ret = -1;
    }
    return ret ;
}
int YWPANEL_VFD_ShowString(char* str)
{
    int ret = 0 ;
	U8 lenth;
 	U8 i,c;
    
    YWPANEL_FPData_t    data;

 	lenth = strlen(str);
	if(lenth > 8)
	{
        ret = -1 ;
//       printf("Bad params\n");
        return ret;
    }    
    data.dataType = YWPANEL_DATATYPE_VFD;
 	for(i = 0; i < 8; i++)
	{
        data.data.vfdData.type = YWPANEL_VFD_DISPLAYSTRING;
        if(i <lenth)
        {
            c = str[i] ;
        
            if(c >= 65 && c <= 95)
                c = c - 65;
            else if(c >= 97 && c <= 122)
                c = c - 97;
            else if(c >= 42 && c <= 57)
                c = c - 11;
            else
            {
                c = 47;         /*遇到不能显示的显示空*/
            }
            VfdSegAddr[i+1].CurrValue1 = CharLib[c][0] ;
            VfdSegAddr[i+1].CurrValue2 = CharLib[c][1] ;
        }
        else
        {
            VfdSegAddr[i+1].CurrValue1 = 0;
            VfdSegAddr[i+1].CurrValue2 = 0;
        }
        data.data.vfdData.address[2*i] = VfdSegAddr[i+1].Segaddr1;
        data.data.vfdData.DisplayValue[2*i] = VfdSegAddr[i+1].CurrValue1;
        data.data.vfdData.address[2*i+1] = VfdSegAddr[i+1].Segaddr2;
        data.data.vfdData.DisplayValue[2*i+1] = VfdSegAddr[i+1].CurrValue2;
	}
   
    if(YWPANEL_FP_SendData(&data) != TRUE)
    {
//        printf("VFD show stings is wrong!!\n");    
        ret = -2;
    }
    return ret;    
 }
int YWPANEL_VFD_ShowIco(LogNum_T log_num,int log_stat)
{
    int ret = 0 ;
    int dig_num = 0,seg_num = 0;
    SegNum_T seg_part = 0;
    U8  seg_offset = 0;
    YWPANEL_FPData_t    	data;
    
    data.dataType = YWPANEL_DATATYPE_VFD;

    //--------------------参数过滤---------------------
    if((log_num >= LogNum_Max)||(log_num < PLAY_FASTBACKWARD))
    {
        ret = -1 ;
//        printf("Bad params\n");        
        return ret;
    }
    dig_num = log_num/15;
    seg_num = log_num%15;
    seg_part = seg_num/9;   

    data.data.vfdData.type = YWPANEL_VFD_DISPLAY;
            
    if(seg_part == SEGNUM1)
	{
        seg_offset = 0x01 << ((seg_num%9) - 1);
        data.data.vfdData.address[0] = VfdSegAddr[dig_num].Segaddr1;
        if(log_stat == LOG_ON)
        {
           VfdSegAddr[dig_num].CurrValue1 |= seg_offset;
        }
        if(log_stat == LOG_OFF)
        {
           VfdSegAddr[dig_num].CurrValue1 &= (0xFF-seg_offset);
        }
        data.data.vfdData.DisplayValue[0] = VfdSegAddr[dig_num].CurrValue1 ;
	}
    else if(seg_part == SEGNUM2)
    {
        seg_offset = 0x01 << ((seg_num%8) - 1);
        data.data.vfdData.address[0] = VfdSegAddr[dig_num].Segaddr2;
        if(log_stat == LOG_ON)
        {
           VfdSegAddr[dig_num].CurrValue2 |= seg_offset;
        }
        if(log_stat == LOG_OFF)
        {
           VfdSegAddr[dig_num].CurrValue2 &= (0xFF-seg_offset);
        }
        data.data.vfdData.DisplayValue[0] = VfdSegAddr[dig_num].CurrValue2 ;
    }
   if(YWPANEL_FP_SendData(&data) != TRUE)
   {
//        printf("Show a Ico wrong!!\n");   
        ret = -2;
   }
    return ret ;
}

int YWPANEL_VFD_GetScanKey(int *key)
{
    YWPANEL_FPData_t    data; 
    int ret = 0;
    data.dataType = YWPANEL_DATATYPE_VFD;
    data.data.vfdData.type = YWPANEL_VFD_READKEY;
    if(YWPANEL_FP_SendData(&data) != TRUE)
    {
        ret = -1;
    }
    *key = data.data.vfdData.key;
    return ret;    
}

void SegAddrInit(void)
{
	int i = 0, addr = 0xC0;//adress flag
	for(i = 0; i < 13; i++)
	{
		VfdSegAddr[i + 1].CurrValue1 = 0;
		VfdSegAddr[i + 1].CurrValue2 = 0;
		VfdSegAddr[i + 1].Segaddr1 = addr;
		VfdSegAddr[i + 1].Segaddr2 = addr + 1;
		addr += 3;
	}
} 
void YW_VFD_Init(void)
{
    SegAddrInit();
    i2c_init(4000000,0x50);
    VFD_Print("BOOT");
/*  2009-06-24@14:22:46 D02SH Remark
    int i;
    for (i=10; i>0; i--)
    {
        YWPANEL_VFD_ShowIco( MP3, 1);
        msleep(200);
        YWPANEL_VFD_ShowIco( MP3, 0);
        msleep(200);
        VFD_Print("WELCOME");        
        msleep(200);
        VFD_Warn("GOODBY");
        msleep(200);        
        YWPANEL_VFD_ShowString("GOODBY");
        msleep(200);
        VFD_BOOT_P(10);        
        msleep(200);
        VFD_KERNEL_P(50);        
        msleep(200);
        VFD_ROOTFS_P(80);        
        msleep(200);
    }
*/
}

void VFD_Warn(char* str)
{
    YWPANEL_VFD_ShowIco(ALERT,LOG_ON);
    YWPANEL_VFD_ShowString(str);
    msleep(500);
    YWPANEL_VFD_ShowIco(ALERT,LOG_OFF);
    msleep(500);
    YWPANEL_VFD_ShowIco(ALERT,LOG_ON);
}
void VFD_Print(char* str)
{
    YWPANEL_VFD_ShowString(str);
}
/*************************************************************
    函数名称:	VFD_BOOT_P
    函数说明:	显示升级ＵＢＯＯＴ的相应进度
    算法说明:	无
    调用说明:   Calls                         	Called By
               ------                         ------------
                AAAAA()                        BBBBB()
    输入参数:	
    输出参数:	
    返 回 值:	
    修改记录:	日       期      作      者     修定
                ---------        ---------      -----
                2008.12.03        D02SH         新建
*************************************************************/
void VFD_BOOT_P(int pro_rate)
{
    char str[16];
    sprintf(str, "%s%d",show_p_boot,pro_rate);    
    YWPANEL_VFD_ShowString(str);
}

void VFD_KERNEL_P(int pro_rate)
{
    char str[16];
    sprintf(str, "%s%d",show_p_kern,pro_rate);
    YWPANEL_VFD_ShowString(str);
}

void VFD_ROOTFS_P(int pro_rate)
{
    char str[16];
    sprintf(str, "%s%d",show_p_root,pro_rate);
    YWPANEL_VFD_ShowString(str);
}
void VFD_BOOT(void)
{
       YWPANEL_VFD_ShowString("BOOT");   
}
void VFD_U_MENU(void)
{
    //VFD_ClearAll();
    YWPANEL_VFD_ShowString("UP-MENU");
}

void VFD_U_BOOT(void)
{
    //VFD_ClearAll();
    YWPANEL_VFD_ShowString("U-BOOT");
}

void VFD_U_Kernel(void)
{
    //VFD_ClearAll();
    YWPANEL_VFD_ShowString("U-KERNEL");    
}

#endif //combo vfd 
//#endif //define CFG_VFD
/* EOF------------------------------------------------------------------------*/

/* BOL-------------------------------------------------------------------*/
//$Log: vfd.c,v $
//Revision 1.1.1.1  2010/01/20 05:03:56  d22cj
//1、U-Boot首次导入
//2、修改启动参数
//3、修改进入菜单的方法：只能用ESC或者键盘进入
//
/* EOL-------------------------------------------------------------------*/

