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
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	ASSIGN_OP,  /* 12: Assign operator*/
	EQUAL_OP,   /* 13: Equal = operator*/
	PLUS_OP,    /* 14: + operator*/
	MINUS_OP,   /* 15: - operator*/
	MULTI_OP,   /* 16: * operator*/
	DIV_OP,     /* 17: / operator*/
	COMM,       /* 18: comment # */
	DBL_QU,      /* 20: double quote */
	VARID_T			/* 21: Variable name identifier token */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	juju_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	juju_int intValue;						/* integer literal attribute (value) */
	juju_int keywordIndex;					/* keyword index in the keyword table */
	juju_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	juju_float floatValue;					/* floating-point literal attribute (value) */
	juju_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	juju_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	juju_uByte flags;			/* Flags information */
	union {
		juju_int intValue;				/* Integer value */
		juju_float floatValue;			/* Float value */
		juju_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	juju_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL0 '#'
#define CHRCOL3 '_'
#define CHRCOL4 '"'
#define CHRCOL5 '('
#define CHRCOL7 '.'



/* These constants will be used on VID / MID function */
#define MNIDPREFIX '('

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	13		/* Error state with no retract */
#define ESWR	0		/* Error state with retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 8

/* TO_DO: Transition table - type of states defined in separate table */
static juju_int transitionTable[][TABLE_COLUMNS] = {
	/*   #,  [0-9],[A..Z], _  ,   "  ,   ( ,  others, .
	   C(0),  D(1), L(2), U(3),  Q(4), M(5),  O(6)   p(7) */
	{     1,     3,    5, ESNR,     8, ESNR, ESNR,  ESNR}, // S0: NOAS
	{     2,     1,    1,    1,     1,    1,    1,     1}, // S1: NOAS
	{    FS,    FS,   FS,   FS,    FS,   FS,   FS,    FS}, // S2: FSNR (Comment)
	{  ESNR,    4, ESNR, ESNR,  ESNR, ESNR, ESNR,   ESNR}, // S3: NOAS
	{    FS,    FS,   FS,   FS,    FS,   FS,   FS,    FS}, // S4: FSWR (Integer Literal, IL)
	{  ESNR,     5,    5,    5,  ESNR,    6,    7,    10}, // S5: NOAS
	{    FS,    FS,   FS,   FS,    FS,   FS,   FS,    FS}, // S6: ASNR (MVID, METHOD)
	{    FS,    FS,   FS,   FS,    FS,   FS,   FS,    FS}, // S7: KEY (KEYWORD)
	{     8,     8,    8,    8,     9,    8,    8,     8}, // S8: NOAS
	{    FS,    FS,   FS,   FS,    FS,    FS,  FS,    FS}  // S9: FSWR (String Literal, SL)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static juju_int stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 - COMMENT */
	NOFS, /* 03 */
	FSWR, /* 04 (IL) */
	NOFS, /* 05 */
	FSWR, /* 06 (MVID) - METHOD */
	FSWR, /* 07 (KEYWORD)  */
	NOFS, /* 08 */
	FSWR, /* 09 (SL) */
	FSWR  /* 10 (VARID) - VARIABLE NAME */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
juju_int startScanner(ReaderPointer psc_buf);
Token tokenizer(juju_void);
static juju_int nextClass(juju_char c);				/* character class function */
static juju_int nextState(juju_int, juju_char);		/* state machine function */
juju_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(juju_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(juju_char lexeme[]);
Token funcID	(juju_char lexeme[]);
Token funcKEY	(juju_char lexeme[]);
Token funcErr	(juju_char lexeme[]);
Token funcIL	(juju_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	NULL,		/* -	[02] - comment */
	NULL,		/* -    [03]  */
	funcIL,		/* IL   [04] - INTEGER LITERAL */
	NULL,		/* -    [05]  */
	funcID,		/* ID   [06] - FUNCTION ID */
	funcKEY,	/* KEY  [07] - KEYWORD */
	NULL,		/* -    [08]  */
	funcSL,		/* SL   [09] - STRING LITERAL */
	funcID		/* VAR  [10] - VARIABLE NAME */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 10

/* TO_DO: Define the list of keywords */
static juju_char* keywordTable[KWT_SIZE] = {
	"int",
	"float",
	"string",
	"if",
	"then",
	"else",
	"while",
	"do",
	"main",
	"print"
};

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	juju_char indentationCharType;
	juju_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
juju_int numScannerErrors;

#endif
