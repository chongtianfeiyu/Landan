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
	// GLOBALS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


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

	

	//PUBLIC VARIABLES
	public:
	

	//PROTECTED FUNCTIONS
	protected:

	//PROTECTED VARIABLES
	protected:



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

	//////////////////////////////////////////////////////////////////////
	// STATICS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


}
#endif
