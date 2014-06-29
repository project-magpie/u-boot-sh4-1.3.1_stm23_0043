
/**********************************文件头部注释************************************/
//
//
//  					Copyright (C), 2005-2010, AV Frontier Tech. Co., Ltd.
//
//
// 文件名：		cryptoe2.c
//
// 创建者：		lz
//
// 创建时间：	2005.07.08
//
// 文件描述：
//
// 修改记录：   日       期      作      者       版本      修定
//				       ---------         ---------        -----        -----
//
/*****************************************************************************************/

/************************************文件包含****************************************/
// FOR ST INTEGRATED ENVIORNMENT
//FOR CURRENT MODULE
#include "cm_lib.h"
#include "cm_i2c.h"
#include "cm_i2c_l.h"
#include "cm_gpa.h"

#include "cryptoe2.h"
/************************************宏定义*******************************************/

#define IDENT_DEBUG(x)	printf x
#define IDENT_ERROR(x)	printf x
#define IDENT_OK(x)		printf x



/************************************常量定义****************************************/
#define IDENT_DES_KEY_LENGTH     				14
#define IDENT_MSGSIZE							1024


#define CRYPTOE2_MAX_RETRY_TIMES				3
#define F_EURO_S2       						0
#define F_TRIPLE_DES    						1
/************************************变量定义****************************************/

extern sint			cpe2_enable_set_lnb;
extern sint			cpe2_enable_play_vdec;
sint				cpe2_enable_castack = 0;

/************************************变量引用****************************************/
#define WriteDebug(x)


static uchar 	CryptoE2_IdentID[7] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff};

static sint  iCryptoE2ErrorCount = CRYPTOE2_MAX_RETRY_TIMES;

void print_boxname ( unsigned char *stb_id );
void  IDENT_Init( void )
{
	sint  	IdentError = 0;
	sint 	iRet = 0;
	//uchar  	BlockData[32];


	iCryptoE2ErrorCount = CRYPTOE2_MAX_RETRY_TIMES;


	IdentError = IDENT_E2_Init();
	if ( IdentError == 0 )
	{
		if ( !IDENT_E2_IsCryptoE2Exist() )
		{
			IDENT_DEBUG(("Ident ic do not exist\n\r"));
			return;
		}

//		IDENT_DEBUG(("Ident ic exist\n\r"));

		iRet = IDENT_E2_ReadSTBID(CryptoE2_IdentID);
		if ( iRet == TRUE )
		{
			iCryptoE2ErrorCount = 0;
//			IDENT_DEBUG(("Ident ic get stb id\n\r"));
			IDENT_DEBUG(("IdentID : %02x %02x %02x %02x %02x %02x %02x \n\r",
				CryptoE2_IdentID[0],
				CryptoE2_IdentID[1],
				CryptoE2_IdentID[2],
				CryptoE2_IdentID[3],
				CryptoE2_IdentID[4],
				CryptoE2_IdentID[5],
				CryptoE2_IdentID[6]
				));
			print_boxname ( CryptoE2_IdentID );
		}

	}


	IDENT_E2_Term();

	return;

}



unsigned char *	IDENT_GetStbID( void )
{
	return CryptoE2_IdentID;
}



sint	IDENT_Valid( void )
{
	sint  valid = 0;

	if( iCryptoE2ErrorCount )
		valid = 0;
	else
		valid = 1;

	return valid;
}


void print_boxname ( unsigned char *stb_id )
{
    int sys_id = (stb_id[0] << 16) | (stb_id[1] << 8) | stb_id[2] ;
    char* tmp = NULL;
    switch (sys_id) {
    case 0x090003:
        tmp = "Truman Premier 1+";
        break;
    case 0x090007:
        tmp = "GoldenMedia GM990";
        break;
    case 0x090008:
        tmp = "Edision Pingulux";
        break;
    case 0x09000a:
        tmp = "Amiko Alien SDH8900";
        break;
    case 0x09000b:
        tmp = "GalaxyInnovations S8120";
        break;
    case 0x09000d:
        tmp = "Dynavision Spark";
        break;
    case 0x09000e:
        tmp = "SAB Unix F+ Solo (S902)";
        break;
    case 0x090015:
        tmp = "Superbox S 750 HD";
        break;
    case 0x09001d:
        tmp = "Fulan Spark I+";
        break;
    case 0x090020:
        tmp = "SAMSAT LINUX 1";
        break;
    case 0x090021:
        tmp = "Visionnet Hammer 5400"; // or Startrack SRT 2020 HD, or Visionnet Fireball 101
        break;
    case 0x0c0003:
        tmp = "Truman Top Box 2";
        break;
    case 0x0c0007:
        tmp = "GoldenMedia Triplex";
        break;
    case 0x0c000a:
        tmp = "Amiko Alien 2";
        break;
    case 0x0c000b:
        tmp = "GalaxyInnovations Avatar 3 (8820)";
        break;
    case 0x0c000d:
        tmp = "Dynavision 7162";
        break;
    case 0x0c000e:
        tmp = "SAB Unix Triple HD (S903)";
        break;
    case 0x0c001d:
        tmp = "Satcom 7162";
        break;
    case 0x0c0020:
        tmp = "Samsat 7162";
        break;
    case 0x0c0021:
        tmp = "Visionnet Falcon";
        break;
    case 0x0c002b00:
        tmp = "Icecrypt S3700 CHD";
        break;
    default:
        tmp = "Unkown STB";
    }
    IDENT_DEBUG(("STB     : %s \n\r",tmp));
}

