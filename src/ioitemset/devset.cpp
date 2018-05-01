#include "devset.h"
#include <qtextcodec.h>
	
QDevSet::QDevSet()
{
	QTextCodec * codec = QTextCodec::codecForName( "GB2312" );
	
	//设备地址
	value.sidTaget = codec->toUnicode("设备地址") ;
	value.sidValue = codec->toUnicode("1") ;

	//寄存器区
	value.sregTaget = codec->toUnicode("寄存器区") ;
	value.sregValue << codec->toUnicode("DO线圈") ; 
	value.sregValue << codec->toUnicode("DI离散输入寄存器");
	value.sregValue << codec->toUnicode("AO保持寄存器") ;
	value.sregValue << codec->toUnicode("AI输入寄存器") ;
//	value.sregValue << codec->toUnicode("0x26") ;
	

	//寄存器地址
	value.saddTaget = codec->toUnicode("寄存器地址") ;
	value.saddValue = codec->toUnicode("0") ;

	//数据类型
	value.stypeTaget = codec->toUnicode("数据类型") ;
	value.stypeValue << codec->toUnicode("Bit1位开关量");
	value.stypeValue << codec->toUnicode("Char8位有符号数");
	value.stypeValue << codec->toUnicode("Byte8位无符号数");
	value.stypeValue << codec->toUnicode("Short16位有符号数");
	value.stypeValue << codec->toUnicode("Word16位无符号数");
	value.stypeValue << codec->toUnicode("ACII2个字符");
	value.stypeValue << codec->toUnicode("Long32位有符号数");
	value.stypeValue << codec->toUnicode("Dword32位无符号数");
	value.stypeValue << codec->toUnicode("Float单精度浮点数");
	value.stypeValue << codec->toUnicode("Long32位有符号数_1");
	value.stypeValue << codec->toUnicode("Dword32位无符号数_1");
	value.stypeValue << codec->toUnicode("Float单精度浮点数_1");
	value.stypeValue << codec->toUnicode("String字符串");
	value.stypeValue << codec->toUnicode("Double双精度浮点数");
	value.stypeValue << codec->toUnicode("BCD");

	//偏移地址
	value.soffsetTaget = codec->toUnicode("偏移地址");
	value.soffsetValue = codec->toUnicode("0");
}

	
TagValue QDevSet::getValue()
{	
	return value;
}