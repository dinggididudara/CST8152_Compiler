#..............................................................
# CMakeList.txt : CMake project for Compilers, W23.
#..............................................................
#
#
#----------------------------------------------------------
#|                                                        |
#|....................Language JUJU...................... |
#|                                                        |
#|               *  *    *      *  *    *                 |
#|               *  *    *      *  *    *                 |
#|               *  *    *      *  *    *                 |
#|               *  *    *      *  *    *                 |
#|           ****    ****   ****    ****                  |
#|                                                        |
#|                 ALGONQUIN COLLEGE  2023W               |
#|                                                        |
#----------------------------------------------------------


cmake_minimum_required (VERSION 3.8)

project ("JujuCompiler")

# Add source to this project's executable: check name and dependences
add_executable (JujuCompiler
	"Compilers.h"	"Compilers.c"
	"Reader.h"		"Reader.c"		"MainReader.c"
		"Scanner.c"		"MainScanner.c"
#	"Parser.h"		"Parser.c"		"MainParser.c"
)

# TO_DO: Add tests and install targets if needed.
