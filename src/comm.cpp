// DL103.cpp: implementation of the CCom class.
//
//////////////////////////////////////////////////////////////////////
#include "comm.h"
#include "ctdrive.h"

#include <string.h>
#include <qtextcodec.h>
#include <qsocket.h> 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCom::CCom()
{
	pSerial = new CSerial();
	querynum = 0;
}

CCom::~CCom()
{

}

void CCom::quitDrives()
{
	QCtDrive *ctApp = NULL;
	ctApp = (QCtDrive*)qApp;
	ctApp->quitApplication();
}

void CCom::ReadXmlFile(QString path ,QString file)
{
	QTextCodec * codec = QTextCodec::codecForName( "GB2312" );
	QString name;
	QString queryStr;
	int comNo = 0 ;
	int verifyBit = 0 ;
	int bResult = 0 ;

	name = file;
    
	//读取同名xml配置文件
	if(domparser.readCommLinkLayer(path,name))
	{
		//串口初始化
		comNo = domparser.comm.sComNum.right(domparser.comm.sComNum.length()-3).toInt();
		if(domparser.comm.sVerifyBit == codec->toUnicode("无校验"))
			verifyBit = 0 ;
		else if(domparser.comm.sVerifyBit == codec->toUnicode("偶校验"))
			verifyBit = 1 ;
		else if(domparser.comm.sVerifyBit == codec->toUnicode("奇校验"))
			verifyBit = 2 ;
		else if(domparser.comm.sVerifyBit == codec->toUnicode("固定1校验"))
			verifyBit = 3 ;
		else if(domparser.comm.sVerifyBit == codec->toUnicode("固定0校验"))
			verifyBit = 4 ;

		pSerial->SetValue(comNo,domparser.comm.iBaudRate,domparser.comm.iDataBit,domparser.comm.iTimeOut,
			domparser.comm.iStopBit,verifyBit,50);

		//打开串口
		bResult = pSerial->OpenCom();
		
		
		//读取数据xml配置文件
		domparser.readCommLinkLayer_Reg(path,name);
		domparser.initRequestReg();
		querynum = domparser.RegList.count();

		openinfo.comNo = comNo ;
		openinfo.bandRateLo = (domparser.comm.iBaudRate >> 8 ) & 0xFF;
		openinfo.bandRateHi = domparser.comm.iBaudRate & 0xFF ;
		openinfo.dataBit = domparser.comm.iDataBit ;
		openinfo.verifyBit = verifyBit ;
		openinfo.stopBit = domparser.comm.iStopBit ;
		openinfo.frameLen = domparser.comm.frameLen ;
		openinfo.cycTimeLo = (domparser.comm.cycTime >> 8) & 0xFF;
		openinfo.cycTimeHi = domparser.comm.cycTime  & 0xFF;
		openinfo.bResult = 1 ;

		//其他设置
		cycTime = domparser.comm.cycTime ;
		rdyType = domparser.comm.rdyType;
	//	dvStart = domparser.comm.dvStart ;
		rmtPort = domparser.comm.rmtPort ;   
	}
}



unsigned char CCom::CheckSum( unsigned char * chBuf, int iLen )
{
	int i;
	unsigned int iSum = 0 ;
	for( i = 0 ; i < iLen; i++ )
		iSum += *( chBuf + i );
	return iSum % 0x100 ;
}


void CCom::display( int iDisplayType )
{
	QCtDrive *ctApp = NULL;
	ctApp = (QCtDrive*)qApp;

	switch( iDisplayType ){
	case MSG_COMM_OUTPUT:
		{
		buffer.type = 0x01 ;
		buffer.iLen = iOutputLen;
//		strcpy( (char*)buffer.pBuf, (char*)chOutput );
		memcpy( (char*)buffer.pBuf, (char*)chOutput, iOutputLen ); // linx214 4.26
		ctApp->freshDisplay(buffer);
		}
		break;
	case MSG_COMM_INPUT:
		{
		buffer.type = 0x02 ;
		buffer.iLen = iInputLen;
//		strcpy( (char*)buffer.pBuf, (char*)chInput );
		memcpy( (char*)buffer.pBuf, (char*)chInput, iInputLen ); // linx214 4.26
		ctApp->freshDisplay(buffer);
		}
		break;
	case MSG_DISPLAY:
		
		break;
	default:
		break; 
	}
}


void CCom::DisplayTxt( char *  strTxt )
{
}


void CCom::Run( )
{
	
}


void CCom::ParseFrame( unsigned char * chBuf, int iLen )
{
	
}
