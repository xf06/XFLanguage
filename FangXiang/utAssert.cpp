#include "utAssert.h"
#include "ConsoleColor.h"
#include <sstream>
#include <cmath>
//#include<conio.h>

#define SC_PAUSE	
//#define SC_PAUSE	while (_kbhit()) _getch(); _getch();

bool UT::utComInt(const int a, const int b, const int diff, const std::string an, const std::string bn, std::string &msg)
{
	std::stringstream ss;

	ss << an << "," << bn << "," << a << "," << b << "," << diff << " ";
	if ((a - b) == diff)
	{
		std::cout <<green<<"PASS,"<<ss.str()<<white<< std::endl;
		return true;
	}
	else
	{
		//ss <<"("<<(a - b)<<")"<< " ";
		msg = msg + "\nERROR," + ss.str();
		return false;
	}

}

bool UT::utComDouble(double a, double b, double diff, double precision, const std::string an, const std::string bn, std::string &msg)
{
	std::stringstream ss;

	ss << an << "," << bn << "," << a << "," << b << "," << diff << ", "<<precision<<" ";
	if (abs((a - b) - diff) < precision)
	{
		std::cout << green << "PASS," << ss.str() << white << std::endl;
		return true;
	}
	else
	{
		msg = msg + "\nERROR," + ss.str();
		return false;
	}
}

bool UT::utComDouble(double a, double b, double diff, double precision, const std::string an, const std::string bn, const std::string cn, const std::string dn, const std::string en, std::string &msg)
{
	std::stringstream ss;

	ss << an << "," << bn << "," << cn << "," << dn << "," << en << "," << a << "," << b << "," << diff << ", " << precision << " ";
	if (abs((a - b) - diff) < precision)
	{
		std::cout << green << "PASS," << ss.str() << white << std::endl;
		return true;
	}
	else
	{
		msg = msg + "\nERROR," + ss.str();
		return false;
	}
}

bool UT::utComStr(std::string a, std::string b, const std::string an, const std::string bn, const std::string cn, std::string &msg)
{
	std::stringstream ss;

	ss << an << "," << bn << "," << cn << "," << a << "," << b << " ";
	if (a == b)
	{
		std::cout << green << "PASS," << ss.str() << white << std::endl;
		return true;
	}
	else
	{
		msg = msg + "\nERROR," + ss.str();
		return false;

	}
}

bool utComDouble(double a, double b, double diff, double precision, const std::string an, const std::string bn, const std::string dn, std::string &msg)
{
	std::stringstream ss;

	ss << an << "," << bn << "," << dn <<","<< a << "," << b << "," << diff << ", " << precision << " ";

	if (abs((a - b) - diff) < precision)
	{
		std::cout << green << "PASS," << ss.str() << white << std::endl;
		return true;
	}
	else
	{
		msg = msg + "\nERROR," + ss.str();
		return false;
	}
}

void UT::utPrintErro(const std::string msg)
{
	std::cout << red << msg << white << std::endl;
}

void UT::utPrintErro(const int erroNum)
{
	if (erroNum!=0)
		std::cout << red <<"Error"<<erroNum<<": "<< white;
}

void SC::scCheck(std::string aft_n, std::string bf_n, std::string diff_n, double aft, double bf, double diff, double precision)
{
	std::string msg = "";
	bool cv = utComDouble(aft, bf, diff, precision, aft_n, bf_n, diff_n, msg);
	if (cv != true)
	{
		UT::utPrintErro(msg);
		SC_PAUSE
	}
}

