#if !defined(DEV_SET_H)
#define DEV_SET_H

#include <qstringlist.h>

typedef struct structTagValue
{
	QString sidTaget  ;			//�豸id
	QString sidValue  ;			//��ֵ
	QString sregTaget  ;		//�Ĵ�����
	QStringList sregValue  ;	//��ֵ
	QString saddTaget  ;		//��ַ
	QString saddValue  ;		//��ֵ
	QString stypeTaget  ;		//��������
	QStringList stypeValue  ;	//��ֵ
	QString soffsetTaget  ;		//ƫ�Ƶ�ַ
	QString soffsetValue  ;		//��ֵ
	QString bakTaget ;			//����
	QString bakValue ;			//����
}TagValue;


class QDevSet
{
public:
	QDevSet();
	TagValue getValue();
	TagValue value;

};
#endif