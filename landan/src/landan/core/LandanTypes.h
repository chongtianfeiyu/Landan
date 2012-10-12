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
*Class: LandanTypes.h
*Description: 
*Author: jkeon
**********************************/

#ifndef _LANDANTYPES_H_
#define _LANDANTYPES_H_

//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan
{

//Visual Studio Compiler
#if defined(_MSC_VER)
	//UINTs
	typedef unsigned __int8 u8;
	typedef unsigned __int16 u16;
	typedef unsigned __int32 u32;
	typedef unsigned __int64 u64;

	//INTs
	typedef __int8 i8;
	typedef __int16 i16;
	typedef __int32 i32;
	typedef __int64 i64;

	//FLOATs
	typedef float f32;
	typedef double f64;

//GCC Compiler
#elif defined(__GNUC__)
	//UINTs
	typedef unsigned char u8;
	typedef unsigned short u16;
	typedef unsigned int u32;
	typedef unsigned long long u64;

	//INTs
	typedef char i8;
	typedef short i16;
	typedef int i32;
	typedef long long i64;

	//FLOATs
	typedef float f32;
	typedef double f64;


#endif


#ifdef UNICODE
	typedef wchar_t tchar;

	#define	LT(txt) _LT(txt)
	#define _LT(txt) L##txt
#else
	//Characters, Strings, Streams
	typedef char tchar;

	//All Landan String Literals should be wrapped in this
	#define	LT(txt)	_LT(txt)
	#define _LT(txt) txt
#endif


	typedef std::basic_filebuf<tchar> tfilebuf;
	typedef std::basic_fstream<tchar> tfstream;
	typedef std::basic_ifstream<tchar> tifstream;
	typedef std::basic_ios<tchar> tios;
	typedef std::basic_iostream<tchar> tiostream;
	typedef std::basic_istream<tchar> tistream;
	typedef std::basic_istringstream<tchar> tistringstream;
	typedef std::basic_ofstream<tchar> tofstream;
	typedef std::basic_ostream<tchar> tostream;
	typedef std::basic_ostringstream<tchar> tostringstream;
	typedef std::basic_streambuf<tchar> tstreambuf;
	typedef std::basic_string<tchar> tstring;
	typedef std::basic_stringbuf<tchar> tstringbuf;
	typedef std::basic_stringstream<tchar> tstringstream;

	extern tostream& tcout;
	extern tistream& tcin;
	extern tostream& tcerr;
	extern tostream& tclog;




}


#endif /* _LANDANTYPES_H_ */
