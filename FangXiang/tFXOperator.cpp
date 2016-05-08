#include "tFXOperator.h"

tFXOperator::tFXOperator(std::string ch)
{
	// + - * /
	if (ch == "+")
		this->tType = tFXOperator::ADD;
	else
	if (ch == "-")
		this->tType = tFXOperator::SUB;
	else
	if (ch == "*")
		this->tType = tFXOperator::MUL;
	else
	if (ch == "/")
		this->tType = tFXOperator::DIV;
	else
	if (ch == "")
		this->tType = tFXOperator::DOT;
	else
	if (ch == "*-")
		this->tType = tFXOperator::MULSUB;
	else
	if (ch == "/-")
		this->tType = tFXOperator::DIVSUB;
	else
	if (ch == "==")
		this->tType = tFXOperator::DIVSUB;
	else
	if (ch == "<=")
		this->tType = tFXOperator::DIVSUB;
	else
	if (ch == ">=")
		this->tType = tFXOperator::DIVSUB;
	else
	{
		std::cout << "unrecognised operator "<<ch<<__FILE__<<__LINE__<<std::endl;
		__asm{int 3}
	}
}

tFXOperator::tFXOperator(OptorTypes ot)
{
	this->tType = ot;
}

tFXOperator::~tFXOperator()
{
}

std::string tFXOperator::tFXPrintStr(void)
{
	switch (this->tType)
	{
	//	enum OptorTypes{ ADD, SUB, MUL, DIV, DOT, EMP };
	case ADD: return "add";
	case SUB: return "sub";
	case MUL: return "mul";
	case DIV: return "div";
	case DOT: return "dot";
	case EMP: return "emp";
	default: return "unknown";
	}
}


tFXOperator::OptorTypes tFXOperator::tGetType(void)
{
	return this->tType;
}
