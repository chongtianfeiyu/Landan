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

#ifndef _APPLICATIONCONFIG_H_
#define _APPLICATIONCONFIG_H_


//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <landan/core/LandanTypes.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// ENUMS /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	namespace application
	{
		enum APPLICATION_TYPE
		{
			BASIC = 0,
			WINDOWED = 1
		};

		enum UPDATE_TYPE
		{
			RUN_ONCE = 0,
			FRAMERATE_LIMITED = 1,
			FRAMERATE_UNLIMITED = 2
		};

		enum RENDER_TYPE
		{
			NONE = 0,
			HARDWARE_DIRECT_X_11 = 1
		};
	}

	//////////////////////////////////////////////////////////////////////
	// GLOBALS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////
	// CLASS DECLARATION /////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	class ApplicationConfig {

	//PUBLIC FUNCTIONS
	public:
		ApplicationConfig();
		virtual ~ApplicationConfig();

		application::APPLICATION_TYPE GetApplicationType();
		void SetApplicationType(application::APPLICATION_TYPE applicationType);

		application::UPDATE_TYPE GetUpdateType();
		void SetUpdateType(application::UPDATE_TYPE updateType);

		application::RENDER_TYPE GetRenderType();
		void SetRenderType(application::RENDER_TYPE renderType);

		f32 GetFrameRate();
		void SetFrameRate(f32 frameRate);


	//PRIVATE FUNCTIONS
	private:
		ApplicationConfig(const ApplicationConfig &other);
		ApplicationConfig& operator = (const ApplicationConfig &other);

	//PRIVATE VARIABLES
	private:
		application::APPLICATION_TYPE m_applicationType;
		application::UPDATE_TYPE m_updateType;
		application::RENDER_TYPE m_renderType;
		f32 m_frameRate;
	
	};

	//////////////////////////////////////////////////////////////////////
	// STATICS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


}
#endif