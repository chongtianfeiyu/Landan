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

#include "Timer.h"

#ifdef _WIN32
	#include <Windows.h>
#endif

#include <landan/util/DebugUtil.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// STATICS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	f64 Timer::RCP_FREQUENCY_SECONDS = 0.0;
	f64 Timer::RCP_FREQUENCY_MILLISECONDS = 0.0;
	f64 Timer::RCP_FREQUENCY_MICROSECONDS = 0.0;

#ifdef _WIN32
	void Timer::Init()
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
		{
			LOG_ERROR("Unable to Query Performance Frequency");
		}
		else
		{
			f64 denom = static_cast<f64>(li.QuadPart);
			Timer::RCP_FREQUENCY_SECONDS = 1.0/denom;
			Timer::RCP_FREQUENCY_MILLISECONDS = 1.0/denom*1000.0;
			Timer::RCP_FREQUENCY_MICROSECONDS = 1.0/denom*1000000.0;
		}
	}

	f64 Timer::GetSeconds()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return static_cast<f64>(li.QuadPart)*Timer::RCP_FREQUENCY_SECONDS;
	}

	f64 Timer::GetMilliSeconds()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return static_cast<f64>(li.QuadPart)*Timer::RCP_FREQUENCY_MILLISECONDS;
	}

	f64 Timer::GetMicroSeconds()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return static_cast<f64>(li.QuadPart)*Timer::RCP_FREQUENCY_MICROSECONDS;
	}
#else
	void Timer::Init()
	{
		//TODO: Implement for other platforms
	}

	f64 Timer::GetSeconds()
	{
		//TODO: Implement for other platforms
		return 0.0;
	}

	f64 Timer::GetMilliSeconds()
	{
		//TODO: Implement for other platforms
		return 0.0;
	}

	f64 Timer::GetMicroSeconds()
	{
		//TODO: Implement for other platforms
		return 0.0;
	}
#endif

	//////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS //////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	Timer::Timer() {

	}

	//////////////////////////////////////////////////////////////////////
	// DESTRUCTOR ////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	Timer::~Timer() {

	}

	//////////////////////////////////////////////////////////////////////
	// INITIALIZE ////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////
	// DESTROY ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////
	// BODY //////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////
	// GETTERS/SETTERS ///////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

}