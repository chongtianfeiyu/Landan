/*********************************
*Class: CLASSNAME
*Description:
*Author: jkeon
**********************************/

#ifndef _SYSTEMWINDOW_H_
#define _SYSTEMWINDOW_H_


//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include <Windows.h>
#endif

#include <landan/core/LandanTypes.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {


	//////////////////////////////////////////////////////////////////////
	// ENUMS /////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	namespace window
	{
		enum WINDOW_STATE
		{
			NORMAL = 0,
			FULL_SCREEN = 1
		};
		enum WINDOW_TYPE
		{
			APPLICATION = 0,
			REAL_TIME = 1
		};
		#ifdef _WIN32
		enum WINDOW_RESIZE_STATE
		{
			MINIMIZED = SIZE_MINIMIZED,
			MAXIMIZED = SIZE_MAXIMIZED,
			RESTORED = SIZE_RESTORED
			//TODO: Investigate whether to support SIZE_MAXHIDE or SIZE_MAXSHOW (http://msdn.microsoft.com/en-us/library/ms632646%28v=vs.85%29.aspx)
		};
		#endif
	}


	//////////////////////////////////////////////////////////////////////
	// GLOBALS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////
	// CLASS DECLARATION /////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	class SystemWindow {

	//PUBLIC FUNCTIONS
	public:
		SystemWindow(tstring title, u32 x = 0, u32 y = 0, u32 width = 800, u32 height = 600, window::WINDOW_TYPE type = window::APPLICATION);
		~SystemWindow();

		bool Init();

#ifdef _WIN32
		LRESULT CALLBACK LocalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#endif


	//PUBLIC VARIABLES
	public:
	

	//PROTECTED FUNCTIONS
	protected:

	//PROTECTED VARIABLES
	protected:



	//PRIVATE FUNCTIONS
	private:
		SystemWindow(const SystemWindow &other);
		SystemWindow& operator = (const SystemWindow &other);

		

		//Event Handlers
		void OnResize(u32 width, u32 height, window::WINDOW_RESIZE_STATE);
		void OnMove(u32 x, u32 y);
		void OnClose();
		void OnDestroy();

	//PRIVATE VARIABLES
	private:
		
		tstring m_title;

		u32 m_x;
		u32 m_y;
		u32 m_width;
		u32 m_height;

		window::WINDOW_TYPE m_type;
		window::WINDOW_STATE m_state;
		


		#ifdef _WIN32
		
		HINSTANCE m_hinstance;
		HWND m_hwnd;

		static const LONG_PTR GWL_STYLE_WINDOWED = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;
		static const LONG_PTR GWL_STYLE_FULLSCREEN = WS_POPUP | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;

		static const LONG_PTR GWL_EXSTYLE_WINDOWED = WS_EX_OVERLAPPEDWINDOW;
		static const LONG_PTR GWL_EXSTYLE_FULLSCREEN = WS_EX_TOPMOST;

		static const tstring WINDOW_CLASS_NAME;
		#endif


	
	};

	//////////////////////////////////////////////////////////////////////
	// STATICS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


}
#endif