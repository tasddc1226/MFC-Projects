#pragma once

#ifdef EXTLIBRARY_EXPORTS
#define EXTLIBRARY_API __declspec(dllexport) 
#else
#define EXTLIBRARY_API __declspec(dllimport)
#endif

extern "C" EXTLIBRARY_API void ExternFunc();