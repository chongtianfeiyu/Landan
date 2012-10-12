/*********************************
*Class: Main.cpp
*Description: 
*Author: jkeon
**********************************/

//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <tests/ByteArrayTest.h>
#include <tests/UTF8Test.h>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int response = RUN_ALL_TESTS();
  std::cin.get();
  return response;
}

	

