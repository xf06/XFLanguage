#include "tFXValue.h"
#include "utAssert.h"
#include <assert.h>
#include <iostream>
using namespace std;

// recreate weel
void tTryTest(void);
void Test01(void);
void Test02(void);

int main()
{
	tTryTest();
	//Test01();
	// Test02();

	return 0; 
}

void Test01(void)
{
	string tmp = "";
	tFXValue* ptr = NULL;

	//# single
	ptr = new tFXValue("1"); assert(UT::utComDouble(ptr->tFXCalcu(), 1, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("10"); assert(UT::utComDouble(ptr->tFXCalcu(), 10, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("+10"); assert(UT::utComDouble(ptr->tFXCalcu(), 10, 0, 0.0001, "A", "B", tmp)); delete ptr;

	ptr = new tFXValue("-10"); assert(UT::utComDouble(ptr->tFXCalcu(), -10, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("(1)"); assert(UT::utComDouble(ptr->tFXCalcu(), 1, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("(+10)"); assert(UT::utComDouble(ptr->tFXCalcu(), 10, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("(-10)"); assert(UT::utComDouble(ptr->tFXCalcu(), -10, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("(((10)))"); assert(UT::utComDouble(ptr->tFXCalcu(), 10, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("(((abc)))"); assert(UT::utComDouble(ptr->tFXCalcu(), 255, 0, 0.0001, "A", "B", tmp)); delete ptr;
	
	//# addition
	ptr = new tFXValue("11+12"); assert(UT::utComDouble(ptr->tFXCalcu(), 23, 0, 0.0001, "A", "B", tmp)); delete ptr;
	//ptr = new tFXValue("3-+5"); assert(UT::utComDouble(ptr->tFXCalcu(), 23, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("abc+5"); assert(UT::utComDouble(ptr->tFXCalcu(), 260, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("105+abc_01"); assert(UT::utComDouble(ptr->tFXCalcu(), 360, 0, 0.0001, "A", "B", tmp)); delete ptr;
	
	//# subsitusion
	ptr = new tFXValue("12-11"); assert(UT::utComDouble(ptr->tFXCalcu(), 1, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("100-121"); assert(UT::utComDouble(ptr->tFXCalcu(), -21, 0, 0.0001, "A", "B", tmp));  delete ptr;
	ptr = new tFXValue("abc-255"); assert(UT::utComDouble(ptr->tFXCalcu(), 0, 0, 0.0001, "A", "B", tmp));  delete ptr;
	ptr = new tFXValue("255-abc"); assert(UT::utComDouble(ptr->tFXCalcu(), 0, 0, 0.0001, "A", "B", tmp));  delete ptr;

	//# multiplication
	ptr = new tFXValue("11*11"); assert(UT::utComDouble(ptr->tFXCalcu(), 121, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("12*90"); assert(UT::utComDouble(ptr->tFXCalcu(), 1080, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("abc*1"); assert(UT::utComDouble(ptr->tFXCalcu(), 255, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("1*abc"); assert(UT::utComDouble(ptr->tFXCalcu(), 255, 0, 0.0001, "A", "B", tmp)); delete ptr;

	//# division
	ptr = new tFXValue("io/io04"); assert(UT::utComDouble(ptr->tFXCalcu(), 1, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("90/5"); assert(UT::utComDouble(ptr->tFXCalcu(), 18, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("1/5"); assert(UT::utComDouble(ptr->tFXCalcu(), 0.20, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("510/abc"); assert(UT::utComDouble(ptr->tFXCalcu(), 2, 0, 0.0001, "A", "B", tmp)); delete ptr;

	//# dot
	ptr = new tFXValue("(io)io04"); assert(UT::utComDouble(ptr->tFXCalcu(), 65025, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("9(5)"); assert(UT::utComDouble(ptr->tFXCalcu(), 45, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("(1.5)2"); assert(UT::utComDouble(ptr->tFXCalcu(), 3, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("510/(abc)2"); assert(UT::utComDouble(ptr->tFXCalcu(), 1, 0, 0.0001, "A", "B", tmp)); delete ptr;

	//# element
	ptr = new tFXValue("1+(2+3)*4"); assert(UT::utComDouble(ptr->tFXCalcu(), 21, 0, 0.0001, "A", "B", tmp));  delete ptr;
	ptr = new tFXValue("1-(2+3)-4*5"); assert(UT::utComDouble(ptr->tFXCalcu(), -24, 0, 0.0001, "A", "B", tmp)); delete ptr;
	//ptr = new tFXValue(""); assert(UT::utComDouble(ptr->tFXCalcu(), -24, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("1-5*(2+3)+4*5"); assert(UT::utComDouble(ptr->tFXCalcu(), -4, 0, 0.0001, "A", "B", tmp)); delete ptr;
	ptr = new tFXValue("1-5/(2+3)+4*5"); assert(UT::utComDouble(ptr->tFXCalcu(), 20, 0, 0.0001, "A", "B", tmp)); delete ptr;
	
	/**
	**/
}

void Test02(void)
{
	tFXValue a("a)");
	tFXValue b("((a+b");
	tFXValue c("a++");
}

void tTryTest(void)
{
	while (1)
	{
		string str = "";
		cin >> str;
		tFXValue obj1(str);
		cout << obj1.tFXCalcu() << endl;
	}
}
