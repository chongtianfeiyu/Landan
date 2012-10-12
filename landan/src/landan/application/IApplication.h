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
*Class: CLASSNAME
*Description:
*Author: jkeon
**********************************/

#ifndef _IAPPLICATION_H_
#define _IAPPLICATION_H_


//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <landan/util/DebugUtil.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS //////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	class ApplicationConfig;

	//////////////////////////////////////////////////////////////////////
	// CLASS DECLARATION /////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	class IApplication {

	//PUBLIC FUNCTIONS
	public:
		IApplication() {LOG_INFO("IApplication Constructor");}
		virtual ~IApplication() {LOG_INFO("IApplication Destructor");}

		virtual void ApplyConfig(ApplicationConfig *appConfig) = 0;
		virtual void Init() = 0;
		virtual void Update(f32 deltaMilliSeconds) = 0;
		virtual void Destroy() = 0;

		void Quit() { *p_quitFlag = 0; }
		void ApplyQuitFlag(u8 *quitFlag) { p_quitFlag = quitFlag; }

	//PRIVATE FUNCTIONS
	private:
		IApplication(const IApplication &other);
		IApplication& operator = (const IApplication &other);


	//QUIT FLAG
	private:
		u8 *p_quitFlag;

	};
}


#endif