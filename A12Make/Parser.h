/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Soomin Lee
* Professors: Paulo Sousa
************************************************************
----------------------------------------------------------
|                                                        |
|....................Language JUJU...................... |
|                                                        |
|               *  *    *      *  *    *                 |
|               *  *    *      *  *    *                 |
|               *  *    *      *  *    *                 |
|               *  *    *      *  *    *                 |
|           ****    ****   ****    ****                  |
|                                                        |
|                 ALGONQUIN COLLEGE  2023W               |
|                                                        |
----------------------------------------------------------

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern juju_int line;
extern Token tokenizer();
extern juju_char* keywordTable[];
juju_int syntaxErrorNumber = 0;

#define STR_LANGNAME	"Juju"
#define LANG_WRTE		"print"
#define LANG_READ		"input"
#define LANG_MAIN		"main"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	//KW_return,
	//KW_int,
	//KW_float,
	//KW_string,
	KW_if,
	KW_then,
	KW_else,
	KW_while,
	KW_do
};

/* Function definitions */
juju_void startParser();
juju_void matchToken(juju_int, juju_int);
juju_void syncErrorHandler(juju_int);
juju_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
juju_void codeSession();
juju_void dataSession();
juju_void optVarListDeclarations();
juju_void optionalStatements();
juju_void outputStatement();
juju_void outputVariableList();
juju_void program();
juju_void statement();
juju_void statements();
juju_void statementsPrime();

#endif
