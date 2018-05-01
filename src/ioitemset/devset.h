#if !defined(DEV_SET_H)
#define DEV_SET_H

#include <qstringlist.h>

typedef struct structTagValue
{
	QString sidTaget  ;			//设备id
	QString sidValue  ;			//键值
	QString sregTaget  ;		//寄存器区
	QStringList sregValue  ;	//键值
	QString saddTaget  ;		//地址
	QString saddValue  ;		//键值
	QString stypeTaget  ;		//数据类型
	QStringList stypeValue  ;	//键值
	QString soffsetTaget  ;		//偏移地址
	QString soffsetValue  ;		//键值
	QString bakTaget ;			//保留
	QString bakValue ;			//保留
}TagValue;


class QDevSet
{
public:
	QDevSet();
	TagValue getValue();
	TagValue value;

};
#endif