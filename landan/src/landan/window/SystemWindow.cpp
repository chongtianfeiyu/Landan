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

//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include "SystemWindow.h"
#include <nowide/convert.hpp>
#include <landan/util/DebugUtil.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// STATICS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

#ifdef _WIN32

	const string SystemWindow::WINDOW_CLASS_NAME = "LANDAN_WINDOW_CLASS";


	//Every Windows Message will hit this function. 
	LRESULT CALLBACK GlobalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
	{

		//Hold our target window instance
		SystemWindow *targetWindow = NULL;

		//If it's the WM_NCCREATE message (which should be the first message we get...)
		if(msg == WM_NCCREATE) {
			//Pull the target window out of the lpCreateParams which is the this pointer we pass into CreateWindowEx
			targetWindow = reinterpret_cast<SystemWindow*>((LONG)((LPCREATESTRUCT)lparam)->lpCreateParams);
			//Set the pointer to this instance in the GWLP_USERDATA so we can pull it out reliably in the future
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)targetWindow);
		}
		else {
			//Pull the window instance out of the GWLP_USERDATA
			targetWindow = reinterpret_cast<SystemWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
		}

		//If we still don't have a window we can't respond to any events so kick it to the default.
		if(targetWindow == NULL) {
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}

		//Otherwise we're all good and we can pipe it to the instances version of the WndProc
		return targetWindow->LocalWndProc(hwnd, msg, wparam, lparam);
	}
#endif


	//////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS //////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	SystemWindow::SystemWindow(string title, u32 x, u32 y, u32 width, u32 height, window::WINDOW_TYPE type)
	:m_title(title), m_x(x), m_y(y), m_width(width), m_height(height), m_type(type), m_state(window::NORMAL)
	{

	}

	//////////////////////////////////////////////////////////////////////
	// DESTRUCTOR ////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	SystemWindow::~SystemWindow() 
	{

	}

	//////////////////////////////////////////////////////////////////////
	// INITIALIZE ////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	bool SystemWindow::Init()
	{
#ifdef _WIN32

		//Get the HINSTANCE - This is how Cinder does it
		m_hinstance = GetModuleHandleW(NULL);

		//Create the Definition
		//TODO: Potentially pull some of these in via external config file
		WNDCLASSEXW definition;
		ZeroMemory(&definition, sizeof(WNDCLASSEXW));
		definition.cbSize = sizeof(WNDCLASSEXW);
		definition.cbClsExtra = 0;
		definition.cbWndExtra = 0;
		definition.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //TODO: If we're using DirectX or OpenGL to render, we don't need a background
		definition.hCursor = LoadCursorW(NULL, IDC_ARROW);
		definition.hIcon = LoadIconW(NULL, IDI_WINLOGO);
		definition.hIconSm = definition.hIcon;
		definition.hInstance = m_hinstance;
		definition.lpfnWndProc = GlobalWndProc;
		definition.lpszClassName = nowide::widen(WINDOW_CLASS_NAME).c_str(); //TODO: Cinder uses a different class name depending if Fullscreen or not. Do we care?
		definition.lpszMenuName = NULL;
		definition.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		//Register the class
		if (!RegisterClassExW(&definition))
		{
			LOG_ERROR("Register Class Failed!");
			return false;
		}


		//Set the initial window size and position
		RECT rect;
		rect.left = m_x;
		rect.top = m_y;
		rect.right = m_x + m_width;
		rect.bottom = m_y + m_height;

#endif

		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// EVENT HANDLERS ////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	void SystemWindow::OnResize(u32 width, u32 height, window::WINDOW_RESIZE_STATE)
	{
		m_width = width;
		m_height = height;
		//TODO: Dispatch Event for window Resize
	}

	void SystemWindow::OnMove(u32 x, u32 y)
	{
		m_x = x;
		m_y = y;
		//TODO: Dispatch Event for window Move
	}

	void SystemWindow::OnClose()
	{

	}

	void SystemWindow::OnDestroy()
	{

	}


	//////////////////////////////////////////////////////////////////////
	// WINDOWS SPECIFIC //////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

#ifdef _WIN32

	LRESULT CALLBACK SystemWindow::LocalWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		
		switch(msg)
		{
		case WM_SIZE:
			OnResize(static_cast<u32>(LOWORD(lparam)), static_cast<u32>(HIWORD(lparam)), static_cast<window::WINDOW_RESIZE_STATE>(wparam));
			break;
		case WM_MOVE:
			OnMove(static_cast<u32>(LOWORD(lparam)), static_cast<u32>(HIWORD(lparam)));
			break;
		case WM_CLOSE:
			OnClose();
			break;
		case WM_DESTROY:
			OnDestroy();
			break;

		default:
			//We don't handle the message so let the Default Window Proc handle it
			return DefWindowProcW(hwnd, msg, wparam, lparam);
		}
		return 0;
	}


#endif

}