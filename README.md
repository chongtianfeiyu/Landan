Landan
======

Landan is a C++ Framework inspired by the Flash/AIR API to allow you to create applications natively. Initially it will target Windows Desktop but may be extended for other operating systems or mobile platforms.


Installation
======

_Other compilers are intended to be supported in the future but no ETA as of yet._

Visual Studio 2010
------

Landan uses [GTest 1.6.0](http://code.google.com/p/googletest/) for unit testing. The LandanTests project expects gtest to be located in a certain location and compiled a certain way.

	* Download **gtest-1.6.0**
	* Extract to the root directory of the **landan** directory.
	** You should have .git, gtest-1.6.0, landan, .gitattributes, .gitignore, and README.md all in the same directory.
	* Inside gtest-1.6.0/msvc open **gtest-md.sln**
	* Build the entire solution in both **Debug** and **Release** mode. This will place the proper libraries where the **LandanTests** project expects them.
	* Open **Landan.sln** in landan/compilers/vs2010/Landan/
	
	
