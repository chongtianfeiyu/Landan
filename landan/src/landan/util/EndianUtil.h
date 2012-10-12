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
 *Class: EndianUtil
 *Description:
 *Author: jkeon
 **********************************/

#ifndef _ENDIANUTIL_H_
#define _ENDIANUTIL_H_

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan
{

//////////////////////////////////////////////////////////////////////
// UNIONS ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

union F32_AS_U32
{
	u32 uValue;
	f32 fValue;
};

union F64_AS_U64
{
	u64 uValue;
	f64 fValue;
};

union CHAR16_AS_SHORT
{
	unsigned char cValue[2];
	short sValue;
};

//////////////////////////////////////////////////////////////////////
// ENUMS /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace endian
{
	enum ENDIAN_TYPE
	{
		LITTLE_ENDIAN = 0,
		BIG_ENDIAN = 1
	};
}

//////////////////////////////////////////////////////////////////////
// ENDIAN FUNCTIONS //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

inline endian::ENDIAN_TYPE DetermineSystemEndianess()
{
	CHAR16_AS_SHORT swapper;
	swapper.cValue[0] = 1;
	swapper.cValue[1] = 0;
	short value = swapper.sValue;
	if (value == 1)
	{
		return endian::LITTLE_ENDIAN;
	}
	else
	{
		return endian::BIG_ENDIAN;
	}
}

inline u16 SwapUInt16(u16 value)
{
	//Swap the Bytes by extracting the bytes needed shifting them to the desired location and then stiching them together with an OR
	return ((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8);
}

inline u32 SwapUInt32(u32 value)
{
	//Swap the Bytes by extracting the bytes needed shifting them to the desired location and then stiching them together with an OR
	return ((value & 0xFF000000) >> 24) | ((value & 0x000000FF) << 24)
			| ((value & 0x00FF0000) >> 8) | ((value & 0x0000FF00) << 8);
}

inline u64 SwapUInt64(u64 value)
{
	//Swap the Bytes by extracting the bytes needed shifting them to the desired location and then stiching them together with an OR
	return ((value & 0xFF00000000000000) >> 56)
			| ((value & 0x00000000000000FF) << 56)
			| ((value & 0x00FF000000000000) >> 40)
			| ((value & 0x000000000000FF00) << 40)
			| ((value & 0x0000FF0000000000) >> 24)
			| ((value & 0x0000000000FF0000) << 24)
			| ((value & 0x000000FF00000000) >> 8)
			| ((value & 0x00000000FF000000) << 8);
}

inline i16 SwapInt16(i16 value)
{
	//Swap the Bytes by extracting the bytes needed shifting them to the desired location and then stiching them together with an OR
	return ((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8);
}

inline i32 SwapInt32(i32 value)
{
	//Swap the Bytes by extracting the bytes needed shifting them to the desired location and then stiching them together with an OR
	return ((value & 0xFF000000) >> 24) | ((value & 0x000000FF) << 24)
			| ((value & 0x00FF0000) >> 8) | ((value & 0x0000FF00) << 8);
}

inline i64 SwapInt64(i64 value)
{
	//Swap the Bytes by extracting the bytes needed shifting them to the desired location and then stiching them together with an OR
	return ((value & 0xFF00000000000000) >> 56)
			| ((value & 0x00000000000000FF) << 56)
			| ((value & 0x00FF000000000000) >> 40)
			| ((value & 0x000000000000FF00) << 40)
			| ((value & 0x0000FF0000000000) >> 24)
			| ((value & 0x0000000000FF0000) << 24)
			| ((value & 0x000000FF00000000) >> 8)
			| ((value & 0x00000000FF000000) << 8);
}

inline f32 SwapFloat32(f32 value)
{
	F32_AS_U32 swapper;
	swapper.fValue = value;
	swapper.uValue = SwapUInt32(swapper.uValue);
	return swapper.fValue;
}

inline f64 SwapFloat64(f64 value)
{
	F64_AS_U64 swapper;
	swapper.fValue = value;
	swapper.uValue = SwapUInt64(swapper.uValue);
	return swapper.fValue;
}

}
#endif
