// Modbus.cpp: implementation of the CModbus class.
//
//////////////////////////////////////////////////////////////////////
#ifdef  OS_WIN
#include "stdafx.h"
#include <afxmt.h>
#endif



#include "Modbus.h"
#include <qtextcodec.h>

//#include "ramdrive.h"
#include "Serial.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern HWND  mainhwnd ;


static unsigned char tableCRCHi[] = {
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,
		0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,
		0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,
		0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,
		0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
		0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,
		0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,
		0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,
		0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,
		0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
		0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,
		0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,
		0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,
		0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
		0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,
		0x40
};

static unsigned char tableCRCLo[] = {
	0x00,0xc0,0xc1,0x01,0xc3,0x03,0x02,0xc2,0xc6,0x06,0x07,0xc7,0x05,0xc5,0xc4,
		0x04,0xcc,0x0c,0x0d,0xcd,0x0f,0xcf,0xce,0x0e,0x0a,0xca,0xcb,0x0b,0xc9,0x09,
		0x08,0xc8,0xd8,0x18,0x19,0xd9,0x1b,0xdb,0xda,0x1a,0x1e,0xde,0xdf,0x1f,0xdd,
		0x1d,0x1c,0xdc,0x14,0xd4,0xd5,0x15,0xd7,0x17,0x16,0xd6,0xd2,0x12,0x13,0xd3,
		0x11,0xd1,0xd0,0x10,0xf0,0x30,0x31,0xf1,0x33,0xf3,0xf2,0x32,0x36,0xf6,0xf7,
		0x37,0xf5,0x35,0x34,0xf4,0x3c,0xfc,0xfd,0x3d,0xff,0x3f,0x3e,0xfe,0xfa,0x3a,
		0x3b,0xfb,0x39,0xf9,0xf8,0x38,0x28,0xe8,0xe9,0x29,0xeb,0x2b,0x2a,0xea,0xee,
		0x2e,0x2f,0xef,0x2d,0xed,0xec,0x2c,0xe4,0x24,0x25,0xe5,0x27,0xe7,0xe6,0x26,
		0x22,0xe2,0xe3,0x23,0xe1,0x21,0x20,0xe0,0xa0,0x60,0x61,0xa1,0x63,0xa3,0xa2,
		0x62,0x66,0xa6,0xa7,0x67,0xa5,0x65,0x64,0xa4,0x6c,0xac,0xad,0x6d,0xaf,0x6f,
		0x6e,0xae,0xaa,0x6a,0x6b,0xab,0x69,0xa9,0xa8,0x68,0x78,0xb8,0xb9,0x79,0xbb,
		0x7b,0x7a,0xba,0xbe,0x7e,0x7f,0xbf,0x7d,0xbd,0xbc,0x7c,0xb4,0x74,0x75,0xb5,
		0x77,0xb7,0xb6,0x76,0x72,0xb2,0xb3,0x73,0xb1,0x71,0x70,0xb0,0x50,0x90,0x91,
		0x51,0x93,0x53,0x52,0x92,0x96,0x56,0x57,0x97,0x55,0x95,0x94,0x54,0x9c,0x5c,
		0x5d,0x9d,0x5f,0x9f,0x9e,0x5e,0x5a,0x9a,0x9b,0x5b,0x99,0x59,0x58,0x98,0x88,
		0x48,0x49,0x89,0x4b,0x8b,0x8a,0x4a,0x4e,0x8e,0x8f,0x4f,0x8d,0x4d,0x4c,0x8c,
		0x44,0x84,0x85,0x45,0x87,0x47,0x46,0x86,0x82,0x42,0x43,0x83,0x41,0x81,0x80,
		0x40
};

CModbus::CModbus()
{

	readDataLen = 0;
	exeNums = 1;
	memset(iCommCount,0,1000*4);

	ramrt = new QRamRT();
	if(ramrt->CreateRam(1))
	{
		ramrt->SetKcData(0,-1,"");
		ramrt->SetKcFlag(0,0);
	}
	querynum = 0 ;
	nCurrentIndex = 0;

	iInputLen = 0;
}

CModbus::~CModbus()
{

}

//功能:十六位CRC校验函数
//参数：puchMsg是存放需要校验数据的缓冲区指针，usDataLen是缓冲区中数据的长度
//返回:十六位CRC校验值，作为短整型返回
unsigned short CModbus::CRC16(unsigned char *puchMsg, unsigned short usDataLen)
{
	unsigned char uchCRCHi = 0xFF;
	unsigned char uchCRCLo = 0xFF;
	unsigned uIndex;
	while(usDataLen--)
	{
		uIndex = uchCRCHi ^ *puchMsg++;
		uchCRCHi = uchCRCLo ^ tableCRCHi[uIndex];
		uchCRCLo = tableCRCLo[uIndex];
	}
	return (uchCRCHi*0x100+uchCRCLo);
}

// 制作MODBUS RTU 的查询帧
void CModbus::CreateFrame( DataReg  pdataReg ,int index)
{
// 	QTextCodec * codec = QTextCodec::codecForName( "GB2312" );
//    *( chOutput + 0) = pdataReg.iId ;
//   
//    //这部分也可以优化
//    //在解析文件的时候这些部分都可以预先处理
//    if (pdataReg.reg == codec->toUnicode("DO线圈"))  //数据区转换
// 	  *( chReq + 1) = 0x01;
//    if (pdataReg.reg == codec->toUnicode("DI离散输入寄存器"))
// 	  *( chReq + 1) = 0x02;
//    if (pdataReg.reg == codec->toUnicode("AO保持寄存器"))
// 	  *( chReq + 1) = 0x03;
//    if (pdataReg.reg == codec->toUnicode("AI输入寄存器"))
// 	  *( chReq + 1) = 0x04;
// 
//    *( chOutput + 1 ) = pdataReg.cFunc;
//   
//    *( chOutput + 2) = (pdataReg.regStart >> 8) & 0xFF;
//    *( chOutput + 3) = pdataReg.regStart & 0xFF ;
//   
//    *( chOutput + 4) = (pdataReg.regNUM >> 8) & 0xFF;
//    *( chOutput + 5) = pdataReg.regNUM & 0xFF;
// 
//     unsigned short  shCRC ;
// 	shCRC = CRC16( chOutput, 6 );
// 	*( chOutput + 6) =  ( shCRC >> 8 ) & 0xFF;
// 	*( chOutput + 7) =  shCRC & 0xFF ;
// 	if ( pdataReg.reg == codec->toUnicode("DO线圈") || pdataReg.reg == codec->toUnicode("DI离散输入寄存器") )//DI
// 	{
// 		//int temp = pdataReg.regNUM%8;
// 		//
// 		int temp = (pdataReg.regNUM & 0x07);
// 		if( temp > 0 )
// 		{
// 			readDataLen = (pdataReg.regNUM>>3) + 6;
// 		}
// 		else
// 		{
// 			readDataLen = (pdataReg.regNUM>>3) + 5;
// 		}
// 	}
// 	else
// 	{
// 		readDataLen = (pdataReg.regNUM<<2) + 5;
// 	}
}

void CModbus::Run()
{
	//为了保证效率，请尽量不要使用/或者%
	//能进行移位操作就进行移位
	unsigned short shCRC ;
	bool bRes = false;		

	ScanCmd();
	
	if(nCurrentIndex >= querynum) nCurrentIndex = 0;

	//CreateFrame( domparser.RegList[nCurrentIndex], nCurrentIndex);  //传第二个参数i，为作为TCP帧包头。
	//memcpy( chOutput, chReq, 8 );
	iOutputLen = 8;
	//01 03 00 39 00 06 15 c5
	chOutput = domparser.RegList[nCurrentIndex].chReq;
	int nRet =pSerial->WriteCom( chOutput, 8 );

	for (int j = 0; j < 8; j++)
	{
		printf("%2x ", chOutput[j]);
	}

	if ( nRet == iOutputLen )
		display( MSG_COMM_OUTPUT );

	//iInputLen =  pSerial->ReadCom( chInput,readDataLen);
	iInputLen =  pSerial->ReadCom( chInput,domparser.RegList[nCurrentIndex].nRequestReadLen);
	chInput[iInputLen] = 0 ;
	/*调试*/
   /* iInputLen =29;
	char red[29]={0x01,0x04,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x67,0x0a,0x40,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0x1c};  
	memcpy(chInput,red,29);*/

	int StatuIndex = 0;
	int StatuCount = 0;
	int isWriteStatu = 0;
        StatuCount = domparser.StatuList.count();
	for (int n=0; n<(int)domparser.StatuList.count(); n++)
	{
		if ( chOutput[0] == domparser.StatuList[n].id )
		{
			StatuIndex = domparser.StatuList[n].index;
			isWriteStatu = 0;
			break;
		}
		else
		{
			isWriteStatu = 1;
		}
	}

	if( iInputLen > 3 )
	{
		iCommCount[nCurrentIndex] = 0 ;
		display( MSG_COMM_INPUT );
		if ( *( chOutput + 0) != *( chInput + 0 ) ) 
		{
			/*if ( StatuCount > 0 && isWriteStatu==0)
			{
				ramrt->SetItemValue(0,StatuIndex,0);//0 异常 1 正常
			}*/
			iCommCount[nCurrentIndex]++;
		
			nCurrentIndex++;
			return;
		}
		if( *( chOutput + 1) != *( chInput + 1 ) ) 
		{
			/*if ( StatuCount > 0 && isWriteStatu==0)
			{
				ramrt->SetItemValue(0,StatuIndex,0);//0 异常 1 正常
			}*/
			iCommCount[nCurrentIndex]++;
			nCurrentIndex++;
			return;
		}
		shCRC = CRC16( chInput, iInputLen - 2 );
		if ( StatuCount > 0 && isWriteStatu==0)
		{
			ramrt->SetItemValue(0,StatuIndex,1);//0 异常 1 正常
		}
		Parse( domparser.RegList[nCurrentIndex], chInput, iInputLen,shCRC);
		
	}
	else
	{
		iCommCount[nCurrentIndex] ++ ;
		if( iCommCount[nCurrentIndex] > 3 )
		{
			if ( StatuCount > 0 && isWriteStatu==0)
			{
				ramrt->SetItemValue(0,StatuIndex,0);//0 异常 1 正常
			}
			iCommCount[nCurrentIndex] = 0 ;
		}
	}			

	nCurrentIndex++;

}

void CModbus::Parse(DataReg pdataReg,unsigned char *chInput, unsigned short iInputLen,unsigned short shCRC)
{
    unsigned int i, intTmp , iCount;
	unsigned char chTemp  ;
	unsigned short ushTmp ;
	short shTmp ;
	double iValue;
	float flTmp;
	int bytecount;  //字节序号
	int bitcount;   //位序号

	unsigned long longTemp;
	char chBufTemp[8];
	double doubleTemp=0.0;
	
	//QTextCodec* codec = QTextCodec::codecForName("GB2312");

	unsigned short chCRC[2];
	chCRC[0] = (shCRC >> 8) & 0xFF ;
	chCRC[1] = shCRC & 0xFF ;
	if( *(chInput + iInputLen - 1 ) != chCRC[1] || *(chInput + iInputLen - 2 ) != chCRC[0] )
		return ;
	
	iCount = *( chInput + 2 );
	if(  pdataReg.reg == DO_REG || pdataReg.reg == DI_REG  )
	{
		for( i = 0; i < pdataReg.dataNUM; i++ ){

			bytecount = (pdataReg.dataIO[i].count>>3) ;
			bitcount = pdataReg.dataIO[i].count - (bytecount<<3);

			chTemp = *( chInput + 3 + bytecount );
			iValue = chTemp >> bitcount & 0x01 ;
			ramrt->SetItemValue(0,pdataReg.dataIO[i].index,iValue);			
		}
	}
	
	else if ( pdataReg.reg == AO_REG || pdataReg.reg == AI_REG)
	{
		for( i = 0; i < pdataReg.dataNUM; i++ )
		{
			if ( pdataReg.dataIO[i].dtype == BIT_DATA )
			{
			//	ushTmp = *( chInput + 3 + pdataReg.dataIO[i].count*2 + 1) ;
			//	iValue = ushTmp & 0x0001;
				ushTmp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1) )<<8) 
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1) ;
				iValue = (ushTmp >> pdataReg.dataIO[i].doffsetadd.toInt()) & 0x01;
			}
			else if ( pdataReg.dataIO[i].dtype==  BYTE_DATA )
			{
				if(pdataReg.dataIO[i].doffsetadd.toInt() == 0)
					ushTmp = *( chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1) ;
				else
					ushTmp = *( chInput + 3 + (pdataReg.dataIO[i].count<<1));

				iValue = ushTmp ;

			}
			else if ( pdataReg.dataIO[i].dtype == SHORT_DATA )
			{
				ushTmp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1))<<8)
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1) ;
				memcpy( &shTmp, &ushTmp, 2 );
				iValue = shTmp ;
			}
			else if ( pdataReg.dataIO[i].dtype == WORD_DATA )
			{
				ushTmp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1))<<8)
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1) ;
				iValue = ushTmp ;
			}
			else if ( pdataReg.dataIO[i].dtype == FLOAT_DATA )
			{
				intTmp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1))<<24) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1)<<16)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 2)<<8)
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 3);
				memcpy(&flTmp,&intTmp,4);
				iValue = flTmp ;
			}
			else if ( pdataReg.dataIO[i].dtype == Double_DATA )
			{
			/*	longTemp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1)+7)<<56) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 6)<<48)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 5)<<40)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 4)<<32)
					+(*( chInput + 3 + (pdataReg.dataIO[i].count<<1) +3)<<24) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 2)<<16)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1)<<8)
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 0);
				memcpy(&doubleTemp,&longTemp,8);*/

				chBufTemp[0] = *( chInput + 3 + (pdataReg.dataIO[i].count<<1)+1);
				chBufTemp[1] = *( chInput + 3 + (pdataReg.dataIO[i].count<<1)+0);
				chBufTemp[2] = *( chInput + 3 + (pdataReg.dataIO[i].count<<1)+3);
				chBufTemp[3] = *( chInput + 3 + (pdataReg.dataIO[i].count<<1)+2);
				chBufTemp[4] = *( chInput + 3 + (pdataReg.dataIO[i].count<<1)+5);
				chBufTemp[5] = *( chInput + 3 + (pdataReg.dataIO[i].count<<1)+4);
				chBufTemp[6] = *( chInput + 3 + (pdataReg.dataIO[i].count<<1)+7);
				chBufTemp[7] = *( chInput + 3 + (pdataReg.dataIO[i].count<<1)+6);

				memcpy(&doubleTemp,&chBufTemp,8);
			
				iValue = doubleTemp ;
			}
			else if ( pdataReg.dataIO[i].dtype == DWORD_DATA )
			{
	   	     intTmp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1))<<24) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1)<<16)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 2)<<8)
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 3);
				
				iValue = intTmp ;
			}
			else if ( pdataReg.dataIO[i].dtype == LONG_DATA )
			{	
				unsigned int uvalue = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1))<<24) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1)<<16) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 2)<<8)
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 3);
				
				int temp = 0;

				memcpy(&temp, &uvalue, 4);

				iValue = temp;

				//memcpy(&iValue,  &uvalue, 4);
			}
			else if ( pdataReg.dataIO[i].dtype == FLOAT_1_DATA )
			{
				intTmp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1))<<8) 
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 2)<<24)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 3)<<16);
				memcpy(&flTmp,&intTmp,4);
				iValue = flTmp ;
			}
			else if ( pdataReg.dataIO[i].dtype == FLOAT_2_DATA )
			{
				intTmp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1))) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1)<<8)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 2)<<16)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 3)<<24);
				memcpy(&flTmp,&intTmp,4);
				iValue = flTmp ;
			}
			else if ( pdataReg.dataIO[i].dtype == DWORD_1_DATA )
			{
				intTmp = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1))<<8) 
					+ *(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 2)<<24)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 3)<<16);
				iValue = intTmp ;
			}
			else if (pdataReg.dataIO[i].dtype == LONG_1_DATA)
			{
				unsigned int uvalue = (*( chInput + 3 + (pdataReg.dataIO[i].count<<1)) << 8) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 1)) 
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 2) << 24)
					+ (*(chInput + 3 + (pdataReg.dataIO[i].count<<1) + 3) << 16);
				
				int temp = 0;

				memcpy(&temp, &uvalue, 4);

				iValue = temp;
			}
		
			//变比、零值、最大、最小
			iValue = iValue * pdataReg.dataIO[i].dK + pdataReg.dataIO[i].dZero;

			if ( pdataReg.dataIO[i].dMax != "" )
			{
				if (iValue > pdataReg.dataIO[i].dMax.toDouble())
					iValue = pdataReg.dataIO[i].dMax.toDouble();
			}
			if ( pdataReg.dataIO[i].dMin != "" )
			{
				if (iValue < pdataReg.dataIO[i].dMin.toDouble())
					iValue = pdataReg.dataIO[i].dMin.toDouble();
			}
			ramrt->SetItemValue(0,pdataReg.dataIO[i].index,iValue);
		}
	}
}

int CModbus::findWiteKcData( int wrindex , DataVar &writevar)
{
	//根据index查找"写点"
	int writencount = domparser.WriteList.count(); 
	for( int i = 0; i< writencount ; i++)  //find index
	{
		if ( domparser.WriteList[i].index == wrindex )
		{
			writevar =  domparser.WriteList[i];
			return 1;
		}
	}
	return 0;
}

// 执行收到的命令
int CModbus::ExecCmd( DataVar execdata, char * chCmd )
{
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	int i, iRegNums ,wrindex = 0 ;
	short data[100];    //源值

	getAnalyseAOCommand(chCmd,iRegNums,data);	
		
	//QString wtype = execdata.dtype; //数据类型
	unsigned char reg = execdata.reg;     //数据区
	int id = execdata.id;           //设备地址
	int addr = execdata.add;        //寄存器地址
	unsigned char chReq[1024];
	if ( reg == DO_REG && iRegNums == 1)
	{	
		*( chReq + 0 ) = id;
		*( chReq + 1 ) = 0x05;
		
		*( chReq + 2 ) = ( addr >> 8 ) & 0xFF;
		*( chReq + 3 ) = addr & 0xFF;

		int idata = data[0] & 0x01;
		if( idata == 0 )
		{
			*( chReq + 4) = 0x00;
			*( chReq + 5) = 0x00;
		}
		else 
		{
			*( chReq + 4) = 0xFF;
			*( chReq + 5) = 0x00;
		}
		
		unsigned short  shCRC ;
		shCRC = CRC16( chReq, 6 );
		*( chReq + 6) =  ( shCRC >> 8 ) & 0xFF ;
		*( chReq + 7) =  shCRC & 0xFF ;
		
		pSerial->WriteCom( chReq, 8 );
		chOutput = chReq;
		//memcpy( chOutput, chReq, 8 );
		iOutputLen = 8;
		display( MSG_COMM_OUTPUT );
	//	pSerial->waitForMillisec(50);
		iInputLen =  pSerial->ReadCom( chInput,8);
		chInput[iInputLen] = 0 ;
		display( MSG_COMM_INPUT );
		return 1;
	}
	if ( reg == DO_REG && iRegNums > 1 )
	{	
		*( chReq + 0) = id ;
		*( chReq + 1) =  0x0F ;				// ====>0x0F
		
		*( chReq + 2) = ( addr >> 8 ) & 0xFF  ;
		*( chReq + 3) = addr & 0xFF ;
		
		*( chReq + 4 ) = ( iRegNums >> 8 ) & 0xFF  ;
		*( chReq + 5 ) = iRegNums & 0xFF ;
		
		*( chReq + 6 ) = ((iRegNums+7)>>3);
		
		int nTmp = 7;
		//		int D0Nums = 0;
		int nBytes=((iRegNums+7)>>3);
		//		int nData[100] = { 0 };
		int nValue[20] = { 0 };
		//		getAnalyseDOCommand( chCmd, D0Nums, nData );
		int nLastBytesInArray = nBytes - 1;							// 在产生数组中的最后一个字节下标
		
		// 除开最后一个字节, 前面全部饱和的字节
		for (int j = 0; j < nLastBytesInArray; ++j)
		{
			for ( int nBit = 0; nBit < 8; ++nBit )
			{
				nValue[j] += (data[ 8 * j + nBit ] << nBit);
			}
		}
		// 最后一个字节特殊处理, 可能不满足8位, 其余补0
		for ( int nLastBit = 0; nLastBit < 8; ++nLastBit )
		{
			nValue[ nLastBytesInArray ] += (data[ 8 * nLastBytesInArray + nLastBit ] << nLastBit);
		}
		
		for (int k = 0; k < nBytes; ++k)
		{
			*(chReq + nTmp) = nValue[k]; nTmp++;
		}
		unsigned short  shCRC ;
		shCRC = CRC16( chReq,  nTmp );
		*( chReq + nTmp ) =  ( shCRC >> 8 ) & 0xFF ;
		*( chReq + nTmp + 1 ) =  shCRC & 0xFF ;
		
		pSerial->WriteCom( chReq, nTmp + 2 );// head + data + crc
		chOutput = chReq;
		//memcpy( chOutput, chReq, nTmp + 2 );
		iOutputLen = nTmp + 2;
		display( MSG_COMM_OUTPUT );
	//	pSerial->waitForMillisec( 50 );
		iInputLen =  pSerial->ReadCom( chInput,8);
		chInput[iInputLen] = 0 ;
		display( MSG_COMM_INPUT );
		return 1;
	}
	if (  reg == AO_REG && iRegNums == 1  )
	{
		
		*( chReq + 0) = id ;
		*( chReq + 1) =  0x06 ;
		
		*( chReq + 2) = ( addr  >> 8 ) & 0xFF ;
		*( chReq + 3) = addr & 0xFF ;
		
		
		*( chReq + 4) = ( data[0] >> 8 ) & 0xFF;
		*( chReq + 5) = data[0] & 0xFF ;
		
		unsigned short  shCRC ;
		shCRC = CRC16( chReq, 6 );
		*( chReq + 6) =  ( shCRC >> 8 ) & 0xFF ;
		*( chReq + 7) =  shCRC & 0xFF ;
		pSerial->WriteCom( chReq, 8 );
		chOutput = chReq;
		//memcpy( chOutput, chReq, 8 );
		iOutputLen = 8;
		display( MSG_COMM_OUTPUT );
	//	pSerial->waitForMillisec( 50 );
		iInputLen =  pSerial->ReadCom( chInput,8);
		chInput[iInputLen] = 0 ;
		display( MSG_COMM_INPUT );
		return 1;
	}
	if (  reg == AO_REG &&  iRegNums > 1  )
	{			
 		*( chReq + 0 ) = id ;
 		*( chReq + 1 ) =  0x10 ;
 		
 		*( chReq + 2 ) = ( addr >> 8) & 0xFF ;
 		*( chReq + 3 ) =  addr & 0xFF ;
 		
 		*( chReq + 4 ) = ( iRegNums >> 8 ) & 0xFF;
 		*( chReq + 5 ) = iRegNums & 0xFF ;
 		*( chReq + 6 ) = (iRegNums<<1) ;
 		
  		for( i = 0; i < iRegNums; i++ ){
  			*( chReq + 7 + 2 * i ) = ( data[i] >> 8 ) & 0xFF;
  			*( chReq + 7 + 2 * i + 1 ) = data[i] & 0xFF;
  		}
 		
 		unsigned short  shCRC ;
 		//这里为啥要反复用到7+(iRegNums*2)？？？？
 		//
 		int nWriteNum = 7+(iRegNums<<1);
 		shCRC = CRC16( chReq,  nWriteNum );
 		*( chReq + nWriteNum ) =  ( shCRC >> 8 ) & 0xFF ;
 		*( chReq + nWriteNum + 1 ) =  shCRC & 0xFF ;
 		pSerial->WriteCom( chReq, nWriteNum + 2 );// head + data + crc
 		chOutput = chReq;
 		//memcpy( chOutput, chReq,  nWriteNum + 2 );
 		iOutputLen = nWriteNum + 2;
 		display( MSG_COMM_OUTPUT );
 	//	pSerial->waitForMillisec( 50 );
 		iInputLen =  pSerial->ReadCom( chInput,8);
 		chInput[iInputLen] = 0 ;
 		display( MSG_COMM_INPUT );
 		return 1;


		/* add by Gaoqiang for WuShui DianQi */
		//*( chReq + 0) = id ;
		//*( chReq + 1) =  0x06 ;
		//
		//*( chReq + 2) = ( addr  >> 8 ) & 0xFF ;
		//*( chReq + 3) = addr & 0xFF ;
		
 	//	for( i = 0; i < iRegNums; i++ )
 	//	{
 	//		*( chReq + 4 + 2 * i ) = ( data[i] >> 8 ) & 0xFF;
 	//		*( chReq + 4 + 2 * i + 1 ) = data[i] & 0xFF;
 	//	}

		//
		//unsigned short  shCRC ;
		//shCRC = CRC16( chReq, 12 );
		//*( chReq + 12) =  ( shCRC >> 8 ) & 0xFF ;
		//*( chReq + 13) =  shCRC & 0xFF ;
		//pSerial->WriteCom( chReq, 14 );
		//chOutput = chReq;
		////memcpy( chOutput, chReq, 8 );
		//iOutputLen = 8;
		//display( MSG_COMM_OUTPUT );
		////	pSerial->waitForMillisec( 50 );
		//iInputLen =  pSerial->ReadCom( chInput,14);
		//chInput[iInputLen] = 0 ;
		//display( MSG_COMM_INPUT );
		//return 1;

	}
	return -1;
}

// 执行收到的命令
void CModbus::ScanCmd()
{
	
	if(strcmp(ramrt->GetKcData(0)->dataKC,"EXIT") == 0){
		quitDrives();
		return ;
	}
	if(ramrt->GetKcFlag(0) == 1)  //控制标志
	{
		int wrindex = ramrt->GetKcData(0)->kcNo ;  //获取写序号
		char chCmd[200];
		strcpy(chCmd,ramrt->GetKcData(0)->dataKC); //获取写Value
		
		DataVar writevar ; 
		if( findWiteKcData(wrindex,writevar) ) //找到写结构
		{
			if ( ExecCmd(writevar, chCmd))     //执行控制结构
				ramrt->SetKcFlag(0,0);         //清空标志
		}
	}
	
}
//补充解析
//////////////////////////////////////////////////////////////////////

void CModbus::getFirstString( char* szData )
{
	char _szRet[10];
	memset( _szRet, 0, 10 );
	
	sscanf( szData, "%s", _szRet );
	
	int nLen = strlen( _szRet ) + 1;
	
	strcpy( szData, szData + nLen );
}

//
int CModbus::getFirstInt( char* szData )
{
	int nRet = -1;
	
	sscanf( szData, "%d", &nRet );
	
//	int nLen = ( (nRet / 10) > 0 ? 2 : 1 ) + 1;
    char strnRet[10];
	sprintf( strnRet,"%d",nRet);
	int nLen = strlen(strnRet) + 1;

	
	strcpy( szData, szData + nLen );
	
	return nRet;
}

//将DO的值存入数组
void CModbus::getAnalyseDOCommand( const char* szData, int& nCommandNums, int Data[] )
{
	// 临时变量
	char tmp[10];
	char _szData[100];
	strcpy( _szData, szData );
	memset(tmp, 0, 10);
	
	// 移除功能码
	getFirstString( _szData );
	// 移除地址位
	getFirstInt( _szData );
	// 移除起始位
	getFirstInt( _szData );
	// 获得数据个数
//	nCommandNums = getFirstInt( _szData );
	nCommandNums = this->getDataNums( QString(_szData) );
	// 循环赋值给数组
	for ( int i = 0; i < nCommandNums; ++i )
	{
		Data[i] = getFirstInt( _szData );
	}
}

void CModbus::getAnalyseAOCommand( const char* szData, int& nCommandNums, short Data[] )
{
	// 临时变量
	char tmp[10];
	char _szData[100];
	strcpy( _szData, szData );
	memset(tmp, 0, 10);
	
	// 移除功能码
//	getFirstString( _szData );
	// 移除地址位
//	getFirstInt( _szData );
	// 移除起始位
//	getFirstInt( _szData );
	// 获得数据个数
	nCommandNums = getDataNums( QString(_szData) );
	// 循环赋值给数组
	for ( int i = 0; i < nCommandNums; ++i )
	{
		Data[i] = getFirstInt( _szData );
	}
}

int CModbus::getDataNums( const QString& qstrCmdList ) const
{
	int it = 0;
	if (qstrCmdList.right(1) == " ")
	{
		it = 1;
	}
	int nDataNums = 0;
	int nStartFindPos = -1;
	
	do 
	{
		nStartFindPos++;
		nStartFindPos = qstrCmdList.find( " ", nStartFindPos );
		nDataNums++;
	} while ( nStartFindPos != -1 );
	
	return nDataNums-it;
}


