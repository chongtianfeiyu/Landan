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

#include <landan/core/Landan.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

using namespace landan;


//////////////////////////////////////////////////////////////////////
// WINDOWED APPLICATION TEST /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

class TestWindowedApplication : public WindowedApplication
{
public:

	TestWindowedApplication();
	~TestWindowedApplication();

	void ApplyConfig(ApplicationConfig &appConfig);
	void Init();
	void Update(f32 deltaMilliSeconds);
	void Render();
	void Destroy();

	u8 count;

};


TestWindowedApplication::TestWindowedApplication()
{
	LOG_INFO("TestWindowedApplication Constructor");
	count = 0;
}

TestWindowedApplication::~TestWindowedApplication()
{
	LOG_INFO("TestWindowedApplication Destructor");
}

void TestWindowedApplication::ApplyConfig(ApplicationConfig &appConfig)
{
	LOG_INFO("TestWindowedApplication Apply Config");
	appConfig.SetUpdateType(application::FRAMERATE_LIMITED);
}

void TestWindowedApplication::Init()
{
	LOG_INFO("TestWindowedApplication Init");
}

void TestWindowedApplication::Update(f32 deltaMilliSeconds)
{
	LOG_INFO("TestWindowedApplication Update " << deltaMilliSeconds);
	count++;

	if (count == 5)
	{
		Quit();
	}
}

void TestWindowedApplication::Render()
{
	LOG_INFO("TestWindowedApplication Render");
}

void TestWindowedApplication::Destroy()
{
	LOG_INFO("TestWindowedApplication Destroy");
}

//////////////////////////////////////////////////////////////////////
// BASIC APPLICATION TEST ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

class TestBasicApplication : public BasicApplication
{
public:

	TestBasicApplication();
	~TestBasicApplication();

	void ApplyConfig(ApplicationConfig &appConfig);
	void Init();
	void Update(f32 deltaMilliSeconds);
	void Destroy();

	u8 count;

};


TestBasicApplication::TestBasicApplication()
{
	LOG_INFO("TestBasicApplication Constructor");
	count = 0;
}

TestBasicApplication::~TestBasicApplication()
{
	LOG_INFO("TestBasicApplication Destructor");
}

void TestBasicApplication::ApplyConfig(ApplicationConfig &appConfig)
{
	LOG_INFO("TestBasicApplication Apply Config");
	appConfig.SetUpdateType(application::FRAMERATE_UNLIMITED);
}

void TestBasicApplication::Init()
{
	LOG_INFO("TestBasicApplicationInit");
}

void TestBasicApplication::Update(f32 deltaMilliSeconds)
{
	LOG_INFO("TestBasicApplication Update " << deltaMilliSeconds);
	count++;

	if (count == 5)
	{
		Quit();
	}
}

void TestBasicApplication::Destroy()
{
	LOG_INFO("TestBasicApplication Destroy");
}

//////////////////////////////////////////////////////////////////////
// ENTRY /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//CREATE_LANDAN_BASIC_APPLICATION(TestBasicApplication);
CREATE_LANDAN_WINDOWED_APPLICATION(TestWindowedApplication);