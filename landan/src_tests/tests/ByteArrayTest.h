/*********************************
 *Class: ByteArrayTest.h
 *Description: 
 *Author: jkeon
 **********************************/

#ifndef _BYTEARRAYTEST_H_
#define _BYTEARRAYTEST_H_

//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <landan/core/LandanTypes.h>
#include <landan/util/ByteArray.h>

//////////////////////////////////////////////////////////////////////
// MACROS ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan
{

//////////////////////////////////////////////////////////////////////
// CLASS DECLARATION /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class ByteArrayTest : public ::testing::Test
{

protected:
	virtual ~ByteArrayTest(){

	}
	virtual void SetUp()
	{
		be = new ByteArray(1024);
		be->SetEndianess(endian::BIG_ENDIAN);
		be->SetPosition(7);


		le = new ByteArray(1024);
		le->SetEndianess(endian::LITTLE_ENDIAN);
		le->SetPosition(7);
	}
	virtual void TearDown() {
		if (be)
		{
			delete be;
			be = 0;
		}
		if (le)
		{
			delete le;
			le = 0;
		}
	}


	ByteArray *be;
	ByteArray *le;


};

TEST_F(ByteArrayTest, TestU8)
{
	u8 tu8 = 0x9D;
	be->WriteUInt8(tu8);
	le->WriteUInt8(tu8);

	be->SetPosition(7);
	le->SetPosition(7);

	u8 abtu8 = be->ReadUInt8();
	u8 altu8 = le->ReadUInt8();

	ASSERT_EQ(tu8, abtu8);
	ASSERT_EQ(tu8, altu8);
}

TEST_F(ByteArrayTest, TestU16)
{
	u16 tu16 = 0x9D8A;
	be->WriteUInt16(tu16);
	le->WriteUInt16(tu16);

	be->SetPosition(7);
	le->SetPosition(7);

	u16 abtu16 = be->ReadUInt16();
	u16 altu16 = le->ReadUInt16();

	ASSERT_EQ(tu16, abtu16);
	ASSERT_EQ(tu16, altu16);
}

TEST_F(ByteArrayTest, TestU32)
{
	u32 tu32 = 0xFAEADACA;
	be->WriteUInt32(tu32);
	le->WriteUInt32(tu32);

	be->SetPosition(7);
	le->SetPosition(7);

	u32 abtu32 = be->ReadUInt32();
	u32 altu32 = le->ReadUInt32();

	ASSERT_EQ(tu32, abtu32);
	ASSERT_EQ(tu32, altu32);
}

TEST_F(ByteArrayTest, TestU64)
{
	u64 tu64 = 0xFAEADACABA9A8A7A;
	be->WriteUInt64(tu64);
	le->WriteUInt64(tu64);

	be->SetPosition(7);
	le->SetPosition(7);

	u64 abtu64 = be->ReadUInt64();
	u64 altu64 = le->ReadUInt64();

	ASSERT_EQ(tu64, abtu64);
	ASSERT_EQ(tu64, altu64);
}

TEST_F(ByteArrayTest, TestI8)
{
	i8 ti8 = 0x10;
	be->WriteInt8(ti8);
	le->WriteInt8(ti8);

	be->SetPosition(7);
	le->SetPosition(7);

	i8 abti8 = be->ReadInt8();
	i8 alti8 = le->ReadInt8();

	ASSERT_EQ(ti8, abti8);
	ASSERT_EQ(ti8, alti8);
}

TEST_F(ByteArrayTest, TestI16)
{
	i16 ti16 = 0x2328;
	be->WriteInt16(ti16);
	le->WriteInt16(ti16);

	be->SetPosition(7);
	le->SetPosition(7);

	i16 abti16 = be->ReadInt16();
	i16 alti16 = le->ReadInt16();

	ASSERT_EQ(ti16, abti16);
	ASSERT_EQ(ti16, alti16);
}

TEST_F(ByteArrayTest, TestI32)
{
	i32 ti32 = 0xFAEADACA;
	be->WriteInt32(ti32);
	le->WriteInt32(ti32);

	be->SetPosition(7);
	le->SetPosition(7);

	i32 abti32 = be->ReadInt32();
	i32 alti32 = le->ReadInt32();

	ASSERT_EQ(ti32, abti32);
	ASSERT_EQ(ti32, alti32);
}

TEST_F(ByteArrayTest, TestI64)
{
	i64 ti64 = 0xFAEADACABA9A8A7A;
	be->WriteInt64(ti64);
	le->WriteInt64(ti64);

	be->SetPosition(7);
	le->SetPosition(7);

	i64 abti64 = be->ReadInt64();
	i64 alti64 = le->ReadInt64();

	ASSERT_EQ(ti64, abti64);
	ASSERT_EQ(ti64, alti64);
}

TEST_F(ByteArrayTest, TestF32)
{
	f32 tf32 = 123.456f;
	be->WriteFloat32(tf32);
	le->WriteFloat32(tf32);

	be->SetPosition(7);
	le->SetPosition(7);

	f32 abtf32 = be->ReadFloat32();
	f32 altf32 = le->ReadFloat32();

	ASSERT_FLOAT_EQ(tf32, abtf32);
	ASSERT_FLOAT_EQ(tf32, altf32);
}

TEST_F(ByteArrayTest, TestF64)
{
	f64 tf64 = 123.456f;
	be->WriteFloat64(tf64);
	le->WriteFloat64(tf64);

	be->SetPosition(7);
	le->SetPosition(7);

	f64 abtf64 = be->ReadFloat64();
	f64 altf64 = le->ReadFloat64();

	ASSERT_DOUBLE_EQ(tf64, abtf64);
	ASSERT_DOUBLE_EQ(tf64, altf64);
}




} /* namespace landan */
#endif /* _BYTEARRAYTEST_H_ */
