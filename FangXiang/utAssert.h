#include <iostream>
#include <string>
#pragma once

namespace UT
{
	bool utComInt(int a, int b, int diff, const std::string an, const std::string bn, std::string &msg);
	bool utComDouble(double a, double b, double diff, double precision, const std::string an, const std::string bn, std::string &msg);
	bool utComDouble(double a, double b, double diff, double precision, const std::string an, const std::string bn, const std::string dn, std::string &msg);
	bool utComDouble(double a, double b, double diff, double precision, const std::string an, const std::string bn, const std::string cn, const std::string dn, const std::string en, std::string &msg);
	bool utComStr(std::string a, std::string b, const std::string an, const std::string bn, const std::string cn, std::string &msg);
	void utPrintErro(const std::string msg);
	void utPrintErro(const int erroNum);
}

// state check
namespace SC
{
	void scCheck(std::string aft_n, std::string bf_n, std::string diff_n, double aft, double bf, double diff, double precision);
}