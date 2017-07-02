#include <stdafx.h>
#include <stdio.h>
namespace logger{

	void LogDebug(const char* fmt, ...)
	{
		char msg[MAX_PATH];
		memset(msg, 0, sizeof(msg));
		va_list args;
		va_start(args, fmt);		
		int r = vsprintf_s(msg,fmt,args);
		msg[r] = '\n';
		msg[r+1] = 0;
		OutputDebugStringA(msg);
		va_end(args);
	}

}