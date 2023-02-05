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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 - Compilers, Lab Section: [012]
* Assignment: A12.
* Date: Jan 25 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for Julius */

/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 7: FUL = Full */
/* TO_DO: BIT 6: EMP: Empty */
/* TO_DO: BIT 5: REL = Relocation */
/* TO_DO: BIT 4: END = EndOfBuffer */
#define SETFULBIT 0x80				/* (1000.0000)_2 = (0x80)_16 = (128) */
#define RESETFULBIT 0x7F			/* (0111.1111)_2 = (0x7F)_16 = (127) */
#define CHECKFULBIT 0x80				

#define SETEMPBIT 0x40				/* (0100.0000)_2 = (0x40)_16 = (64) */
#define RESETEMPBIT 0xBF			/* (1011.1111)_2 = (0xBF)_16 = (191) */
#define CHECKEMPBIT 0x40				

#define SETRELBTI 0x20				/* (0010.0000)_2 = (0x20)_16 = (32) */
#define RESETRELBIT 0xDF			/* (1101.1111)_2 = (0xDF)_16 = (223) */
#define CHECKRELBIT 0x20					

#define SETENDBIT 0x20				/* (0001.0000)_2 = (0x10)_16 = (16) */
#define RESETENDBIT 0xEF			/* (1110.1111)_2 = (0xEF)_16 = (239) */
#define CHECKENDBIT 0x20				

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	juju_int mark;			/* the offset to the mark position (in chars) */
	juju_int read;			/* the offset to the get a char position (in chars) */
	juju_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	juju_char*	content;			/* pointer to the beginning of character array (character buffer) */
	juju_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	juju_int		increment;			/* character array increment factor */
	juju_int		mode;				/* operational mode indicator */
	juju_uByte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;			/* Offset / position field */
	juju_int		histogram[NCHAR];	/* Statistics of chars */
	juju_int		numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(juju_int, juju_int, juju_int);
ReaderPointer	readerAddChar		(ReaderPointer const, juju_char);
juju_bool		readerClear		    (ReaderPointer const);
juju_bool		readerFree		    (ReaderPointer const);
juju_bool		readerIsFull		(ReaderPointer const);
juju_bool		readerIsEmpty		(ReaderPointer const);
juju_bool		readerSetMark		(ReaderPointer const, juju_int);
juju_int		readerPrint		    (ReaderPointer const);
juju_int		readerLoad			(ReaderPointer const, FILE* const);
juju_bool		readerRecover		(ReaderPointer const);
juju_bool		readerRetract		(ReaderPointer const);
juju_bool		readerRestore		(ReaderPointer const);
/* Getters */
juju_char		readerGetChar		(ReaderPointer const);
juju_char*	readerGetContent	(ReaderPointer const, juju_int);
juju_int		readerGetPosRead	(ReaderPointer const);
juju_int		readerGetPosWrte	(ReaderPointer const);
juju_int		readerGetPosMark	(ReaderPointer const);
juju_int		readerGetSize		(ReaderPointer const);
juju_int		readerGetInc		(ReaderPointer const);
juju_int		readerGetMode		(ReaderPointer const);
juju_uByte		readerGetFlags		(ReaderPointer const);
juju_int		readerShowStat		(ReaderPointer const);
juju_int		readerNumErrors		(ReaderPointer const);

#endif
