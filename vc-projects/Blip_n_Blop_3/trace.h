
#ifndef TRACE

#include "globals.h"
#include "bendebug.h"

#ifdef _DEBUG

#define TRACE if ( total_debug) debug<<(__FILE__)<<" : "<<(__LINE__)<<"\n";

#else

#define TRACE ;

#endif

#endif