
#include "devset.h"

QDevSet dev;

extern "C" __declspec(dllexport) TagValue getValue();

TagValue getValue()
{
	return dev.getValue();
}

