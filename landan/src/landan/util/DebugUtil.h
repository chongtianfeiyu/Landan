/*
Simplified BSD License
======================

Copyright(c) 2012, Karman Interactive Ltd. 
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list
of conditions and the following disclaimer in the documentation and/or other materials
provided with the distribution.

THIS SOFTWARE IS PROVIDED BY KARMAN INTERACTIVE LTD "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL KARMAN INTERACTIVE LTD OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Karman Interactive Ltd.
*/

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
#include <sstream>

//////////////////////////////////////////////////////////////////////
// MACROS ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


#ifndef NDEBUG

#define LOG_ERROR(message) \
	landan::DebugUtil::PrepLogStream("ERROR", __FILE__, __FUNCTION__, __LINE__); \
	landan::DebugUtil::LOGSTREAM << message << std::endl; \
	landan::DebugUtil::DeployLogStream();
#define LOG_DEBUG(message) \
	landan::DebugUtil::PrepLogStream("DEBUG", __FILE__, __FUNCTION__, __LINE__); \
	landan::DebugUtil::LOGSTREAM << message << std::endl; \
	landan::DebugUtil::DeployLogStream();
#define LOG_INFO(message) \
	landan::DebugUtil::PrepLogStream("INFO", __FILE__, __FUNCTION__, __LINE__); \
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
			static void PrepLogStream(const char *type, const char *file, const char *function, const unsigned long line);
			static void DeployLogStream();

		//PUBLIC VARIABLES
		public:
			static std::ostringstream LOGSTREAM;
	
	};

}
#endif
