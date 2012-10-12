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
*Class: ByteArray
*Description:
*Author: jkeon
**********************************/

#ifndef _BYTEARRAY_H_
#define _BYTEARRAY_H_


//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <landan/core/LandanTypes.h>
#include <landan/util/EndianUtil.h>

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// CLASS DECLARATION /////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	/**
	 * A ByteArray is an Array of Bytes you can manipulate
	 */
	class ByteArray {

	//PUBLIC FUNCTIONS
	public:
		ByteArray(u32 length = 0);
		~ByteArray();

		u32 GetPosition();
		void SetPosition(u32 position);

		u32 GetLength();

		endian::ENDIAN_TYPE GetEndianess();
		void SetEndianess(endian::ENDIAN_TYPE endianess);

		u8* GetRawBytes();

		void WriteUInt8(u8 value);
		void WriteUInt16(u16 value);
		void WriteUInt32(u32 value);
		void WriteUInt64(u64 value);

		void WriteInt8(i8 value);
		void WriteInt16(i16 value);
		void WriteInt32(i32 value);
		void WriteInt64(i64 value);

		void WriteFloat32(f32 value);
		void WriteFloat64(f64 value);

		u8 ReadUInt8();
		u16 ReadUInt16();
		u32 ReadUInt32();
		u64 ReadUInt64();

		i8 ReadInt8();
		i16 ReadInt16();
		i32 ReadInt32();
		i64 ReadInt64();

		f32 ReadFloat32();
		f64 ReadFloat64();

	//PRIVATE FUNCTIONS
	private:
		ByteArray(const ByteArray& other);
		ByteArray& operator = (const ByteArray& other);

	//PRIVATE VARIABLES
	private:
		u8 *p_data;
		u32 m_length;
		u32 m_position;

		endian::ENDIAN_TYPE m_endianess;
		endian::ENDIAN_TYPE m_systemEndianess;
	};

}
#endif
