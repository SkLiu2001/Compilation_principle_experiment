#pragma once
#include <iostream>
#include<string>
#include <iomanip>
#define BUF_SIZE 1024
using namespace std;
char buffer[2 * BUF_SIZE];//存放缓冲区
class file_read//文件读写类
{
public:
	void read_front()//读写一次文件 存入前半部分缓冲区
	{
		int pos = 0;
		while (pos < 1024)
		{
			buffer[pos] = fin.get();
			if (buffer[pos]==EOF)
			{
				break;
			}
			pos++;
		}
		//cout << buffer << endl;
		//cout << strlen(buffer) << endl;
	}

	void read_behind()//读写一次文件 存入后半部分缓冲区
	{
		int pos = 0;
		while ( pos < 1024)
		{
			buffer[pos + 1024] = fin.get();
			if (buffer[pos + 1024]==EOF)
			{
				break;
			}
			pos++;
		}
		//cout << buffer << endl;
	}

	file_read()//构造函数
	{
		fin.open("test.txt", ios::in);
		if (!fin.is_open())
		{
			std::cerr << "can't open the file" << endl;
		}
		memset(buffer, 0, 2 * BUF_SIZE);

		fout.open("out.txt", ios::out);
		if (!fout.is_open())
		{
			std::cerr << "can't open the file" << endl;
		}
	}
	~file_read()
	{

	}

	ofstream fout;
private:
	ifstream fin;

};

file_read myread;

enum Mark
{
	id,
	num,
	integer,
	keyword,
	operater,
	pound_sign,
	my_string,
	my_char
};

class Binary 
{
public:
	Binary ();
	~Binary ();
	Mark sign;
	long long Integer;
	double Unsigned_number;
	string word="";
private:
};//二元式

Binary ::Binary ()
{
}

Binary ::~Binary ()
{
}

class Statistics
{
public:
	Statistics();
	~Statistics();
	int my_line = 1;
	//int my_column = 0;
	long long num_char = 0;

	int num_id = 0;
	int num_num = 0;
	int num_integer = 0;
	int num_keyword = 0;
	int num_operater = 0;
	int num_single = 0;
	int num_my_string = 0;
	int num_my_char = 0;
	int num_error = 0;

	void print_num() 
	{
		cout << "分析报告如下" << endl;
		cout << setw(30) << "total_lines:" << my_line << endl;
		cout << setw(30) << "total_chars:" << num_char << endl;
		cout << setw(30) << "total_errors:" << num_error << endl;

		cout << setw(30) << "num of id:" << num_id << endl;
		cout << setw(30) << "num of integer:" << num_integer << endl;
		cout << setw(30) << "num of Unsigned number:" << num_num << endl;
		cout << setw(30) << "num of keyword:" << num_keyword << endl;
		cout << setw(30) << "num of operater:" << num_operater << endl;
		cout << setw(30) << "num of pound_sign:" << num_single << endl;
		cout << setw(30) << "num of string:" << num_my_string << endl;
		cout << setw(30) << "num of char:" << num_my_char << endl;

		myread.fout << setw(25) << "total_lines:" << my_line << endl;
		myread.fout << setw(25) << "total_chars:" << num_char << endl;
		myread.fout << setw(25) << "total_errors:" << num_error << endl;

		myread.fout << setw(25) << "num of id:" << num_id << endl;
		myread.fout << setw(25) << "num of integer:" << num_integer << endl;
		myread.fout << setw(25) << "num of Unsigned number:" << num_num << endl;
		myread.fout << setw(25) << "num of keyword:" << num_keyword << endl;
		myread.fout << setw(25) << "num of operater:" << num_operater << endl;
		myread.fout << setw(25) << "num of pound_sign:" << num_single << endl;
		myread.fout << setw(25) << "num of string:" << num_my_string << endl;
		myread.fout << setw(25) << "num of char:" << num_my_char << endl;

	}

private:

};

Statistics::Statistics()
{
}

Statistics::~Statistics()
{
}
