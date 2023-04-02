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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

juju_void startParser() {
	lookahead = tokenizer();
	
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
juju_void matchToken(juju_int tokenCode, juju_int tokenAttribute) {
	juju_int matchFlag = 1;
	switch (lookahead.code) {	
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
		
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
juju_void syncErrorHandler(juju_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
juju_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	case COMM:
		printf("COMM\n");
		break;
	case VARID_T:
		printf("VARID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case INL_T:
		printf("INL_T\t\t%d\n", t.attribute.intValue);
		break;
	case DBL_QU:
		printf("DBL_QU\n");
		break;
	case ASSIGN_OP:
		printf("ASSIGN_OP\n");
		break;
	case EQUAL_OP:
		printf("EQUAL_OP\n");
		break;
	case ARTH_OP_T:
		printf("ARTH_OP_T\n");
		break;
	
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main)}.
 ***********************************************************
 */
juju_void program() {
	while (lookahead.code == COMM) {
		matchToken(COMM, NO_ATTR);
	}  //ignore comment
	switch (lookahead.code) {
	case KW_T: //if main
		if(lookahead.attribute.codeType == 8){
			//if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
				matchToken(KW_T, KW_main);
				printf("%s%s\n", STR_LANGNAME, ": main parsed");
				matchToken(LBR_T, NO_ATTR);
				
				statements();
				
				matchToken(RBR_T, NO_ATTR);
				break;
			}
			else {
			printError();
			}
		
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

///*
// ************************************************************
// * dataSession
// * BNF: <dataSession> -> data { <opt_varlist_declarations> } XXX
// * FIRST(<program>)= {KW_T (KW_data)}.
// ***********************************************************
// */
//juju_void dataSession() {
//	//matchToken(KW_T, KW_data);
//	//matchToken(LBR_T, NO_ATTR);
//	optVarListDeclarations();
//	//matchToken(RBR_T, NO_ATTR);
//	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
//}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
juju_void optVarListDeclarations() {
	if (lookahead.code == EOS_T) {
		matchToken(EOS_T, NO_ATTR);
	}
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType == 0) { //keyword int
			matchToken(KW_T, KW_int);
			
			variableID();
			assignmentStatement(); 
		}
		else if (lookahead.attribute.codeType == 3) { //keyword string
			matchToken(KW_T, KW_string);
			
			variableID();
			assignmentStatement();
		}
		break;
	default:
		printError();
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}
juju_void variableID() {
	matchToken(VARID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Variable ID parsed");
}
/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
//juju_void codeSession() {
//	//matchToken(KW_T, KW_code);
//	//matchToken(LBR_T, NO_ATTR);
//	statements();
//	//matchToken(RBR_T, NO_ATTR);
//	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
//}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print), MNID_T(input) }
 ***********************************************************
 */
juju_void optionalStatements() {
	switch (lookahead.code) {
	case MNID_T: //print
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}

	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
juju_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input), MNID_T(print) }
 ***********************************************************
 */
juju_void statementsPrime() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
juju_void statement() {
	switch (lookahead.code) {
	//case EOS_T:
		
	case KW_T: //keyward table
		switch (lookahead.attribute.codeType) {
		case KW_do:
			matchToken(KW_T, KW_do);
			break;
		case KW_else:
			matchToken(KW_T, KW_else);
			break;
		case KW_if:
			matchToken(KW_T, KW_if);
			break;
		case KW_while:
			matchToken(KW_T, KW_while);
			break;
		case KW_then:
			matchToken(KW_T, KW_then);
			break;
		case KW_string:
			optVarListDeclarations();
			break;
		case KW_float:
			optVarListDeclarations();
			break;
		case KW_int:
			optVarListDeclarations();
			break;
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		break;
	default:
		printError();
	}
	if (lookahead.code == EOS_T) {
		matchToken(EOS_T, NO_ATTR);
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
juju_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
juju_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

juju_void assignmentStatement() {
	matchToken(ASSIGN_OP, NO_ATTR);
	variableExpressions();
	//if(lookahead.code==EOS_T)
		//matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Assignment statement parsed");
}

juju_void variableExpressions() {
	variableExpression();
	variableExpressionsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Variable expressions parsed");
}

juju_void variableExpression() {
	switch (lookahead.code) {
	case VARID_T:
		matchToken(VARID_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case ARTH_OP_T:
		arithmeticExpression();
		break;
	case STR_T:
		stringExpression();
		break;
	case MNID_T:
		statement();
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Variable expression parsed");
}

juju_void variableExpressionsPrime() {
	switch (lookahead.code) {
	case ARTH_OP_T:
		variableExpressions();
	default:
		; // empty string
	}
}

juju_void arithmeticExpression() {
	switch (lookahead.code) {
	case ARTH_OP_T:
		switch (lookahead.attribute.arithmeticOperator) {
		case OP_ADD:
			addArithmeticExpression();
		case OP_SUB:
			
			break;
		case OP_MUL:
			multiArithmeticExpression();
			break;
		case OP_DIV:
			break;
		}
		break;
	case VARID_T:
	case INL_T:
		primaryArithmeticExpression();
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Arithmetic expression parsed");
}
juju_void addArithmeticExpression() {
	switch (lookahead.code) {
	case INL_T:
	case VARID_T:
		multiArithmeticExpression();
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Additive arithmetic expression parsed");
}


juju_void multiArithmeticExpression() {
	matchToken(ARTH_OP_T, NO_ATTR);
	switch (lookahead.code) {
	case INL_T:
	case VARID_T:
		primaryArithmeticExpression();
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Multiplicative arithmetic expression parsed");
}
juju_void primaryArithmeticExpression() {
	switch (lookahead.code) {
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case VARID_T:
		matchToken(VARID_T, NO_ATTR);
		break;
	default:
		printError();
		break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Primary arithmetic expression parsed");
}


juju_void stringExpression() {
	matchToken(STR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": String expression parsed");
}