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
	QString sName;              //�豸����
	int frameLen;				//֡����
	QString pName;				//Э������
	QString rdyType;            //��·����
	int cycTime;				//ѭ������
    bool bStop;					//ֹͣ�豸
	QString sComNum;			//����
	int iBaudRate;				//������
	int iDataBit;				//����λ
	int	iStopBit;				//ֹͣλ
	QString sVerifyBit;			//У��λ
	int iTimeOut;				//��ʱ
    int stateVar;               //״̬��
	int ctlVar;                 //������
	int rmtPort;                //Զ�̶˿�
  //int dvStart;				//�豸״̬��ַ
  //int iNum;					//���ʹ���
  //QString sText;			    //���ʹ�
}CommLinkLayer;

//���ݵ�
typedef struct structdatabaseIO
{
	//QString dtype;       //��������
	unsigned char dtype;
	int     count;       //�ڷ��ش��е�λ/�����
	QString dMax;        //���ֵ
	QString dMin;        //��Сֵ
	QString doffsetadd;   //ƫ�Ƶ�ַ
	double  dZero;       //����ֵ
	double  dK;          //���
	unsigned int index;  //ʵʱ���ݵ�ַ
}databaseIO;

//���ݴ�
typedef struct structReg
{
	int iId;                   //�豸��ַ
	//QString reg;               //�豸��
	unsigned char reg;
	int regStart;              //��ʼ��ַ
	int regNUM;                //��������
	int regEnd;                //������ַ
	int dataNUM;               //���ݸ���
	databaseIO dataIO[MAX];    //ʵʱ���ݿ�,��������

	//gaowf 2015.1.9
	//�˴����Ż���ѯ�Ĳ�����
	//char cFunc;
	int nRequestReadLen;
	unsigned char chReq[8];
}DataReg;

//���ݱ�
typedef struct structTable
{
	int     add   ;        //�Ĵ�����ַ   
	//QString dtype ;        //��������
	unsigned char dtype;
	int     id    ;        //�豸��ַ
	//QString reg   ;	       //�豸��
	unsigned char reg;
	double  zero  ;        //����ֵ
	double  k     ;        //���
	QString min   ;        //��Сֵ
	QString max   ;        //���ֵ
	QString offsetadd;     //ƫ�Ƶ�ַ
	int     index ;        //���ݿ����
}DataVar;

//״̬�豸���ݱ�
typedef struct structStatu
{
	int     id    ;        //�豸��ַ
	int     index ;        //���ݿ����
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
	int type;   //����ķ�ʽ
	int order;  //��������
	
	QValueList<DataReg> RegList;
	QValueList<DataVar> WriteList;
	QValueList<DataVar> VarList;	
	QValueList<DataStatu> StatuList;
	int stateVar;
    
		
};

#endif
