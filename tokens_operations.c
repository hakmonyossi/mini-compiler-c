#include <stdio.h>
#include "tokens_operations.h"
#include "tokens.h"
#include "tokens.c" 
#include <malloc.h>
#include <string.h>
extern int yylex();


int flagDoneBAckToken = 0;

typedef struct node* list;

typedef struct node{
	int idx;
	token tokenArray[MAX];
	list next;
	list prev;
}node;

list  head = NULL,  tail =NULL , tmpnode=NULL;

void appendnode(node* tmp)
{
	if  (head==NULL)
		{ 
			head =tmp;
			tmp->prev=NULL;
		}
	else 
	{
		tail->next=tmp;
		tmp->prev=tail;
	}
	tail=tmp;
	tmp->next=NULL;
}

token* nextToken()
{
	if(flagDoneBAckToken == 0 )
	
	{ 
		token* t;
		yylex();
		return &tmpnode->tokenArray[tmpnode->idx - 1];
	
	}
	
	else
	{
		
		tmpnode->idx++;
		if (tmpnode->idx == MAX)
		{
			tmpnode=tmpnode->next;
			tmpnode->idx=0;
		}

		flagDoneBAckToken=0;
		return &(tmpnode->tokenArray[tmpnode->idx++]);
	}
}

token* backToken()
{
	flagDoneBAckToken = 1;
	tmpnode->idx--;
	if (tmpnode->idx <= 0)	
	{											 												 
		 tmpnode=tmpnode->prev;
		 (tmpnode->idx) = MAX;
	}
	tmpnode->idx--;
	return &tmpnode->tokenArray[tmpnode->idx];
}

void addnewtokentolist(char* lex,int type, int line)
{
	if (head==NULL || tmpnode->idx==MAX)
	{
		tmpnode=(list)malloc(sizeof(node));
		appendnode(	tmpnode);
		tmpnode->idx=0;
	}

	tmpnode->tokenArray[tmpnode->idx].type=type;
	tmpnode->tokenArray[tmpnode->idx].linenum=line;
	tmpnode->tokenArray[tmpnode->idx].lexeme=(char*)malloc(sizeof(lex)+1);
	strcpy(tmpnode->tokenArray[tmpnode->idx++].lexeme,lex);
}

void match(int tokennumber)
{
	token* tkn=nextToken();
	if ((tkn->type !=tokennumber) && (tkn->type!=EOF) )
	{
		printf("\nAn Error Match At Line %d Lexeme %s .expected token  is: %s",tkn->linenum,tkn->lexeme, getTokenType(tokennumber));
	}
}

char* getTokenType(int tokenNumber)
{
	char* str;
	switch(tokenNumber)
	{
	case 1: 
		{
			str="program";
			break;
		}
	case 2: 
		{
			str="id";
			break;
		}

	case 3: 
		{
			str="number";
			break;
		}
	case 4: 
		{
			str="start";
			break;
		}
	case 5: 
		{
			str="comma";
			break;
		}
	case 6: 
		{
			str=":=";
			break;
		}
	case 7: 
		{
			str="char";
			break;
		}
	case 8: 
		{
			str="integer";
			break;
		}
	case 9: 
		{
			str="[";
			break;
		}
	case 10: 
		{
			str="]";
			break;
		}
	case 11: 
		{
			str="{";
			break;
		}
	case 12: 
		{
			str="}";
			break;
		}
	case 13: 
		{
			str="*";
			break;
		}
	case 14: 
		{
			str=";";
			break;
		}
	case 16: 
		{
			str="cycle";
			break;
		}
	case 17: 
		{
			str="do";
			break;
		}
	case 18: 
		{
			str="otherwise";
			break;
		}
	case 19: 
		{
			str="end_cycle";
			break;
		}
	case 20: 
		{
			str="until";
			break;
		}
	case 21: 
		{
			str="done";
			break;
		}
	case 22: 
		{
			str="ar_op";
			break;
		}
	case 23: 
		{
			str="rel_op";
			break;
		}

	case 24: 
		{
			str="end";
			break;
		}

	case 25: 
		{
			str="when";
			break;
		}

	case 26: 
		{
			str="symbol";
			break;
		}

	default : {
				str="undefined";			  
			  }
	}
	return str;
}

void parse_program()
{
	token* tkn = nextToken();
	
	switch(tkn->type)
	{
		case PROGRAM: 
		{	
			parse_definitions();
			match(START); 
			parse_commands(); 
			match(END); 
			match(EOF); 
			printf("\n Rule:	PROGRAM -> program DEFINITIONS start COMMANDS end ");
 			break;
		}
		default:
			{
				printf("\n An Error: wanted %s token got :  %s  , line no.[%d]","program" ,tkn->lexeme,tkn->linenum);
			} 
	}
	
}

void parse_definitions()
{
	parse_definition();
	parse_definition_tag();
	printf("\nRule: DEFINITIONS -> DEFINITION DEFINITIONS_TAG");
}

void parse_definition_tag()
{
	token* tkn=nextToken();
	switch (tkn->type)
	{
		case SEMICOLON : 
		{
			parse_definitions();		
			printf("\n Rule:	DEFINITIONS_TAG ->;DEFINITIONS");
			break;
		}

		default : 
			{
				printf("\nRule:	DEFINITIONS_ TAG ->  null"); 
				backToken();
			}
	}

}

void parse_definition()
{
	parse_type(); 
	parse_variables_list(); 
	printf("\n Rule: TYPE  VARIABLES_LIST");
}

void parse_type()
{
	token* tkn=nextToken();
	switch(tkn->type)
	{
		case INTEGER: 
		{
			printf("\n Rule:	TYPE -> int");
			break;
		}
		case CHAR: 
		{
			printf("\n Rule:	TYPE -> char");
			break;
		}
		

		default:
			{
				printf("\nAn error : wanted %s and got token %s, line no. [%d] ","char or int",  tkn->lexeme, tkn->linenum);
				while(tkn->type!=EOF && !typefollowtok(tkn))
					{
							tkn=nextToken();
					}
				if(tkn->type!=EOF)
					{
						tkn=backToken();
					}
			}
	}

}

void parse_variables_list()
{
	parse_veriable();  
	parse_veriables_list_tag();   
	printf("\n Rule:	VARIABLES_LIST -> VARIABLE   VARIABLES_LIST_TAG");
}

void parse_veriable()
{
	token* tkn=nextToken();
	switch(tkn->type)
	{
	case ID : 
		{
			parse_variable_tag();
			printf("\n Rule:	VARIABLE -> id VARIABLE_TAG");
			break;
		}

	case POINTER: 
		{
			match(ID);
			printf("\nRule: 	VARIABLE -> *id ");
			break;
		}

	default:
		printf("An Error : wanted token %s and got %S line no.[%d]","* or id ",tkn->lexeme, tkn->linenum); 
		while(tkn->type!=EOF && !veriablefollowtok(tkn))
		{
			tkn=nextToken();
		}
		if(tkn->type!=EOF)
		{
			tkn=backToken();
		}
	}
}

void parse_variable_tag()
{
	token* tkn=nextToken();
	switch (tkn->type)
	{
	case OPEN_SQ_BRACKETS:
		{
			parse_size();
			match(CLOSE_SQ_BRACKETS);
			printf("\n Rule:	VARIABLE_TAG -> [SIZE]");
			break;
		}
	default : 
		{
			printf("\n Rule:	VARIABLE_TAG -> null");
			backToken();
		}
	}
}

void parse_veriables_list_tag()
{
	token* tkn=nextToken();
	switch(tkn->type)
	{
	case COMMA:
		{
			parse_variables_list();
			printf("\n Rule:	VARIABLES_LIST_TAG ->  ,VARIABLES_LIST");
			break;
		}

	default: 
		{
			printf("\n Rule:	VARIABLES_LIST_TAG -> null");
			backToken();
		}
	}
}

void parse_commands()
{
	parse_command();
	parse_commands_tag();
	printf("\n Rule:	COMMANDS -> COMMAND COMMANDS_TAG ");
}

void parse_commands_tag()
{
	token* tkn = nextToken();
	switch(tkn->type)
	{
		case SEMICOLON:
		{
			parse_commands();
			printf("\n Rule:	COMMANDS_TAG -> ;COMMANDS");
			break;
		}
		default:
		{
			printf("\nRule:	COMMANDS_TAG is null");
			backToken();
		}
	}
}

void parse_command() 
{
	token* tkn = nextToken();
	switch(tkn->type)
	{
	case WHEN:
		{
			parse_condition();
			match(DO);
			parse_commands();
			match(OTHERWISE);
			parse_commands();
			match(DONE);
			printf("\n Rule:	COMMAND -> when CONDITION do COMMANDS otherwise COMMANDS done");
			break;
		}

	case ID: 
		{
			backToken();
			parse_reciver();
			match(ASSIGNMENT);
			parse_expression();
			printf("\n Rule:	COMMAND ->  RECEIVER := EXPRESSION");
			break;
		}

		case CYCLE:
		{
			parse_commands();
			match(UNTIL);
			parse_condition();
			match(END_CYCLE);
			printf("\n Rule:	COMMAND -> when CONDITION do COMMANDS otherwise COMMANDS done");
			break;
		}
		
	case OPEN_CL_BRACKETS:
		{
			parse_definitions();
			match(START);
			parse_commands();
			match(CLOSE_CL_BRACKETS);
			printf("\n Rule:	COMMAND -> when CONDITION do COMMANDS otherwise COMMANDS done");
			break;
		}	
		
	default: {
				printf("Error wanted when,  cycle or id and got token %s in line [%d] ",tkn->lexeme,tkn->linenum);
				while(tkn->type!=EOF && !commandfollowtok(tkn))
					{
							tkn=nextToken();
					}
				if(tkn->type!=EOF)
					{
						tkn=backToken();
					}
			 }
		}
}

void parse_expression()
{
	parse_basic_expression();
	parse_expression_tag();
	printf("\n Rule: BASIC_EXPRESSION  EXPRESSION_TAG");
}

void parse_condition()
{
	parse_expression();
	match(REL_OP);
	parse_expression();
	printf("\n Rule:	CONDITION -> EXPRESSION  rel_op  EXPRESSION  ");
}

void parse_reciver()
{
	token* tkn=nextToken();
	switch(tkn->type)
	{
		case ID:
		{
			parse_reciver_tag();
			printf("\n Rule:	RECEIVER -> id RECEIVER_TAG ");
			break;
		}
		default: 
			{
				printf("an error : wanted lexeme or id and got %s in line no.[%d]",tkn->lexeme, tkn->linenum);
				while(tkn->type!=EOF && !reciverfollowtok(tkn))
					{
							tkn=nextToken();
					}
				if(tkn->type!=EOF)
					{
						tkn=backToken();
					}
			}
	}
}

void parse_reciver_tag()
{
	token* tkn=nextToken();
	switch(tkn->type)
	{
	case POINTER:
		{
			printf("\n Rule:	RECEIVER_TAG ->");
			break;
		}
	case OPEN_SQ_BRACKETS:
		{
			parse_expression();
			match(CLOSE_SQ_BRACKETS);
			printf("\n RUle:	RECEIVER_TAG -> [EXPRESSION]");
			break;
		}
	default: 
		{
			printf("\n Rule:	RECEIVER_TAG -> ε");
			backToken();
		}
	}
}  

void parse_basic_expression() 
{
	token* tkn=nextToken();
	switch(tkn->type)
	{

	case NUMBER:
		{
			printf("\n Rule:	BASIC_EXPRESSION  -> number ");
			break;
		}

	case ID:
			{
				parse_basic_expression_tag();
				printf("\n Rule:	BASIC_EXPRESSION  -> id BASIC_EXPRESSION_TAG ");
			break;
			}

	case SYMBOL:
			{
					printf("\n Rule:	BASIC_EXPRESSION -> SYMBOL ");
			break;
			}


	default:
		{
			printf("an error: token wanted: number, symbol or id. token got :  %s , in line [%d]",tkn->lexeme,tkn->linenum);
			while(tkn->type!= EOF && !(basicexpfollow(tkn)))
			{
				tkn=nextToken();
			}
			if (tkn->type !=EOF)
			{
				tkn=backToken();
			}
		}

	}
}

void parse_basic_expression_tag()
{
	token* tkn=nextToken();
	switch(tkn->type)
	{
	case OPEN_SQ_BRACKETS:
		{
			parse_basic_expression();
			match(CLOSE_SQ_BRACKETS);
			printf("\n Rule:	BASIC_EXPRESSION_TAG -> [BASIC_EXPRESSION]");
			break;
		}
	case POINTER:
			{
				printf("\n Rule:	BASIC_EXPRESSION_TAG -> pointer sign");
				break;
			}
	default:
			{
			printf("\n Rule:	BASIC_EXPRESSION_TAG is null");
			backToken();
	      	}

	}
}

void parse_expression_tag()
{
	token* tkn=nextToken();
	switch(tkn->type)
	{
	case AR_OP:
		{
			parse_basic_expression();
			printf("\n Rule:	EXPRESSION_TAG -> ar_op BASIC_EXPRETION");
			break;
		}
	default:
			{
			printf("\n Rule:	EXPRESSION_TAG is null ");
			backToken();
	      	}

	}

}

void parse_size()
{
	token* tkn=nextToken();
	switch(tkn->type)
	{
	case NUMBER:
		{
			printf("\n Rule:	SIZE -> number");
			break;
		}
	default:
		{
			printf("\n an error : wanted number and got %, in line [%d]" ,tkn->lexeme,tkn->linenum);
		while(tkn->type!= EOF && !(sizeexpfollow(tkn)))
			{
				tkn=nextToken();
			}
			if (tkn->type !=EOF)
			{
				tkn=backToken();
			}
		}

	}
}

int commandfollowtok(token* tkn)
{
	switch(tkn->type)
	{
	case END:
		{
			return 1;
		}

	case OTHERWISE:
		{
			return 1;
		}

	case DONE:
		{
			return 1;
		}

	case UNTIL:
		{
			return 1;
		}

	case SEMICOLON:
		{
			return 1;
		}

	case CLOSE_CL_BRACKETS:
		{
			return 1;
		}

		default:
			{
				return 0;
			}

	}
}

int veriablefollowtok(token* tkn)
{
	switch(tkn->type)
	{
		case COMMA:
		{
				return 1;
		}

		case SEMICOLON:
		{
			return 1;
		}

		case START:
		{
			return 1;
		}

		default:
		{
			return 0;
		}

	}
}

int basicexpfollow(token* tkn)
{
	switch (tkn->type)
	{
	case AR_OP:
		{
			return 1;
			
		}
	case END:
		{
			return 1;
		}
	case OTHERWISE:
		{
			return 1;
		}
	case DONE:
		{
			return 1;
		}
	case UNTIL:
		{
			return 1;
		}
	case CLOSE_CL_BRACKETS:
		{
			return 1;
		}
	case SEMICOLON:
		{
			return 1;
		}
	case CLOSE_SQ_BRACKETS:
		{
			return 1;
		}
	case REL_OP:
		{
			return 1;
		}
	case DO:
		{
			return 1;
		}

	
	case END_CYCLE:
		{
			return 1;
		}


		default:
			{
				return 0;
			}

	}
}

int sizeexpfollow(token* tkn)
{
	switch(tkn->type)
	{
	case CLOSE_SQ_BRACKETS:
		{
			return 1;
		}
	default: return 0;
	}
}

int reciverfollowtok(token* tkn)
{
	switch(tkn->type)
	{
		case ASSIGNMENT:
		{
			return 1;
		}

		default:
		{
			return 0;
		}

	}
}

int typefollowtok(token* tkn)
{
	switch(tkn->type)
	{
		case ID:
		{
			return 1;
		}

		case POINTER:
		{
			return 1;
		}

		default:
		{
			return 0;
		}

	}
}