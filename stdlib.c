#include "stdlib.h"

#if defined(_WIN32)
	#include <windows.h>
#endif

//
void __exit(int status)
{
	// platform specific process exit
	#if defined(_WIN32)
		ExitProcess(status);
	#endif
}
