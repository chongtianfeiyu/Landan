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
*Class: Scaffold
*Description:
*Author: jkeon
**********************************/

#ifndef _APPLICATIONSCAFFOLD_H_
#define _APPLICATIONSCAFFOLD_H_


//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <landan/core/LandanTypes.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS //////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	class IApplication;
	class ApplicationConfig;

	//////////////////////////////////////////////////////////////////////
	// CLASS DECLARATION /////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	class ApplicationScaffold {

	//PUBLIC FUNCTIONS
	public:
	
		ApplicationScaffold(IApplication *app);
		~ApplicationScaffold();

		void Init();

		void PrepBasic();
		void RunBasic();
		void StopBasic();

		void PrepWindowed();
		void RunWindowed();
		void StopWindowed();

	//PRIVATE FUNCTIONS
	private:
		ApplicationScaffold(const ApplicationScaffold &other);
		ApplicationScaffold& operator = (const ApplicationScaffold &other);

	//PRIVATE VARIABLES
	private:
		IApplication *p_app;
		f64 m_lastTime;
		f64 m_currentTime;
		f32 m_deltaTime;

		ApplicationConfig *p_appConfig;

		u8 *p_quitFlag;
	
	};

}




//If we're running on Windows we need a Windows entry point
#ifdef _WIN32
	//TODO: Do memchecking on a platform other than Visual Studio
	#ifdef LANDAN_DEVELOPMENT

		//Basic applications without the need for windows get a standard entry point
		#define CREATE_LANDAN_BASIC_APPLICATION(BASIC_APPLICATION_CLASS)											\
		int main(int argc, const char* argv[])																		\
		{																											\
			int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);													\
			tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;																	\
			tmpDbgFlag |= _CRTDBG_ALLOC_MEM_DF;																		\
			_CrtSetDbgFlag(tmpDbgFlag);																				\
			IApplication *app = new BASIC_APPLICATION_CLASS();														\
			ApplicationScaffold *scaffold = new ApplicationScaffold(app);											\
			scaffold->Init();																						\
			scaffold->PrepBasic();																					\
			scaffold->RunBasic();																					\
			scaffold->StopBasic();																					\
			if (scaffold != 0)																						\
			{																										\
				delete scaffold;																					\
				scaffold = 0;																						\
			}																										\
			if (app != 0)																							\
			{																										\
				delete app;																							\
				app = 0;																							\
			}																										\
			return 0;																								\
		}
		
		//Windowed applications need a Windows entry point
		#define CREATE_LANDAN_WINDOWED_APPLICATION(WINDOWED_APPLICATION_CLASS)										\
		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)				\
		{																											\
			int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);													\
			tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;																	\
			tmpDbgFlag |= _CRTDBG_ALLOC_MEM_DF;																		\
			_CrtSetDbgFlag(tmpDbgFlag);																				\
			IApplication *app = new WINDOWED_APPLICATION_CLASS();													\
			ApplicationScaffold *scaffold = new ApplicationScaffold(app);											\
			scaffold->Init();																						\
			scaffold->PrepWindowed();																				\
			scaffold->RunWindowed();																				\
			scaffold->StopWindowed();																				\
			if (scaffold != 0)																						\
			{																										\
				delete scaffold;																					\
				scaffold = 0;																						\
			}																										\
			if (app != 0)																							\
			{																										\
				delete app;																							\
				app = 0;																							\
			}																										\
			return 0;																								\
		}
		
	#else
		//Basic applications without the need for windows get a standard entry point
		#define CREATE_LANDAN_BASIC_APPLICATION(BASIC_APPLICATION_CLASS)											\
		int main(int argc, const char* argv[])																		\
		{																											\
			IApplication *app = new BASIC_APPLICATION_CLASS();														\
			ApplicationScaffold *scaffold = new ApplicationScaffold(app);											\
			scaffold->Init();																						\
			scaffold->PrepBasic();																					\
			scaffold->RunBasic();																					\
			scaffold->StopBasic();																					\
			if (scaffold != 0)																						\
			{																										\
				delete scaffold;																					\
				scaffold = 0;																						\
			}																										\
			if (app != 0)																							\
			{																										\
				delete app;																							\
				app = 0;																							\
			}																										\
			return 0;																								\
		}

		//Windowed applications need a Windows entry point
		#define CREATE_LANDAN_WINDOWED_APPLICATION(WINDOWED_APPLICATION_CLASS)										\
		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)				\
		{																											\
			IApplication *app = new WINDOWED_APPLICATION_CLASS();													\
			ApplicationScaffold *scaffold = new ApplicationScaffold(app);											\
			scaffold->Init();																						\
			scaffold->PrepWindowed();																				\
			scaffold->RunWindowed();																				\
			scaffold->StopWindowed();																				\
			if (scaffold != 0)																						\
			{																										\
				delete scaffold;																					\
				scaffold = 0;																						\
			}																										\
			if (app != 0)																							\
			{																										\
				delete app;																							\
				app = 0;																							\
			}																										\
			return 0;																								\
		}						
	#endif
#endif



#endif