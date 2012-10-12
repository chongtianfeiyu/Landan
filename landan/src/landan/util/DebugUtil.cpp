//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include "DebugUtil.h"

#ifdef _WIN32
#include <Windows.h>
#endif

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// STATICS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	tostringstream DebugUtil::LOGSTREAM;


	void DebugUtil::PrepLogStream(const tchar* type, const tchar* file, const tchar* function, const unsigned long line) 
	{

		tstring formattedFile;
		formattedFile.append(file);

		size_t c1 = formattedFile.find_last_of('\\');
		size_t c2 = formattedFile.find_last_of('/');
		(c2 > formattedFile.length()) ? (c2 = 0) : c2;
		size_t index = (c1 > c2) ? c1 : c2;

		DebugUtil::LOGSTREAM << type << " [" << formattedFile.substr(index+1) << " :: " << function << " : " << line << "] - ";
	}

#ifdef _MSC_VER
	void DebugUtil::DeployLogStream() {
		OutputDebugString(DebugUtil::LOGSTREAM.str().c_str());
		//Necessary to prevent leaks
		DebugUtil::LOGSTREAM.str(LT(""));
	}
#else
	void DebugUtil::DeployLogStream() {
		tcout << DebugUtil::LOGSTREAM.str() << std::endl;
		//Necessary to prevent leaks
		DebugUtil::LOGSTREAM.str(LT(""));
	}
#endif



}
