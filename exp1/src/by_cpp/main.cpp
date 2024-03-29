#include<iostream>
#include<string>
#include<fstream>
#include"table.h"
#include<vector>
#include <iomanip>

using namespace std;

int STATE;//当前状态指示
int iskey;//标记是否为关键字
char C;//存放当前存入的字符
string token;//存放当前正在识别的单词字符串

int forward=0;//向前指针
int lexmebegin=0;//开始指针
int is_retract = 0;
vector<Binary> mytable;
string keywords[]={ "auto", "double" ,"int" ,"struct" ,"break" ,"else" ,"long" ,"switch",

					"case" ,"enum" ,"register" ,"typedef" ,"char" ,"extern" ,"return" ,

					"unionconst" ,"float" ,"short" ,"unsigned" ,"continue" ,"for" ,
	
					"signed" ,"void" ,"default" ,"goto" ,"sizeof" ,"volatile" ,"do" ,

					"if" ,"while" ,"static"};
Statistics my_statis;
void cat()//把C中的字符连接在token的字符串后面
{
	token = token + C;
}

bool letter()//判断C中字符是否为字母或下划线
{
	if ((C >= 'A' && C <= 'Z') || (C >= 'a' && C <= 'z')||C=='_')
		return true;
	else
		return false;
}

bool digit()//判断C中字符是否为数字
{
	if ((C >= '0' && C <= '9'))
		return true;
	else
		return false;
}

void retract()//forward后退一个字符
{
	if (C=='\n')
	{
		my_statis.my_line--;
	}
	if (::forward != 0)
	{
		::forward--;
		is_retract = 1;
	}
	else
	{
		::forward = 2047;
		is_retract = 1;
	}
}

int reserve()//token内单词是关键字 返回关键字记号 否则返回-1
{
	for (int i = 0; i < 32; i++)
	{
		if (keywords[i] == token)
		{
			return 1;
		}
	}
	return 0;
}

int table_insert(Mark sign,string word)//将识别出来的标识符插入符号表，返回该单词的位置指针
{
	for (int i = 0; i++; i < mytable.size())
	{
		if (sign == num)
		{
			if (mytable[i].Unsigned_number== stod(word))//浮点数相等？？？？
			{
				return i;
			}
		}
		else if (sign == integer)
		{
			if (mytable[i].Integer == stoi(word))
			{
			return i;
			}
		}
		else if (sign == id)
		{
			if (mytable[i].word ==word)
			{
				return i;
			}
		}//表中原来就存在
	}
	Binary temp;
	if (sign == id)
	{
		temp.sign = id;
		temp.word = word;
	}
	/*else if (sign == keyword)
	{
		temp.sign = keyword;
		temp.word = word;
	}*/
	else if (sign == num)
	{
		temp.sign = num;
		temp.Unsigned_number = stod(word);
	}
	else if (sign == integer)
	{
		temp.sign = integer;
		temp.Integer = stoi(word);
	}
	/*else if (sign == operater)
	{
		temp.sign = operater;
		temp.word = word;
	}
	else
	{
		temp.sign = single;
		temp.word = word;
	}*/

	mytable.push_back(temp);
	return (mytable.size() - 1);

}

void print_mark(Mark x)
{
	my_statis.num_char++;
	cout << "line:" << setw(5) << my_statis.my_line;
	myread.fout << setiosflags(ios::left) << "line:" << setw(5) << my_statis.my_line;
	switch (x)
	{
	case id:
		cout << setw(25) << "id" ;
		myread.fout << setiosflags(ios::left) << setw(25) << "id";
		my_statis.num_id++;
		break;
	case num:
		cout <<setw(25)  << "Unsigned number";
		myread.fout << setiosflags(ios::left) << setw(25) << "Unsigned number";
		my_statis.num_num++;
		break;
	case integer:
		cout << setw(25) << "integer" ;
		myread.fout << setiosflags(ios::left) << setw(25) << "integer";
		my_statis.num_integer++;
		break;
	case keyword:
		cout << setw(25) << "keyword";
		myread.fout << setiosflags(ios::left) << setw(25) << "keyword";
		my_statis.num_keyword++;
		break;
	case operater:
		cout << setw(25) << "operater";
		myread.fout << setiosflags(ios::left) << setw(25) << "operator";
		my_statis.num_operater++;
		break;
	case pound_sign:
		cout << setw(25) << "pound_sign";
		myread.fout << setiosflags(ios::left) << setw(25) << "pound_sign";
		my_statis.num_single++;
		break;
	case my_string:
		cout << setw(25) << "string";
		myread.fout <<setiosflags(ios::left) << setw(25) << "string";
		my_statis.num_my_string++;
		break;
	case my_char:
		cout << setw(25) << "char" ;
		myread.fout << setiosflags(ios::left) << setw(25) << "char";
		my_statis.num_my_char++;
		break;
	default:
		break;
	}
}

void return_ID(Mark x, string word)
{
	print_mark(x);
	cout << "     " << word << endl;
	myread.fout  << word << endl;
}

void return_ID(Mark x, long long word)
{
	print_mark(x);
	cout << "     " << word << endl;
	myread.fout << word << endl;
}

void return_ID(Mark x, double word)
{
	print_mark(x);
	cout << "     " << word <<  endl;
	myread.fout <<word << endl;
}

//error函数 与 return函数


void get_char()//根据forward读取一个字符 存入变量C 并移动forward
{
	C = buffer[::forward];
	if (C == '\n')
	{
		my_statis.my_line++;
	}
	/*if (C == EOF)
	{
		cout << "词法分析结束" << endl;
		my_statis.print_num();
		exit(0);
	}*/

	if (::forward == 1023)
	{
		if (!is_retract)
		{
			myread.read_behind();
		}
		::forward++;
		is_retract = 0;
	}
	else if (::forward == 2047)
	{
		if (!is_retract)
		{
			myread.read_front();
		}
		::forward=0;
		is_retract = 0;
	}
	else
	{
		::forward++;
		is_retract = 0;
	}
}

void get_nbc()//检查C中的字符是否为空格 若是则反复调用get_char 直到C中进入一个非空字符为止
{
	while (C == ' ' || C == '\n' || C == '\r' || C == '\t')
	{
		get_char();
	}
}

void error()
{
	my_statis.num_error++;
	cout << setw(25) << "error";
	cout << "     C:"<< C <<" " << "token:" << token << endl;
	cout << setw(25) << "error lines:";
	cout <<"     " << my_statis.my_line << endl;

	myread.fout << setw(25) << "error";
	myread.fout << "C:" << C << " " << "token:" << token << endl;
	myread.fout << setw(25) << "error lines:";
	myread.fout << my_statis.my_line << endl;
	STATE = 0;
}

int main()
{
	//读文件
	myread.read_front();//先读取一次前半部分
	myread.fout.setf(ios::left);
	cout.setf(ios::left);
	cout << setw(35) << "          Type" << "     " << "Value" << endl;
	myread.fout<< setw(35) << "          Type" << "Value" << endl;
	STATE = 0;
	while (C != EOF)
	{
		switch (STATE)
		{
		case 0://初始状态
			token = "";
			get_char();
			get_nbc();
			switch (C)
			{
			case '_':
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':
				STATE = 1;//设置标识符
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				STATE = 2;//设置常数状态
				break;
			case '<':
				STATE = 8;
				break;
			case '>':
				STATE = 9;
				break;
			case '/':
				STATE = 11;
				break;
			case'=':
				STATE = 14;
				break;
			case'+':
				STATE = 15;
				break;
			case'-':
				STATE = 16;
				break;
			case'*':
				STATE = 17;
				break;
			case'&':
				STATE = 18;
				break;
			case'!':
				STATE = 19;
				break;
			case'%':
				STATE = 20;
				break;
			case'^':
				STATE = 21;
				break;
			case'|':
				STATE = 22;
				break;
			case'(':
				STATE = 0;
				return_ID(pound_sign,"(");
				break;
			case')':
				STATE = 0;
				return_ID(pound_sign, ")");
				break;
			case';':
				STATE = 0;
				return_ID(pound_sign, ";");
				break;
			case'[':
				STATE = 0;
				return_ID(pound_sign, "[");
				break;
			case']':
				STATE = 0;
				return_ID(pound_sign, "]");
				break;
			case '.':
				STATE = 0;
				return_ID(operater, ".");
				break;
			case'~':
				STATE = 0;
				return_ID(operater, "~");
				break;
			case',':
				STATE = 0;
				return_ID(pound_sign, ",");
				break;
			case'?':
				STATE = 0;
				return_ID(operater,"?");
				break;
			case'#':
				STATE = 0;
				return_ID(pound_sign, "#");
				break;
			case':':
				STATE = 0;
				return_ID(operater, ":");
				break;
			case'{':
				STATE = 0;
				return_ID(pound_sign, "{");
				break;
			case'}':
				STATE = 0;
				return_ID(pound_sign, "}");
				break;
			case'"':
				//return_ID(pound_sign, "\"");
				token = "\"";//将token清零 准备读入字符串
				C = 0;
				STATE = 28;
				break;
			case'\'':
				//return_ID(pound_sign, "'");
				token = "\'";//将token清零 准备读入字符
				STATE = 29;
				C = 0;
				break;
			default:
				if (C!=EOF)
				{
					STATE = 13;//设置错误状态
					error();
				}
				break;
			}
			break;

		case 1:
			cat();
			get_char();
			if (letter() || digit())
			{
				STATE = 1;
			}
			else
			{
				retract();
				STATE = 0;
				iskey = reserve();
				if (iskey)
				{
					return_ID(keyword,token);
				}
				else//不是关键字
				{
					int position = 0;
					position = table_insert(id,token);
					return_ID(id,token);
				}
			}
			break;
		case 2:
			cat();
			get_char();
			switch (C)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': STATE = 2; break;
			case '.': STATE = 3; break;
			case 'E':
			case 'e': STATE = 5; break;
			default:
				retract();
				STATE = 0;
				return_ID(integer,stoll(token));
				break;
			}
			break;
		case 3://小数点状态
			cat();
			get_char();
			if (digit())
			{
				STATE = 4;
			}
			else
			{
				error();
				STATE = 0;
			}
			break;
		case 4://小数状态
			cat();
			get_char();
			switch (C)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': STATE = 4; break;
			case 'E':
			case 'e': STATE = 5; break;
			default://识别出为小数
				retract();
				STATE = 0;
				return_ID(num,stod(token));
				break;
			}
			break;
		case 5://指数状态
			cat();
			get_char();
			switch (C)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': STATE = 7; break;
			case '+':
			case '-': STATE = 6; break;
			default:
				retract();
				error();
				STATE = 0;
				break;
			}
			break;
		case 6:
			cat();
			get_char();
			if (digit()) STATE = 7;
			else
			{
				retract();
				error();
				STATE = 0;
			}
			break;
		case 7:
			cat();
			get_char();
			if (digit()) STATE = 7;
			else
			{
				retract();
				STATE = 0;
				return_ID(num,token);//返回无符号数
			}
			break;
		case 8://'<'状态
			cat();
			get_char();
			switch (C)
			{
			case'=':cat(); STATE = 0; return_ID(operater,"<="); break;//<=
			case'<':STATE = 23; break;
			default:
				retract();
				STATE = 0;
				return_ID(operater, "<");
				break;
			}
			break;
		case 23://<<状态
			cat();
			get_char();
			if (C=='=')
			{
				cat(); STATE = 0; return_ID(operater, "<<="); break;//<<=
			}
			else
			{
				retract();
				STATE = 0;
				return_ID(operater, "<<");//<<
			}
			break;
		case 9://'>'状态
			cat();
			get_char();
			switch (C)
			{
			case '>':
				STATE = 24;
				break;
			case '=':
				cat(); STATE = 0; return_ID(operater, ">="); break;
			default:
				retract();
				STATE = 0;
				return_ID(operater, ">");//返回>状态
				break;
			}
			break;
		case 24://'>='状态
			cat();
			get_char();
			if (C=='=')
			{
				cat(); STATE = 0; return_ID(operater, ">>=");//>>=
			}
			else
			{
				retract();
				STATE = 0;
				return_ID(operater, ">>");//>>
			}
			break;
		//注释处理部分（顺带处理除法运算）
		case 11://'/'状态
			cat();
			get_char();
			switch (C)
			{
			case '/':
				STATE = 25;//'//状态'
				break;
			case'*':
				STATE = 26;// '/*'状态
				break;
			case '=':
				cat(); STATE = 0; return_ID(operater, "/="); break;// '/='
			default:
				retract(); STATE = 0; return_ID(operater, "/");
				break;
			}
			break;
		case 26://'/*状态'
			get_char();
			if (C=='*')
			{
				STATE = 27;//进入//*状态
			}
			else
			{
				STATE = 26;//保持/*状态
			}
			break;
		case 25://'//状态'
			get_char();
			if (C == '\n')
			{
				STATE = 0;
			}
			else
			{
				STATE = 25;
			}
			break;
		case 27:
			get_char();
			switch (C)
			{
			case '*':
				STATE = 27;//回到/**状态
				break;
			case '/':
				STATE = 0;//注释结束
				break;
			default:
				STATE = 26;//回到/*状态
				break;
			}
			break;
		case 14://=
			cat();
			get_char();
			if (C=='=')
			{
				cat(); STATE = 0; return_ID(operater, "==");//==
			}
			else
			{
				retract(); STATE = 0; return_ID(operater, "=");//=
			}
			break;
		case 15://+
			cat();
			get_char();
			switch (C)
			{
			case '+'://++
				cat(); STATE = 0; return_ID(operater, "++"); break;
			case '='://+=
				cat(); STATE = 0; return_ID(operater, "+="); break;
			default:
				retract(); STATE = 0; return_ID(operater, "+");//+
				break;
			}
			break;
		case 16://-
			cat();
			get_char();
			switch (C)
			{
			case '-'://--
				cat(); STATE = 0; return_ID(operater, "-"); break;
			case '='://-=
				cat(); STATE = 0; return_ID(operater, "-="); break;
			case '>'://->
				cat(); STATE = 0; return_ID(operater, "->"); break;
			default:
				retract(); STATE = 0; return_ID(operater, "-");//-
				break;
			}
			break;
		case 17://*
			cat();
			get_char();
			switch (C)
			{
			case '='://*=
				cat(); STATE = 0; return_ID(operater, "*="); break;
			default:
				retract(); STATE = 0; return_ID(operater, "*");//*
				break;
			}
			break;
		case 18://&
			cat();
			get_char();
			switch (C)
			{
			case '&'://&&
				cat(); STATE = 0; return_ID(operater, "&&"); break;
			case '='://&=
				cat(); STATE = 0; return_ID(operater, "&="); break;
			default:
				retract(); STATE = 0; return_ID(operater, "&");//&
				break;
			}
			break;
		case 19://！
			cat();
			get_char();
			switch (C)
			{
			case '='://！=
				cat(); STATE = 0; return_ID(operater, "!="); break;
			default:
				retract(); STATE = 0; return_ID(operater, "!");//!
				break;
			}
			break;
		case 20://%
			cat();
			get_char();
			switch (C)
			{
			case '='://%=
				cat(); STATE = 0; return_ID(operater, "%="); break;
			default:
				retract(); STATE = 0; return_ID(operater, "%");//%
				break;
			}
			break;

		case 21://^
			cat();
			get_char();
			switch (C)
			{
			case '='://^=
				cat(); STATE = 0; return_ID(operater, "^="); break;
			default:
				retract(); STATE = 0; return_ID(operater, "^");//^
				break;
			}
			break;

		case 22://|
			cat();
			get_char();
			switch (C)
			{
			case '|'://||
				cat(); STATE = 0; return_ID(operater, "||"); break;
			case '='://|=
				cat(); STATE = 0; return_ID(operater, "|="); break;
			default:
				retract(); STATE = 0; return_ID(operater, "|");//|
				break;
			}
			break;

		case 28://开始读入字符串
			cat();
			get_char();
			if (C == '"')
			{
				cat();
				return_ID(my_string, token);
				//return_ID(pound_sign, "\"");
				STATE = 0;
			}
			else if (C == '\\')
			{
				cat();
				get_char(); 
				STATE = 28;
			}
			else
			{
				STATE = 28;
			}
			break;
		case 29://开始读入字符
			cat();
			get_char();
			if (C == '\'')
			{
				cat();
				return_ID(my_char, token);
				//return_ID(pound_sign, "'");
				STATE = 0;
			}
			else if (C == '\\')
			{
				cat();
				get_char();
				STATE = 29;
			}
			else
			{
				STATE = 29;
			}
			break;
		default:
			break;
		}
	} 

	if (C == EOF)
	{
		cout << "词法分析结束" << endl;
		//my_statis.my_line++;
		my_statis.print_num();
		exit(0);
	}
	return 0;
}