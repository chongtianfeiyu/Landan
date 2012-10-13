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
*Class: UTF8Test.h
*Description: 
*Author: jkeon
**********************************/

#ifndef _UTF8TEST_H_
#define _UTF8TEST_H_

//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <landan/util/DebugUtil.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan
{

	//////////////////////////////////////////////////////////////////////
	// CLASS DECLARATION /////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	class UTF8Test : public ::testing::Test
	{

	//PUBLIC FUNCTIONS
	protected:
		virtual ~UTF8Test(){

		}
		virtual void SetUp()
		{
			
		}
		virtual void TearDown()
		{

		}

		//UTF8 Sample Text from http://www.nubaria.com/en/blog/?p=289
	};

	TEST_F(UTF8Test, TestSimple)
	{
		// Chinese characters for "zhongwen" ("Chinese language").
		const char kChineseSampleText[] = {-28, -72, -83, -26, -106, -121, 0};

		LOG_INFO("Chinese Text: " << kChineseSampleText);

		// Arabic "al-arabiyya" ("Arabic").
		const char kArabicSampleText[] = {-40, -89, -39, -124, -40, -71, -40, -79, -40, -88, -39, -118, -40, -87, 0};

		LOG_INFO("Arabic Text: " << kArabicSampleText);

		// Spanish word "canon" with an "n" with "~" on top and an "o" with an acute accent.
		const char kSpanishSampleText[] = {99, 97, -61, -79, -61, -77, 110, 0};

		LOG_INFO("Spanish Text: " << kSpanishSampleText);

		ASSERT_EQ(1.0, 1.0);
	}


}

#endif /* _UTF8TEST_H_ */
