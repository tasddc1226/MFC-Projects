#include <iostream>
#include "EXTLibrary.h"
using namespace std;
extern "C" EXTLIBRARY_API void ExternFunc() {
	cout << "Call the ExternFunc()!\n";
}