#include "devset.h"
#include <qtextcodec.h>
	
QDevSet::QDevSet()
{
	QTextCodec * codec = QTextCodec::codecForName( "GB2312" );
	
	//�豸��ַ
	value.sidTaget = codec->toUnicode("�豸��ַ") ;
	value.sidValue = codec->toUnicode("1") ;

	//�Ĵ�����
	value.sregTaget = codec->toUnicode("�Ĵ�����") ;
	value.sregValue << codec->toUnicode("DO��Ȧ") ; 
	value.sregValue << codec->toUnicode("DI��ɢ����Ĵ���");
	value.sregValue << codec->toUnicode("AO���ּĴ���") ;
	value.sregValue << codec->toUnicode("AI����Ĵ���") ;
//	value.sregValue << codec->toUnicode("0x26") ;
	

	//�Ĵ�����ַ
	value.saddTaget = codec->toUnicode("�Ĵ�����ַ") ;
	value.saddValue = codec->toUnicode("0") ;

	//��������
	value.stypeTaget = codec->toUnicode("��������") ;
	value.stypeValue << codec->toUnicode("Bit1λ������");
	value.stypeValue << codec->toUnicode("Char8λ�з�����");
	value.stypeValue << codec->toUnicode("Byte8λ�޷�����");
	value.stypeValue << codec->toUnicode("Short16λ�з�����");
	value.stypeValue << codec->toUnicode("Word16λ�޷�����");
	value.stypeValue << codec->toUnicode("ACII2���ַ�");
	value.stypeValue << codec->toUnicode("Long32λ�з�����");
	value.stypeValue << codec->toUnicode("Dword32λ�޷�����");
	value.stypeValue << codec->toUnicode("Float�����ȸ�����");
	value.stypeValue << codec->toUnicode("Long32λ�з�����_1");
	value.stypeValue << codec->toUnicode("Dword32λ�޷�����_1");
	value.stypeValue << codec->toUnicode("Float�����ȸ�����_1");
	value.stypeValue << codec->toUnicode("String�ַ���");
	value.stypeValue << codec->toUnicode("Double˫���ȸ�����");
	value.stypeValue << codec->toUnicode("BCD");

	//ƫ�Ƶ�ַ
	value.soffsetTaget = codec->toUnicode("ƫ�Ƶ�ַ");
	value.soffsetValue = codec->toUnicode("0");
}

	
TagValue QDevSet::getValue()
{	
	return value;
}