%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	int line=1;
	int num_word=0;

	int num_id = 0;
	int num_num = 0;
	int num_integer = 0;
	int num_keyword = 0;
	int num_operater = 0;
	int num_single = 0;
	int num_my_string = 0;
	int num_my_char = 0;

	#define yywrap() 1

%}

digit ([0-9])

letter ([A-Za-z_])

LINE_NOTES (\/\/[^\n]*)

MUL_LINE_NOTES (\/\*([^\*]|(\*)*[^\*/])*(\*)*\*\/)

STRING (\"([^\\\"\n]|\\.)*\")

CHAR (\'([^\'\\]|\\.)*\')

KEYWORD "auto"|"double"|"int"|"struct"|"break"|"else"|"long"|"switch"|"case"|"enum"|"register"|"typedef"|"char"|"extern"|"return"|"unionconst"|"float"|"short"|"unsigned"|"continue"|"for"|"signed"|"void"|"default"|"goto"|"sizeof"|"volatile"|"do"|"if"|"while"|"static"

IDENTIFIER ({letter}({letter}|{digit})*)

OPERATOR "+"|"."|"->"|"-"|"++"|"--"|"*"|"&"|"!"|"~"|"/"|"%"|"<<"|">>"|">"|"<"|">="|"<="|"=="|"!="|"^"|"|"|"&&"|"||"|"="|"/="|"*="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="|":"|"?"

POUND_SIGN "("|")"|"["|"]"|"{"|"}"|"#"|";"|","

INTEGER ({digit}+)

UNSIGNED_NUM ({digit}+(\.{digit}+)?([Ee][+-]?{digit}+)?)



%%
{KEYWORD} {
	printf("line%d:(KEYWORD, %s)\n\n",line,yytext);
	num_keyword++;
	num_word++;
	}
{IDENTIFIER} {
	printf("line%d:(IDENTIFIER, %s)\n\n",line,yytext);
	num_id++;
	num_word++;
	}
{OPERATOR} {
	printf("line%d:(OPERATOR, %s)\n\n",line,yytext);
	num_operater++;
	num_word++;
	}
{POUND_SIGN} {
	printf("line%d:(POUND_SIGN, %s)\n\n",line,yytext);
	num_single++;
	num_word++;
	}
{INTEGER} {
	printf("line%d:(INTEGER, %s)\n\n",line,yytext);
	num_integer++;
	num_word++;
	}
{UNSIGNED_NUM} {
	printf("line%d:(UNSIGNED_NUM, %s)\n\n",line,yytext);
	num_num++;
	num_word++;
	}
{STRING} {
	printf("line%d:(STRING, %s)\n\n",line,yytext);
	num_my_string++;
	num_word++;
	}
{CHAR} {
	printf("line%d:(CHAR, %s)\n\n",line,yytext);
	num_my_char++;
	num_word++;
	}
{LINE_NOTES} {
	printf("line%d:(LINE_NOTES, %s)\n\n",line,yytext);
}
{MUL_LINE_NOTES} {
	printf("line%d:(MUL_LINE_NOTES, %s)\n\n",line,yytext);
	for (int i=0;i<strlen(yytext);i++)
	{
		if (yytext[i]=='\n')
		{
			line++;
		}
	}
}

\n      {
    line++;
}

%%
int main()
{
	yylex();
	puts("-------------------------------------------------------------");
	printf("\nTotal Word: %d\n",num_word);
	printf("Total Line: %d\n",line);
	
	printf("Total KEYWORD: %d\n",num_keyword);
	printf("Total IDENTIFIER: %d\n",num_id);
	printf("Total OPERATOR: %d\n",num_operater);
	printf("Total POUND_SIGN: %d\n",num_single);
	printf("Total INTEGER: %d\n",num_integer);
	printf("Total UNSIGNED_NUM: %d\n",num_num);
	printf("Total STRING: %d\n",num_my_string);
	printf("Total CHAR: %d\n",num_my_char);
	return 0;
}
