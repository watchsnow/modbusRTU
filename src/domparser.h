#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <qdom.h>
#include <qlistview.h>
#include <qmap.h> 
#include <qstring.h>
#include <qvariant.h>
#include <qstringlist.h>

class QDomElement;
class QIODevice;

#define  MAX  1024

#define DO_REG 0x01
#define DI_REG 0x02
#define AO_REG 0x03
#define AI_REG 0x04

#define BIT_DATA		0x01
#define BYTE_DATA		0x02
#define SHORT_DATA		0x03
#define WORD_DATA		0x04
#define FLOAT_DATA		0x05
#define DWORD_DATA		0x06
#define LONG_DATA		0x07
#define FLOAT_1_DATA	0x08
#define DWORD_1_DATA	0x09
#define LONG_1_DATA		0x0A
#define FLOAT_2_DATA	0x0B
#define Double_DATA     0x0C


typedef struct structCommLinkLayer
{
	QString sName;              //设备名称
	int frameLen;				//帧长度
	QString pName;				//协议名称
	QString rdyType;            //链路冗余
	int cycTime;				//循环周期
    bool bStop;					//停止设备
	QString sComNum;			//串口
	int iBaudRate;				//波特率
	int iDataBit;				//数据位
	int	iStopBit;				//停止位
	QString sVerifyBit;			//校验位
	int iTimeOut;				//超时
    int stateVar;               //状态量
	int ctlVar;                 //控制量
	int rmtPort;                //远程端口
  //int dvStart;				//设备状态地址
  //int iNum;					//发送串数
  //QString sText;			    //发送串
}CommLinkLayer;

//数据点
typedef struct structdatabaseIO
{
	//QString dtype;       //数据类型
	unsigned char dtype;
	int     count;       //在返回串中的位/字序号
	QString dMax;        //最大值
	QString dMin;        //最小值
	QString doffsetadd;   //偏移地址
	double  dZero;       //零点初值
	double  dK;          //变比
	unsigned int index;  //实时数据地址
}databaseIO;

//数据串
typedef struct structReg
{
	int iId;                   //设备地址
	//QString reg;               //设备区
	unsigned char reg;
	int regStart;              //起始地址
	int regNUM;                //连续个数
	int regEnd;                //结束地址
	int dataNUM;               //数据个数
	databaseIO dataIO[MAX];    //实时数据库,连续个数

	//gaowf 2015.1.9
	//此处做优化查询的部分用
	//char cFunc;
	int nRequestReadLen;
	unsigned char chReq[8];
}DataReg;

//数据表
typedef struct structTable
{
	int     add   ;        //寄存器地址   
	//QString dtype ;        //数据类型
	unsigned char dtype;
	int     id    ;        //设备地址
	//QString reg   ;	       //设备区
	unsigned char reg;
	double  zero  ;        //零点初值
	double  k     ;        //变比
	QString min   ;        //最小值
	QString max   ;        //最大值
	QString offsetadd;     //偏移地址
	int     index ;        //数据库序号
}DataVar;

//状态设备数据表
typedef struct structStatu
{
	int     id    ;        //设备地址
	int     index ;        //数据库序号
}DataStatu;

class QDomParser
{
public:
    QDomParser();
	~QDomParser();
	bool readCommLinkLayer(QString path ,QString sname);
	bool readCommLinkLayer_Reg(QString path ,QString sname);
	bool judgeReg(int id, int addr,unsigned char dtype,unsigned char reg);
	void newReg(DataVar iData, int itype);
	void insertReg(DataVar itable,int itype, int iorder);
	void tidy( int tablenum );
	
	void initRequestReg();

	unsigned short CRC16(unsigned char *puchMsg, unsigned short usDataLen); 

public:

	CommLinkLayer comm;
	QString fullPath;
	int type;   //插入的方式
	int order;  //插入的序号
	
	QValueList<DataReg> RegList;
	QValueList<DataVar> WriteList;
	QValueList<DataVar> VarList;	
	QValueList<DataStatu> StatuList;
	int stateVar;
    
		
};

#endif
