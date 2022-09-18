#pragma once
#include <iostream>
#include<string>
using namespace std;

enum Mark
{
	id,
	num,
	integer,
	keyword,
	operater,
	single,
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

};//¶şÔªÊ½

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
	int my_line = 0;
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

	void print_num() 
	{
		cout << "total_lines:" << my_line << endl;
		cout << "total_chars:" << my_line << endl;

		cout << "num of id:" << num_id << endl;
		cout << "num of integer:" << num_integer << endl;
		cout << "num of Unsigned number:" << num_num << endl;
		cout << "num of keyword:" << num_keyword << endl;
		cout << "num of operater:" << num_operater << endl;
		cout << "num of single:" << num_single << endl;
		cout << "num of string:" << num_my_string << endl;
		cout << "num of char:" << num_my_char << endl;

	}

private:

};

Statistics::Statistics()
{
}

Statistics::~Statistics()
{
}
