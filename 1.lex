%{
	#include "tokens.h"
	#include "tokens_operations.h"
	int t;
	int flageof=0;
	int linenum=1;
%}
PROGRAM "program" 
COMMENT "/*".*"*/"
END	"end"
DIGIT [0-9]
NUMBER 0|[1-9]{DIGIT}*
START "start"
COMMA ","
CHAR "char"
SYMBOL "'"[a-z0-9]"'"
INTEGER "integer"
SEMICOLON ";"
CYCLE "cycle"
DO "do"
OTHERWISE "otherwise" 
END_CYCLE "end_cycle"
OPEN_SQ_BRACKETS "["
CLOSE_SQ_BRACKETS "]"
OPEN_CL_BRACKETS "{"
CLOSE_CL_BRACKETS "}"
UNTIL "until"
DONE "done"
AR_OP "+"|"**"|"-"|"mod"
REL_OP "<"|"<="|"=="|"!="|">"|">="
ASSIGNMENT ":="
POINTER "*"
WHEN "when"
ID    [a-zA-Z]+([_]?([a-zA-Z0-9])+)*
SPACE " "
%%
\n {linenum++;}
{COMMENT} {break;}
{PROGRAM} {fprintf(yyout,"\n lexeme: %s  , line:  %d, type: keywords",yytext,linenum); addnewtokentolist(yytext,PROGRAM,linenum);  return; }
{END} {fprintf(yyout,"\n lexeme: %s  , line:  %d, type: keywords",yytext,linenum); addnewtokentolist(yytext,END,linenum);  return; }
{NUMBER}  {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: number",yytext,linenum); addnewtokentolist(yytext,NUMBER,linenum);  return; }
{START}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords ",yytext,linenum); addnewtokentolist(yytext,START,linenum);  return; }
{COMMA}  {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: marks ",yytext,linenum); addnewtokentolist(yytext,COMMA,linenum);  return; }
{CHAR}  {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,CHAR,linenum);  return; }
{INTEGER} {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,INTEGER,linenum);  return; }
{OPEN_SQ_BRACKETS} {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,OPEN_SQ_BRACKETS,linenum);  return; }
{CLOSE_SQ_BRACKETS} {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,CLOSE_SQ_BRACKETS,linenum);  return; }
{OPEN_CL_BRACKETS} {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,OPEN_CL_BRACKETS,linenum);  return; }
{CLOSE_CL_BRACKETS} {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,CLOSE_CL_BRACKETS,linenum);  return; }
{ASSIGNMENT} {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,ASSIGNMENT,linenum);  return; }
{CHAR}  {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,CHAR,linenum);  return; }
{SEMICOLON} {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: marks",yytext,linenum); addnewtokentolist(yytext,SEMICOLON,linenum);  return; }
{CYCLE}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,CYCLE,linenum);  return; }
{DO}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,DO,linenum);  return; }
{OTHERWISE}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,OTHERWISE,linenum);  return; }
{END_CYCLE}  {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,END_CYCLE,linenum);  return; }
{UNTIL}    {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,UNTIL,linenum);  return; }
{WHEN}    {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,WHEN,linenum);  return; }
{DONE}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,DONE,linenum);  return; }
{SYMBOL}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: keywords",yytext,linenum); addnewtokentolist(yytext,SYMBOL,linenum);  return; }
{AR_OP}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: ar_op",yytext,linenum); addnewtokentolist(yytext,AR_OP,linenum);  return; }
{REL_OP}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: rel_op",yytext,linenum); addnewtokentolist(yytext,REL_OP,linenum);  return; }
{ID}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: id",yytext,linenum); addnewtokentolist(yytext,ID,linenum);  return; }
{POINTER}   {fprintf(yyout,"\n lexeme:  %s , line:  %d,   type: rel_op ",yytext,linenum); addnewtokentolist(yytext,POINTER,linenum);  return; }
{SPACE} {printf(""); break;}
. {printf("\n illegal lexeme %s , line %d : ",yytext, linenum); return;}

<<EOF>> {printf("");addnewtokentolist(yytext,EOF,linenum);flageof =1;return;}
. {printf("");}
%%
void main(int argc, char* argv[])
{
	yyin=fopen(argv[1], "r");
	parse_program();

}

