#pragma once

#ifdef DLIBRARY_EXPORTS // 파일명_EXPORTS
#define DLIBRARY_API __declspec(dllexport) // 파일명_API __declspec(dllexport)
#else
#define CLIBRARY_API __declspec(dllimport)
#endif

// extern "C" 파일명_API return_type function_name(arguments)
extern "C" DLIBRARY_API void ExternFunction();