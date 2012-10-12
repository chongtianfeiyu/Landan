/*********************************
*Class: DebugUtil
*Description:
*Author: jkeon
**********************************/

#ifndef _DEBUGUTIL_H_
#define _DEBUGUTIL_H_

//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <landan/core/LandanTypes.h>

//////////////////////////////////////////////////////////////////////
// MACROS ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


#ifndef NDEBUG


#define __TFILE__ LT(__FILE__)
#define __TFUNCTION__ LT(__FUNCTION__)


#define LOG_ERROR(message) \
	landan::DebugUtil::PrepLogStream(LT("ERROR"), __TFILE__, __TFUNCTION__, __LINE__); \
	landan::DebugUtil::LOGSTREAM << message << std::endl; \
	landan::DebugUtil::DeployLogStream();
#define LOG_DEBUG(message) \
	landan::DebugUtil::PrepLogStream(LT("DEBUG"), __TFILE__, __TFUNCTION__, __LINE__); \
	landan::DebugUtil::LOGSTREAM << message << std::endl; \
	landan::DebugUtil::DeployLogStream();
#define LOG_INFO(message) \
	landan::DebugUtil::PrepLogStream(LT("INFO"), __TFILE__, __TFUNCTION__, __LINE__); \
	landan::DebugUtil::LOGSTREAM << message << std::endl; \
	landan::DebugUtil::DeployLogStream();
#else
#define LOG_ERROR(message) 
#define LOG_DEBUG(message)
#define LOG_INFO(message)
#endif


//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {
	

	//////////////////////////////////////////////////////////////////////
	// CLASS DECLARATION /////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	
	class DebugUtil {

		//PUBLIC FUNCTIONS
		public:
			static void PrepLogStream(const tchar *type, const tchar *file, const tchar *function, const unsigned long line);
			static void DeployLogStream();

		//PUBLIC VARIABLES
		public:
			static tostringstream LOGSTREAM;
	
	};

}
#endif
