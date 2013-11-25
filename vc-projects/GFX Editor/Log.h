#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <Windows.h>

using namespace std;

namespace Log
{

	extern ofstream Debug;
	extern ofstream Error;

	void Clear();
	/*void Debug(string s);
	void Error(string s);*/

};