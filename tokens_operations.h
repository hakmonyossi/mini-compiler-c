#define PROGRAM 1
#define ID 2
#define NUMBER 3
#define START 4
#define COMMA 5
#define ASSIGNMENT 6
#define  CHAR 7
#define  INTEGER 8 
#define  OPEN_SQ_BRACKETS 9
#define  CLOSE_SQ_BRACKETS 10
#define  OPEN_CL_BRACKETS 11
#define  CLOSE_CL_BRACKETS 12
#define  POINTER 13
#define  SEMICOLON 14
#define  CYCLE 16
#define  DO 17
#define  OTHERWISE 18
#define  END_CYCLE 19
#define  UNTIL 20
#define  DONE 21
#define  AR_OP 22
#define  REL_OP 23
#define  END 24
#define  WHEN 25
#define  SYMBOL 25
#define  MAX 90


typedef struct token{
	int type;
	int linenum;
	char* lexeme;
}token;


token* nextToken();
token* backToken();
void parse_program();
char* getTokenType(int tokenNumber);
void parse_definition_tag();
void parse_definitions();
void parse_definition();
void parse_variables_list();
void parse_type();
void parse_veriables_list_tag();
void parse_veriable();
void parse_variable_tag();
void parse_commands();
void pars_reciver();
void parse_expression();
void parse_commands_tag();
void parse_command();
void parse_conditions();
void parse_expression();
void parse_condition();
void parse_reciver();
void parse_reciver_tag();
void parse_basic_expression();
void parse_basic_expression_tag();
void parse_expression_tag();
void parse_size();
int commandfollowtok(token* t);
int veriablefollowtok(token* t);
int reciverfollowtok(token* t);
int basicexpfollow(token* t);
int sizeexpfollow(token* t);
int typefollowtok(token* t);