#pragma once

#ifdef DLIBRARY_EXPORTS // ���ϸ�_EXPORTS
#define DLIBRARY_API __declspec(dllexport) // ���ϸ�_API __declspec(dllexport)
#else
#define CLIBRARY_API __declspec(dllimport)
#endif

// extern "C" ���ϸ�_API return_type function_name(arguments)
extern "C" DLIBRARY_API void ExternFunction();