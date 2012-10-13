# Landan

Landan is a C++ Framework inspired by the Flash/AIR API to allow you to create applications natively. Initially it will target Windows Desktop but may be extended for other operating systems or mobile platforms.

## Disclaimer

Many aspects of this project will change over time and it is not recommended for any usage other than personal interest at this point.

## Installation

_Other compilers are intended to be supported in the future but no ETA as of yet._

### Visual Studio 2010

Landan uses [GTest 1.6.0](http://code.google.com/p/googletest/) for unit testing. The LandanTests project expects gtest to be located in a certain location and compiled a certain way.

1. Download **gtest-1.6.0**
2. Extract to the root directory of the **landan** directory.
	1. You should have .git, gtest-1.6.0, landan, nowide_standalone, .gitattributes, .gitignore, LICENSE.md and README.md all in the same directory.
3. Inside gtest-1.6.0/msvc open **gtest-md.sln**
4. Build the entire solution in both **Debug** and **Release** mode. This will place the proper libraries where the **LandanTests** project expects them.
5. Open **Landan.sln** in landan/compilers/vs2010/Landan/

Landan also uses [Boost NoWide](http://cppcms.com/files/nowide/html/) for dealing with UTF-8 strings on Windows. For more information on why this is the case please see [UTF-8 Everywhere](http://www.utf8everywhere.org/).

## Launching

For now, the DemoApplication project is the default. You may switch it to LandanTests to launch the unit tests. Ideally I'd like to get this to a better workflow but I'm unsure how to accomplish it in Visual Studio. Being tracked on [StackOverflow](http://stackoverflow.com/questions/12877528/visual-studio-2010-multiple-projects-launch-after-previous-project-complete).

## Strings

Strings are considered UTF-8 encoded internally.


	
	
