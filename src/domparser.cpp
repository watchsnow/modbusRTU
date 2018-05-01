#include <qfile.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qtextcodec.h>

#include "domparser.h"
#include "os.h"

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

QDomParser::QDomParser()
{
  
}

QDomParser::~QDomParser()
{

}


bool QDomParser::readCommLinkLayer(QString path ,QString sname)
{
	QDomDocument doc;
	
	QString name = QString(sname+".xml");
	name = path+ "/" + name ;

	QFile file(name);

	QString errorStr;
    int errorLine;
    int errorColumn;
	
    if (!doc.setContent(&file, true, &errorStr, &errorLine,
		&errorColumn)) {
        qWarning("Line %d, column %d: %s", errorLine, errorColumn,
			errorStr.ascii());
        return FALSE;
    }
	
    QDomElement doc_root = doc.documentElement();
    if (doc_root.tagName() != sname) {
        qWarning("The file is not a runconfig file");
        return FALSE ;
    }

	QDomElement element;
    QDomNode doc_node = doc_root.firstChild();
	while (!doc_node.isNull()) 
	{
		element = doc_node.toElement();
		if (element.tagName() == "sName")
			comm.sName = element.text();
		else if (element.tagName() == "frameLen")
			comm.frameLen = element.text().toInt();
		else if (element.tagName() == "sProName")
			comm.pName = element.text();
		else if (element.tagName() == "rdyType")
			comm.rdyType = element.text();
		else if (element.tagName() == "cycTime")
			comm.cycTime = element.text().toInt();
		else if (element.tagName() == "bStop")
			comm.bStop = (bool)element.text().toInt();
		else if (element.tagName() == "sComNum")
			comm.sComNum = element.text();
		else if (element.tagName() == "iBaudRate")
			comm.iBaudRate = element.text().toInt();
		else if (element.tagName() == "iDataBit")
			comm.iDataBit = element.text().toInt();
		else if (element.tagName() == "iStopBit")
			comm.iStopBit = element.text().toInt();
		else if (element.tagName() == "sVerifyBit")
			comm.sVerifyBit = element.text();
		else if (element.tagName() == "iTimeOut")
			comm.iTimeOut = element.text().toInt();
		else if (element.tagName() == "stateVar")
			comm.stateVar = element.text().toInt();
		else if (element.tagName() == "ctlVar")
			comm.ctlVar = element.text().toInt();
		else if (element.tagName() == "rmtPort")
			comm.rmtPort = element.text().toInt();

		doc_node = doc_node.nextSibling();
	}
	return TRUE;
}


bool QDomParser::readCommLinkLayer_Reg(QString path ,QString sname)
{
    QDomDocument doc;
		
	QString pname = QString(sname+"_Reg.xml");
	pname = path+ "/" + pname ;
	
	QFile file(pname);
	
	QString errorStr;
    int errorLine;
    int errorColumn;
	
    if (!doc.setContent(&file, true, &errorStr, &errorLine,
		&errorColumn)) {
        qWarning("Line %d, column %d: %s", errorLine, errorColumn,
			errorStr.ascii());
        return FALSE;
    }
	
    QDomElement doc_root = doc.documentElement();
    if (doc_root.tagName() != QString(sname)) {
        qWarning("The file is not a runconfig file");
        return FALSE ;
    }
	QTextCodec* m_textCodec = QTextCodec::codecForName("GB2312");

	QDomElement element;
    QDomNode doc_node = doc_root.firstChild();
	while (!doc_node.isNull()) 
	{			
		   
		   element = doc_node.toElement();

		   QString rtype = element.attribute("rtype"); //读写模式
		   
		   DataVar datavar  ;  

		   
		   QString stype = element.attribute("dtype");

		   if ( stype == m_textCodec->toUnicode("Bit1位开关量") )
		   {
				datavar.dtype = BIT_DATA;
		   }
		   else if ( stype==  m_textCodec->toUnicode("Byte8位无符号数") )
		   {
				datavar.dtype = BYTE_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Short16位有符号数") )
		   {
				datavar.dtype = SHORT_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Word16位无符号数") )
		   {
				datavar.dtype = WORD_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Float单精度浮点数") )
		   {
				datavar.dtype = FLOAT_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Double双精度浮点数") )
		   {
			   datavar.dtype = Double_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Dword32位无符号数") )
		   {
				datavar.dtype = DWORD_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Long32位有符号数") )
		   {	
				datavar.dtype = LONG_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Float单精度浮点数_1") )
		   {
				datavar.dtype = FLOAT_1_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Float单精度浮点数_2") )
		   {
				datavar.dtype = FLOAT_2_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Dword32位无符号数_1") )
		   {
				datavar.dtype = DWORD_1_DATA;
		   }
		   else if ( stype == m_textCodec->toUnicode("Long32位有符号数_1") )
		   {	
			   datavar.dtype = LONG_1_DATA;
		   }
		   else
				datavar.dtype = FLOAT_DATA;

		   //datavar.dtype = element.attribute("dtype");
		   datavar.id    = element.attribute("id").toInt();
		   datavar.add   = element.attribute("add").toInt();
		   datavar.zero  = element.attribute("zero").toDouble();
		   datavar.k     = element.attribute("k").toDouble();
		   datavar.index = element.attribute("index").toInt();

		   QString sReg   = element.attribute("reg");
		   if (sReg == m_textCodec->toUnicode("DO线圈"))  //数据区转换
				datavar.reg = DO_REG;
		   if (sReg == m_textCodec->toUnicode("DI离散输入寄存器"))
				datavar.reg = DI_REG;
		   if (sReg == m_textCodec->toUnicode("AO保持寄存器"))
				datavar.reg = AO_REG;
		   if (sReg == m_textCodec->toUnicode("AI输入寄存器"))
				datavar.reg = AI_REG;

		   //datavar.reg   = element.attribute("reg");
		   datavar.max   = element.attribute("max");
		   datavar.min   = element.attribute("min");
		   datavar.offsetadd = element.attribute("offsetadd");
		   
		   //2015.9.11 add 设备状态
		   DataStatu datastatu;
		   if (sReg == m_textCodec->toUnicode("设备状态"))
		   {
			   datastatu.id = element.attribute("id").toInt();
			   datastatu.index = element.attribute("index").toInt();
			   StatuList.append(datastatu);
		   }
		   else
		   {
			   if(rtype == m_textCodec->toUnicode("只读"))  
			   {
				   VarList.append(datavar);
			   }
			   else if(rtype == m_textCodec->toUnicode("只写"))
			   {
				   WriteList.append(datavar);
			   }
			   else
			   {
				   DataVar datavar2 ;
				   datavar2 = datavar; 
				   WriteList.append(datavar);
				   VarList.append(datavar2);			
			   }
		   }
 
		   
		
		doc_node = doc_node.nextSibling();
	}

	int tablenum = VarList.count();
	//规划查询帧
	if (tablenum > 0)
	{
		tidy( tablenum );   //整理排序表
	//	debug( "%d\n" , VarList.count());
		for (int i = 0 ; i < tablenum ; i++ )
		{
			DataVar DaVar = VarList[i];
			if ( judgeReg(DaVar.id, DaVar.add,DaVar.dtype,DaVar.reg) )
			{
				insertReg(DaVar, type, order); //粘贴
			}else
			{
				newReg(DaVar, type );  //新建
			}
		}
	//	debug( "%d\n" , RegList.count());
	}
	
	return TRUE;
		
}

void QDomParser::tidy( int tablenum)
{
	int i,j,addrmax = 0,x=0;
	DataVar tab ;

	for( j = 0 ; j < tablenum - 1 ; j++)  //按寄存器地址排序
	{	
		x = 0; ////////////////////////////////////////////////////////////////////
		addrmax = VarList[0].add;
		for( i = 1 ; i < tablenum - j ; i++) 
		{
			if ( VarList[i].add > addrmax )
			{
				x = i;
				addrmax = VarList[i].add;
			}
		}
		tab = VarList[tablenum - 1 - j];
		VarList[tablenum - 1 - j] = VarList[x];
		VarList[x] = tab;
	}
}

//判断粘贴或新建
bool QDomParser::judgeReg(int id, int addr,unsigned char dtype,unsigned char reg)
{
	QTextCodec* codec = QTextCodec::codecForName("GB2312");

	int Num = RegList.count(); 

	int shortnum = ( comm.frameLen -9 ) / 2;  //帧长判断数据个数
	int bitnum = shortnum * 16;

	if  ( dtype == FLOAT_DATA || dtype == LONG_DATA || dtype == DWORD_DATA || dtype == FLOAT_1_DATA || dtype == LONG_1_DATA || dtype == DWORD_1_DATA || dtype == FLOAT_2_DATA ) 
		type = 2;
	else if( dtype == Double_DATA )
		type = 4;
	else
		type = 1;

	while( Num-- )
	{
		DataReg datareg = RegList[Num];
		order = Num;

		//判断粘贴
		if ( reg == DO_REG || reg == DI_REG ) 
		{
			if ( (addr - datareg.regStart) < bitnum && datareg.iId == id 
				&& datareg.reg == reg  ) 
			{				
				return true;
			}
		}
		if ( reg == AO_REG || reg == AI_REG )
		{
			if ( (addr - datareg.regStart) < shortnum && datareg.iId == id 
				&& datareg.reg == reg && !(dtype ==Double_DATA || dtype == FLOAT_DATA || dtype == LONG_DATA || dtype == DWORD_DATA || dtype == FLOAT_1_DATA || dtype ==LONG_1_DATA || dtype == DWORD_1_DATA || dtype == FLOAT_2_DATA) ) 
			{				
				return true;
			}

			if ( (addr + 1 - datareg.regStart) < shortnum && datareg.iId == id 
				&& datareg.reg == reg && (dtype ==Double_DATA || dtype == FLOAT_DATA || dtype == LONG_DATA || dtype == DWORD_DATA || dtype == FLOAT_1_DATA || dtype == LONG_1_DATA || dtype == DWORD_1_DATA || dtype == FLOAT_2_DATA) ) 
			{			
				return true;
			}
		}
	}

	return false;
}

//新建命令串
void QDomParser::newReg(DataVar iData, int itype)
{
	DataReg  initReg  ;
	initReg.iId = iData.id;
	initReg.reg = iData.reg;
	initReg.regStart = iData.add;
	initReg.regNUM = itype;
	initReg.regEnd = initReg.regStart + itype - 1;
	initReg.dataNUM = 1; //数据个数

	initReg.dataIO[0].index  = iData.index;
	initReg.dataIO[0].dK     = iData.k;
	initReg.dataIO[0].dZero  = iData.zero;
	initReg.dataIO[0].dMax   = iData.max;
	initReg.dataIO[0].dMin   = iData.min;
	initReg.dataIO[0].doffsetadd = iData.offsetadd;
	initReg.dataIO[0].dtype  = iData.dtype;
	initReg.dataIO[0].count  = 0;  //数据的位/字序号

	RegList.append(initReg);
}

//粘贴命令串
void QDomParser::insertReg(DataVar iData,int itype, int iorder)
{
	int der;

	RegList[iorder].regNUM = iData.add - RegList[iorder].regStart + itype;
	RegList[iorder].regEnd = iData.add + itype - 1;
	RegList[iorder].dataNUM++;
	
	der = RegList[iorder].dataNUM - 1;

	RegList[iorder].dataIO[der].index  = iData.index;
	RegList[iorder].dataIO[der].dK     = iData.k;
	RegList[iorder].dataIO[der].dZero  = iData.zero;
	RegList[iorder].dataIO[der].dMax   = iData.max;
	RegList[iorder].dataIO[der].dMin   = iData.min;
	RegList[iorder].dataIO[der].doffsetadd   = iData.offsetadd;
	RegList[iorder].dataIO[der].dtype  = iData.dtype;
	RegList[iorder].dataIO[der].count  = iData.add - RegList[iorder].regStart;//数据所在串中的序号
	  
}

void QDomParser::initRequestReg()
{
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	int nRegNum = (int)RegList.count();
	int i=0; 
	for(i=0; i<nRegNum; i++){
		DataReg pdataReg = RegList[i];

		if ( pdataReg.reg == DO_REG || pdataReg.reg == DI_REG )//DI
		{
			int temp = (pdataReg.regNUM & 0x07);
			if( temp > 0 )
			{
				RegList[i].nRequestReadLen = (pdataReg.regNUM>>3) + 6;
			}
			else
			{
				RegList[i].nRequestReadLen = (pdataReg.regNUM>>3) + 5;
			}
		}
		else
		{
			RegList[i].nRequestReadLen = (pdataReg.regNUM<<1) + 5;
		}

		//协议组帧
		*( RegList[i].chReq + 0) = pdataReg.iId ;
		*( RegList[i].chReq + 1 ) = pdataReg.reg;
		
		*( RegList[i].chReq + 2) = (pdataReg.regStart >> 8) & 0xFF;
		*( RegList[i].chReq + 3) = pdataReg.regStart & 0xFF ;
		
		*( RegList[i].chReq + 4) = (pdataReg.regNUM >> 8) & 0xFF;
		*( RegList[i].chReq + 5) = pdataReg.regNUM & 0xFF;
		
		unsigned short  shCRC ;
		shCRC = CRC16( RegList[i].chReq, 6 );
		*( RegList[i].chReq + 6) =  ( shCRC >> 8 ) & 0xFF;
		*( RegList[i].chReq + 7) =  shCRC & 0xFF ;
	}
}

unsigned short QDomParser::CRC16(unsigned char *puchMsg, unsigned short usDataLen)
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
