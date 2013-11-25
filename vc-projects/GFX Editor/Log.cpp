#include "StdAfx.h"
#include "Log.h"

namespace Log
{
	ofstream Debug("log-debug.txt");
	ofstream Error("log-error.txt");

	void Clear()
	{
		/*DeleteFile("log-debug.txt");
		DeleteFile("log-error.txt");*/
	}

	/*void Debug(string s)
	{
		
		out << s << endl;
		out.flush();
		out.close();
	}*/

	/*void Error(string s)
	{
		ofstream out("log-error.txt");
		out << s << endl;
		out.flush();
		out.close();
	}*/

};