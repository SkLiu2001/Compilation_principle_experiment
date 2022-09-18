#include<iostream>
#include<string>
#include<fstream>
#include"table.h"
#include<vector>
#define BUF_SIZE 1024
using namespace std;

int STATE;//��ǰ״ָ̬ʾ
int iskey;//����Ƿ�Ϊ�ؼ���
char C;//��ŵ�ǰ������ַ�
string token;//��ŵ�ǰ����ʶ��ĵ����ַ���
char buffer[2 * BUF_SIZE];//��Ż�����
int forward=0;//��ǰָ��
int lexmebegin=0;//��ʼָ��
vector<Binary> mytable;
string keywords[]={ "auto", "double" ,"int" ,"struct" ,"break" ,"else" ,"long" ,"switch",

					"case" ,"enum" ,"register" ,"typedef" ,"char" ,"extern" ,"return" ,

					"unionconst" ,"float" ,"short" ,"unsigned" ,"continue" ,"for" ,
	
					"signed" ,"void" ,"default" ,"goto" ,"sizeof" ,"volatile" ,"do" ,

					"if" ,"while" ,"static"};
Statistics my_statis;
void cat()//��C�е��ַ�������token���ַ�������
{
	token = token + C;
}

bool letter()//�ж�C���ַ��Ƿ�Ϊ��ĸ
{
	if ((C >= 'A' && C <= 'Z') || (C >= 'a' && C <= 'z'))
		return true;
	else
		return false;
}

bool digit()//�ж�C���ַ��Ƿ�Ϊ����
{
	if ((C >= '0' && C <= '9'))
		return true;
	else
		return false;
}

void retract()//forward����һ���ַ�
{
	::forward--;
}

int reserve()//token�ڵ����ǹؼ��� ���عؼ��ּǺ� ���򷵻�-1
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

int table_insert(Mark sign,string word)//��ʶ������ı�ʶ��������ű����ظõ��ʵ�λ��ָ��
{
	for (int i = 0; i++; i < mytable.size())
	{
		if (sign == num)
		{
			if (mytable[i].Unsigned_number== stod(word))//��������ȣ�������
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
		}//����ԭ���ʹ���
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
	cout << "<";
	switch (x)
	{
	case id:
		cout << "id ,";
		my_statis.num_id++;
		break;
	case num:
		cout << "num ,";
		my_statis.num_num++;
		break;
	case integer:
		cout << "integer ,";
		my_statis.num_integer++;
		break;
	case keyword:
		cout << "keyword ,";
		my_statis.num_keyword++;
		break;
	case operater:
		cout << "operater ,";
		my_statis.num_operater++;
		break;
	case single:
		cout << "single ,";
		my_statis.num_single++;
		break;
	case my_string:
		cout << "string ,";
		my_statis.num_my_string++;
		break;
	case my_char:
		cout << "char ,";
		my_statis.num_my_char++;
		break;
	default:
		break;
	}
}

void return_ID(Mark x, string word)
{
	print_mark(x);
	cout << word << ">" << endl;
}

void return_ID(Mark x, long long word)
{
	print_mark(x);
	cout << word << ">" << endl;
}

void return_ID(Mark x, double word)
{
	print_mark(x);
	cout << word << ">" << endl;
}

//error���� �� return����
class file_read//�ļ���д��
{
public:
	void read_front()//��дһ���ļ� ����ǰ�벿�ֻ�����
	{
		int pos = 0;
		while ((buffer[pos] = fin.get()) != EOF && pos<1024)
		{
			pos++;
		}
	}

	void read_behind()//��дһ���ļ� �����벿�ֻ�����
	{
		int pos = 0;
		while ((buffer[pos+1024] = fin.get()) != EOF && pos < 1024)
		{
			pos++;
		}
	}

	file_read()//���캯��
	{
		fin.open("test.txt", ios::in);
		if (!fin.is_open())
		{
			std::cerr << "can't open the file" << endl;
		}
		memset(buffer, 0, 2*BUF_SIZE);
	}
	~file_read()
	{

	}

private:
	ifstream fin;
};

file_read myread;

void get_char()//����forward��ȡһ���ַ� �������C ���ƶ�forward
{
	C = buffer[::forward];
	if (C == '\n')
	{
		my_statis.my_line++;
	}
	if (!(C == ' ' || C == '\n' || C == '\r' || C == '\t'))
	{
		my_statis.num_char++;
	}
	if (C == EOF)
	{
		cout << "�ʷ���������" << endl;
		my_statis.print_num();
		exit(0);
	}

	if (::forward == 1023)
	{
		myread.read_behind();
		::forward++;
	}
	else if (::forward == 2047)
	{
		myread.read_front();
		::forward=0;
	}
	else
	{
		::forward++;
	}
}

void get_nbc()//���C�е��ַ��Ƿ�Ϊ�ո� �����򷴸�����get_char ֱ��C�н���һ���ǿ��ַ�Ϊֹ
{
	while (C == ' ' || C == '\n' || C == '\r' || C == '\t')
	{
		get_char();
	}
}

void error()
{

}
int main()
{
	//���ļ�
	myread.read_front();//�ȶ�ȡһ��ǰ�벿��

	STATE = 0;
	do
	{
		switch (STATE)
		{
		case 0://��ʼ״̬
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
				STATE = 1;//���ñ�ʶ��
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
				STATE = 2;//���ó���״̬
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
				return_ID(single,"(");
				break;
			case')':
				STATE = 0;
				return_ID(single, ")");
				break;
			case';':
				STATE = 0;
				return_ID(single, ";");
				break;
			case'[':
				STATE = 0;
				return_ID(single, "[");
				break;
			case']':
				STATE = 0;
				return_ID(single, "]");
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
				return_ID(single, ",");
				break;
			case'?':
				STATE = 0;
				return_ID(operater,"?");
				break;
			case'#':
				STATE = 0;
				return_ID(single, "#");
				break;
			case':':
				STATE = 0;
				return_ID(operater, ":");
				break;
			case'{':
				STATE = 0;
				return_ID(single, "{");
				break;
			case'}':
				STATE = 0;
				return_ID(single, "}");
				break;
			case'"':
				return_ID(single, "\"");
				token = "";//��token���� ׼�������ַ���
				C = 0;
				STATE = 28;
				break;
			case'\'':
				return_ID(single, "'");
				token = "";//��token���� ׼�������ַ�
				STATE = 29;
				C = 0;
				break;
			default:
				STATE = 13;//���ô���״̬
				cout << "oh,no!there is an error" << endl;
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
				else//���ǹؼ���
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
		case 3://С����״̬
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
		case 4://С��״̬
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
			default://ʶ���ΪС��
				retract();
				STATE = 0;
				return_ID(num,stod(token));
				break;
			}
			break;
		case 5://ָ��״̬
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
				return_ID(num,stod(token));//�����޷�����
			}
			break;
		case 8://'<'״̬
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
		case 23://<<״̬
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
		case 9://'>'״̬
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
				return_ID(operater, ">");//����>״̬
				break;
			}
			break;
		case 24://'>='״̬
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
		//ע�ʹ����֣�˳������������㣩
		case 11://'/'״̬
			cat();
			get_char();
			switch (C)
			{
			case '/':
				STATE = 25;//'//״̬'
				break;
			case'*':
				STATE = 26;// '/*'״̬
				break;
			case '=':
				cat(); STATE = 0; return_ID(operater, "/="); break;// '/='
			default:
				retract(); STATE = 0; return_ID(operater, "/");
				break;
			}
			break;
		case 26://'/*״̬'
			get_char();
			if (C=='*')
			{
				STATE = 27;//����//*״̬
			}
			else
			{
				STATE = 26;//����/*״̬
			}
			break;
		case 25://'//״̬'
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
				STATE = 27;//�ص�/**״̬
				break;
			case '/':
				STATE = 0;//ע�ͽ���
				break;
			default:
				STATE = 26;//�ص�/*״̬
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
		case 19://��
			cat();
			get_char();
			switch (C)
			{
			case '='://��=
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

		case 28://��ʼ�����ַ���
			cat();
			get_char();
			if (C == '"')
			{
				return_ID(my_string, token);
				return_ID(single, "\"");
				STATE = 0;
			}
			/*else if (C == '\\')
			{
				cat();
				get_char(); 
				STATE = 28;
			}*/
			else
			{
				STATE = 28;
			}
			break;
		case 29://��ʼ�����ַ�
			cat();
			get_char();
			if (C == '\'')
			{
				return_ID(my_char, token);
				return_ID(single, "'");
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
	} while (C!=EOF);

	my_statis.print_num();
	return 0;
}