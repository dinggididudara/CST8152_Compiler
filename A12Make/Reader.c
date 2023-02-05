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
* Purpose: This file is the main code for Reader (.c)
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
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(juju_int size, juju_int increment, juju_int mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the values according to parameters */
	size = READER_DEFAULT_SIZE;
	increment = READER_DEFAULT_INCREMENT;
	mode = MODE_FIXED;
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	readerPointer->content = (juju_char*)malloc(size);
	/* TO_DO: Defensive programming */
	if (!readerPointer->content) return NULL;
	/* TO_DO: Initialize the histogram */
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* TO_DO: Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;
	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->flags |= SETEMPBIT;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, juju_char ch) {
	juju_char* tempReader = NULL;
	juju_int newSize = 0;
	/* TO_DO: Defensive programming: check buffer and valid char (increment numReaderErrors) */
	if ((!readerPointer)) {
		return NULL;
	}

	if ((ch >= NCHAR) || (ch < 0)) {
		readerPointer->numReaderErrors;
			return NULL;
	}
	/* TO_DO: Reset Realocation */
	readerPointer->flags &= RESETRELBIT;
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (juju_int)sizeof(juju_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */

	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags &= RESETFULBIT;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize >= READER_MAX_SIZE) {
				readerPointer->flags |= SETFULBIT;
				return readerPointer;
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize >= READER_MAX_SIZE) {
				readerPointer->flags |= SETFULBIT;
				return readerPointer;
			}
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = realloc(readerPointer->content, newSize);
		/* TO_DO: Defensive programming */
		if (!tempReader) return NULL;
		/* TO_DO: Check Relocation */
		if (tempReader != readerPointer->content) {
			readerPointer->flags |= CHECKRELBIT;
		}
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_bool readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) return JUJU_FALSE;
	/* TO_DO: Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG;
	readerPointer->position.mark, readerPointer->position.read, readerPointer->position.wrte = 0;
	return JUJU_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_bool readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return JUJU_FALSE;
	/* TO_DO: Free pointers */
	
	free(readerPointer);
	return JUJU_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_uByte readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) return JUJU_FALSE;
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer->flags == CHECKFULBIT) return JUJU_TRUE;
	return JUJU_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_bool readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) return JUJU_FALSE;
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags == CHECKEMPBIT) return JUJU_TRUE;
	return JUJU_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_uByte readerSetMark(ReaderPointer const readerPointer, juju_int mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark >= readerPointer->position.wrte)
		return JUJU_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return JUJU_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerPrint(ReaderPointer const readerPointer) {
	juju_int cont = 0;
	juju_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	while (c < 0 || c>127) {
		c = readerGetChar(readerPointer);
	}
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);

		if ((readerPointer->flags) == CHECKENDBIT) {
			break;
		}
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	juju_int size = 0;
	juju_char c;
	/* TO_DO: Defensive programming */
	c = (juju_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);

			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	if (size > READER_MAX_SIZE) {
		return READER_ERROR;
	}

	if (size != 0) {
		readerPointer->flags &= RESETEMPBIT;
	}
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_uByte readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Recover positions */
	if (!readerPointer) {
		return JUJU_FALSE;
	}
	readerPointer->position.mark, readerPointer->position.read = 0;
	return JUJU_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_uByte readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Retract (return 1 pos read) */
	if (!readerPointer || readerPointer->position.read <= 0)
	{
		return JUJU_FALSE;
	}
	readerPointer->position.read -= 1; //decrement the read counter
	return JUJU_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_uByte readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Restore positions (read/mark) */
	if (!readerPointer) {
		return JUJU_FALSE;
	}
	readerPointer->position.read = readerPointer->position.mark;
	return JUJU_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) return '\0';
	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->position.read == readerPointer->position.wrte) {
		/* TO_DO: Set EOB flag */
		readerPointer->flags |= SETENDBIT;
		return '\0';
	}
	
	/* TO_DO: Reset EOB flag */
	readerPointer->flags &= RESETENDBIT;

	return readerPointer->content[readerPointer->position.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_char* readerGetContent(ReaderPointer const readerPointer, juju_int pos) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return content (string) */
	if (readerPointer && pos < readerPointer->position.wrte) {
		return (readerPointer->content + pos);
	}
	return NULL;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return read */
	if (readerPointer) {
		return (readerPointer->position.read);
	}
	return 0;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return wrte */
	if (readerPointer) {
		return (readerPointer->position.wrte);
	}
	return 0;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mark */
	if (readerPointer) {
		return (readerPointer->position.mark);
	}
	return 0;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return size */
	if (readerPointer)
	{
		return (readerPointer->size);
	}
	return 0;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return increment */
	if (readerPointer) {
		return (readerPointer->increment);
	}
	return 0;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	if(readerPointer) {
		return(readerPointer->mode);
	}
	return 0;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_uByte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return flags */
	if (readerPointer) {
		return (readerPointer->flags);
	}
	return 0;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerShowStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */

	/* TO_DO: Updates the histogram */
	if (readerPointer) {
		juju_int c = 0;
		for (juju_int i = 0; i < 128; i++) {
			if (readerPointer->histogram[i] != 0) c++;
		}
		return c;
	}

	return 0;
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
juju_int readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* else {
		return readerPointer->numReaderErrors;
	} */
	/* TO_DO: Updates the histogram */
	if (readerPointer) {
		juju_int c = 0;
		for (juju_int i = 0; i < 128; i++) {
			if (readerPointer->histogram[i] != 0) {
				c++;
			}
			return c;
		}
		return 0;
	}
	return 0;
}
