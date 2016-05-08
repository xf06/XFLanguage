#pragma once
#include <iostream>
#include <string>

class tFXOperator
{
public:
	enum OptorTypes{ ADD, SUB, MUL, DIV, MULSUB, DIVSUB, DOT, EMP };

	tFXOperator(std::string ch);
	tFXOperator(OptorTypes ot);
	~tFXOperator();
	
	OptorTypes tGetType(void);
	std::string tFXPrintStr(void);

private:

	OptorTypes tType;
};
