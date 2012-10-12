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

#include "ByteArray.h"

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {


	//////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS //////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	ByteArray::ByteArray(u32 length)
	:m_length(length)
	{
		if (m_length > 0)
		{
			p_data = new u8[m_length];
		}
		else
		{
			p_data = 0;
		}
		m_position = 0;
		m_endianess = m_systemEndianess = DetermineSystemEndianess();
	}

	//////////////////////////////////////////////////////////////////////
	// DESTRUCTOR ////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	ByteArray::~ByteArray() {
		if (p_data != 0) 
		{
			delete p_data;
			p_data = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////
	// BODY //////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	void ByteArray::WriteUInt8(u8 value)
	{
		p_data[m_position] = value;
		m_position++;
	}
	
	u8 ByteArray::ReadUInt8()
	{
		u8 value = p_data[m_position];
		m_position++;
		return value;
	}

	void ByteArray::WriteUInt16(u16 value)
	{
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapUInt16(value);
		
		//Copy the entire value into the position as dictated by the byte arrays position.
		memcpy(&p_data[m_position], &value, sizeof(value));

		//Update the position
		m_position += 2;
	}

	u16 ByteArray::ReadUInt16()
	{
		//Extract the result by getting the memory address of current position in the byte array and reinterpreting that pointer as a pointer to a uint16 pointer.
		//Then simply dereference the pointer to get the actual value as a uint16
		u16 value = *(reinterpret_cast<u16 *>(&p_data[m_position]));
		
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapUInt16(value);

		//Update the position
		m_position += 2;

		return value;
	}

	void ByteArray::WriteUInt32(u32 value)
	{
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapUInt32(value);
		
		//Copy the entire value into the position as dictated by the byte arrays position.
		memcpy(&p_data[m_position], &value, sizeof(value));

		//Update the position
		m_position += 4;
	}

	u32 ByteArray::ReadUInt32()
	{
		//Extract the result by getting the memory address of current position in the byte array and reinterpreting that pointer as a pointer to a uint16 pointer.
		//Then simply dereference the pointer to get the actual value as a uint32
		u32 value = *(reinterpret_cast<u32 *>(&p_data[m_position]));
		
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapUInt32(value);

		//Update the position
		m_position += 4;

		return value;
	}
	
	void ByteArray::WriteUInt64(u64 value)
	{
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapUInt64(value);
		
		//Copy the entire value into the position as dictated by the byte arrays position.
		memcpy(&p_data[m_position], &value, sizeof(value));

		//Update the position
		m_position += 8;
	}

	u64 ByteArray::ReadUInt64()
	{
		//Extract the result by getting the memory address of current position in the byte array and reinterpreting that pointer as a pointer to a uint16 pointer.
		//Then simply dereference the pointer to get the actual value as a uint64
		u64 value = *(reinterpret_cast<u64 *>(&p_data[m_position]));
		
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapUInt64(value);

		//Update the position
		m_position += 8;

		return value;
	}
	
	
	void ByteArray::WriteInt8(i8 value)
	{
		p_data[m_position] = value;
		m_position++;
	}
	
	i8 ByteArray::ReadInt8()
	{
		i8 value = p_data[m_position];
		m_position++;
		return value;
	}

	void ByteArray::WriteInt16(i16 value)
	{
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapInt16(value);
		
		//Copy the entire value into the position as dictated by the byte arrays position.
		memcpy(&p_data[m_position], &value, sizeof(value));

		//Update the position
		m_position += 2;
	}

	i16 ByteArray::ReadInt16()
	{
		//Extract the result by getting the memory address of current position in the byte array and reinterpreting that pointer as a pointer to a uint16 pointer.
		//Then simply dereference the pointer to get the actual value as a int16
		i16 value = *(reinterpret_cast<i16 *>(&p_data[m_position]));
		
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapInt16(value);

		//Update the position
		m_position += 2;

		return value;
	}

	void ByteArray::WriteInt32(i32 value)
	{
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapInt32(value);
		
		//Copy the entire value into the position as dictated by the byte arrays position.
		memcpy(&p_data[m_position], &value, sizeof(value));

		//Update the position
		m_position += 4;
	}

	i32 ByteArray::ReadInt32()
	{
		//Extract the result by getting the memory address of current position in the byte array and reinterpreting that pointer as a pointer to a uint16 pointer.
		//Then simply dereference the pointer to get the actual value as a int32
		i32 value = *(reinterpret_cast<i32 *>(&p_data[m_position]));
		
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapInt32(value);

		//Update the position
		m_position += 4;

		return value;
	}
	
	void ByteArray::WriteInt64(i64 value)
	{
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapInt64(value);
		
		//Copy the entire value into the position as dictated by the byte arrays position.
		memcpy(&p_data[m_position], &value, sizeof(value));

		//Update the position
		m_position += 8;
	}

	i64 ByteArray::ReadInt64()
	{
		//Extract the result by getting the memory address of current position in the byte array and reinterpreting that pointer as a pointer to a uint16 pointer.
		//Then simply dereference the pointer to get the actual value as a int64
		i64 value = *(reinterpret_cast<i64 *>(&p_data[m_position]));
		
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapInt64(value);

		//Update the position
		m_position += 8;

		return value;
	}

	void ByteArray::WriteFloat32(f32 value)
	{
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapFloat32(value);

		//Copy the entire value into the position as dictated by the byte arrays position.
		memcpy(&p_data[m_position], &value, sizeof(value));

		//Update the position
		m_position += 4;
	}

	f32 ByteArray::ReadFloat32()
	{
		//Extract the result by getting the memory address of current position in the byte array and reinterpreting that pointer as a pointer to a float32 pointer.
		//Then simply dereference the pointer to get the actual value as a float32
		f32 value = *(reinterpret_cast<f32 *>(&p_data[m_position]));

		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapFloat32(value);

		//Update the position
		m_position += 4;

		return value;
	}

	void ByteArray::WriteFloat64(f64 value)
	{
		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapFloat64(value);

		//Copy the entire value into the position as dictated by the byte arrays position.
		memcpy(&p_data[m_position], &value, sizeof(value));

		//Update the position
		m_position += 8;
	}

	f64 ByteArray::ReadFloat64()
	{
		//Extract the result by getting the memory address of current position in the byte array and reinterpreting that pointer as a pointer to a float32 pointer.
		//Then simply dereference the pointer to get the actual value as a float32
		f64 value = *(reinterpret_cast<f64 *>(&p_data[m_position]));

		//Handle Endianess
		value = (m_endianess == m_systemEndianess) ? value : SwapFloat64(value);

		//Update the position
		m_position += 8;

		return value;
	}

	//////////////////////////////////////////////////////////////////////
	// GETTERS/SETTERS ///////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	u32 ByteArray::GetPosition()
	{
		return m_position;
	}

	void ByteArray::SetPosition(u32 position)
	{
		m_position = position;
	}

	endian::ENDIAN_TYPE ByteArray::GetEndianess()
	{
		return m_endianess;
	}

	void ByteArray::SetEndianess(endian::ENDIAN_TYPE endianess)
	{
		m_endianess = endianess;
	}

	u8* ByteArray::GetRawBytes()
	{
		return p_data;
	}

	u32 ByteArray::GetLength()
	{
		return m_length;
	}

}
