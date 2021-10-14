#include <iostream>
#include "DLibrary.h"

extern "C" DLIBRARY_API void ExternFunction() {
	std::cout << "Call the ExternFunction()!" << "\n";
}