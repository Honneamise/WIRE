
#include "../shodan.h"

/*********/
void Log(const char* func, char* fmt, ...)
{
	if (func != NULL) { fprintf(stdout, "[%s]", func); };

	if (func != NULL && fmt != NULL) { fprintf(stdout, " "); };

	if (fmt != NULL)
	{
		va_list argp;
		va_start(argp, fmt);
		vfprintf(stdout, fmt, argp);
		va_end(argp);
	};

	fprintf(stdout, "\n");
}

/*********/
void Error(const char* func, char* fmt, ...)
{
#if defined(_MSC_VER) && defined(_DEBUG)
	int flag = 0;

	flag &= ~_CRTDBG_ALLOC_MEM_DF;
	_CrtSetDbgFlag(flag);

	flag &= ~_CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);
#endif

	fprintf(stdout, "[---ERROR---]\n");

	if (func != NULL) { fprintf(stdout, "[%s]", func); };

	if (func != NULL && fmt != NULL) { fprintf(stdout, " "); };

	if (fmt != NULL)
	{
		va_list argp;
		va_start(argp, fmt);
		vfprintf(stdout, fmt, argp);
		va_end(argp);
	};

	fprintf(stdout, "\n");

	exit(0);
}
