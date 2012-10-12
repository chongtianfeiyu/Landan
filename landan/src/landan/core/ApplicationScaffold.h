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
	// GLOBALS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


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


	//PUBLIC VARIABLES
	public:
		
	

	//PROTECTED FUNCTIONS
	protected:

	//PROTECTED VARIABLES
	protected:



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

	//////////////////////////////////////////////////////////////////////
	// STATICS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


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