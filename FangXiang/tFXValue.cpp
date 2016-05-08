#include "tFXValue.h"
#include "tFXOperator.h"
#include <string>

// parsing string
tFXValue::tFXValue(std::string formula)
{
	try
	{
		// This is the string compile time check
		this->tCheckStr(formula);

		// Parsing String into SL
		this->tFXParseSL(formula);

	}
	catch (int e)
	{
		this->tErrorMappingComments(e);
		return;
	}
	catch (...)
	{
		std::cout << "syntax error" << std::endl;
	}
	

	// Parsing String into EOE
	this->tFXParseEOE(); // error should change throw
	// problem 
}
// parsing string array
tFXValue::tFXValue(std::vector <std::string> SL)
{
	this->SL = SL;
	this->tFXParseEOE();
}
// parsing is finished, final calculation
tFXValue::tFXValue(std::vector <tFXValue> SEL, std::vector <tFXOperator> SOL)
{
	this->EL = SEL;
	this->OL = SOL;
}
// destructing tFXValue
tFXValue::~tFXValue()
{}

// true means EndNode, false means Not EndNode 
bool tFXValue::tEndNode(std::string str)
{
	// check if this is the end node
	size_t cv = str.find_first_of("()+-*/");// 
	if (cv != std::string::npos)
		return false;
	else
		return true;
}

// true : const number, false : variable
bool tFXValue::tConstNum(std::string str)
{
	size_t cv = str.find_first_not_of("0123456789.");
	if (cv != std::string::npos)
		return false;
	else
		return true;
}

// end node required 
bool tFXValue::tConstVar(std::string str)
{	
	size_t cv = str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789.");
	if (cv != std::string::npos)
		return false;// unrecorgnized charactor
	else
	{
		cv = str.find_first_not_of("0123456789.");
		if (cv != std::string::npos)
			return true;
		else
			return false;
	}
}

// true is L, false is NOT 
bool tFXValue::IsLeave(void) // leave node has value, branch node is empty
{
	if (this->SL.size() == 1)
	{
		if (!this->EL.empty())
		{
			std::cout << "end node is not empty" << std::endl;
			__asm{int 3}
		}
		if (this->tEndNode(this->SL[0]))
			return true;
	}

	return false;
}

double tFXValue::tGetEndNodeValue(void)
{
	// risks checking
	//try{
	if (this->IsLeave());
		//throw new std::string("not leave node");

		std::string tmp = this->SL[0];
		
		if (this->tConstNum(tmp))
			return atof(this->SL[0].c_str());
		else
		{
			if (this->tConstVar(this->SL[0]))
				return 255;
			else
				;//	throw new std::string("not a const or var");
		}
	//}
	//catch (std::string& e)
	//{
	//	std::cout << e << std::endl;
	//	delete &e;
	//		__asm{int 3}
	//	}
	//	catch (){	
	//	}

}

// parsing into String List Formate
// input string has been checked already 
void tFXValue::tFXParseSL(std::string formula)
{
	// check if it is the end node
	if (this->tEndNode(formula))
	{
		//this->formula = formula;
		this->SL.push_back(formula);
		return;
	}
	/*
	// parsing to array vector string
	// std::vector <std::string> SL;
	std::string ach = "";
	std::string sum = "";
	for (int i = 0; i < formula.size(); i++)
	{
		// filter out space and tab
		if ((formula[i] == ' ') || (formula[i] == '\t'))
			continue;
		ach.clear();
		ach += formula[i];

		size_t cv = ach.find_first_of("*()+-/");
		if (cv != std::string::npos)
		{
			if (sum != "")
			{
				this->SL.push_back(sum);
				sum = "";
			}
			this->SL.push_back(ach);
		}else
			sum += ach;
	}
	if (sum != "")
	{
		this->SL.push_back(sum);
		sum = "";
	}
	//this->tFXPrint_SL();
	*/

	//================= new parsing =====================//
	// seperate operand and operator
	std::string opd_acm = "";
	std::string opt_acm = "";

	for (int i = 0; i< formula.size(); i++)
	{
		switch (formula[i])
		{
		case '(': 
		case ')':{
			// clean the stack buffer
			if (!opd_acm.empty())
			{
				this->SL.push_back(opd_acm);
				opd_acm.clear();
			}else
			if (!opt_acm.empty())
			{
				this->SL.push_back(opt_acm);
				opt_acm.clear();
			}
			// save the braket
			opt_acm += formula[i];
			this->SL.push_back(opt_acm);
			opt_acm.clear();
		};break;
		// charactor cause to ignore
		case '\s':
		case '\t':; break;
		// operator charactor
		case '+':
		case '-':
		case '*':
		case '/':
		{
			if (!opd_acm.empty())
			{
				this->SL.push_back(opd_acm);
				opd_acm.clear();
			}

			// accum the opt
			opt_acm += formula[i];

		}; break;
		// operand (other case)
		default: 
		{
			if (!opt_acm.empty())
			{
				this->SL.push_back(opt_acm);
				opt_acm.clear();
			}

			// accum the opd
			opd_acm += formula[i];
		};
		}//end of switch
	}// end of for-loop

	// if stack is having buffer
	if (!opd_acm.empty())
	{
		this->SL.push_back(opd_acm);
		opd_acm.clear();
	}
	else
	if (!opt_acm.empty())
	{
		this->SL.push_back(opt_acm);
		opt_acm.clear();
	}
	//===================================================//
}

// the SL is done 
// assume there is no error syntx
// first SL[0] is not */ )
// we deal with SL[0] is + - later
// ileagul input check before everything else
void tFXValue::tFXParseEOE(void)
{
	// Pre: the SL is done

	// Parsing EOE Error Checking
	size_t tm = this->SL[0].find_first_of("*)/");
	if (tm != std::string::npos)
	{
		throw 3001;
	}

	// Check if it End Node, // if less than 1 then end node and return, // there will be no new Element created
	if (this->SL.size() <= 1) // this will cause problem
		return;

	// control varibles;
	std::vector<std::string> accum;
	accum.clear();
	bool start = false;
	int LBC = 0; // left braket count

	for (int i = 0; i< this->SL.size(); i++)
	{
		if (!start){
			// it is an ELEMENT
			//std::cout << this->SL[i] << std::endl;
			if (this->SL[i] == "(")
			{
				start = true;
				LBC++;
			}
			else // if it is a CONST
			if (this->SL[i].find_first_of(")(+-*/")==std::string::npos)
			{
			//	std::cout << "============" << this->SL[i] << std::endl;//const seems to be ok all the time
				std::vector<std::string> tmp;
				tmp.clear();
				tmp.push_back(this->SL[i]);
				tFXValue obj(tmp);
				this->EL.push_back(obj);

				if (this->EL.size() == (2 + this->OL.size()))
				{
					tFXOperator opt(tFXOperator::DOT);
					this->OL.push_back(opt);
				}
			}
			else	// this would be the Operator one and start as initial
			{		// "+ - * /"
				tFXOperator opt(this->SL[i]);
				this->OL.push_back(opt);
				//
				if (this->OL.size() > this->EL.size())
				{
					//except multiplication
					tFXValue opt("0");
					this->EL.push_back(opt);
					//this->EL.push_back(new tFXValue("0"));
				}
				else // * / is used at the begining 
				{
					if (0){
						std::cout << "+- , problem" << __FILE__ << __LINE__ << std::endl;
						__asm{int 3}
					}
				}
			}
		}// element already started
		else
		{
			if (this->SL[i] == "(")
			{
				LBC++;
				accum.push_back(this->SL[i]);
				continue;
			}

			if (this->SL[i] == ")")
			{
				LBC--;
				if (LBC == 0)
				{
					tFXValue obj(accum);
					this->EL.push_back(obj);
					// DOT
					if (this->EL.size() == (2 + this->OL.size()))
					{
						tFXOperator opt(tFXOperator::DOT);
						this->OL.push_back(opt);
					}
					accum.clear();
					start = false;
				}
				else
				{
					// adding ")" into accum
					accum.push_back(this->SL[i]);
				}
				continue;
			}

			// not "(" or ")" put into accum
			accum.push_back(this->SL[i]);
		}
	}
}

// the EOE is done // EOE there will be no brackets anymore
// assume everything is correct
double tFXValue::tFXCalcu(void)
{
	// check if it is end node
	if (this->IsLeave())
	{
		double ret = this->tGetEndNodeValue();
		//delete this;
		return ret;
	}
	else
	{
		// check element
		// check operator, return index, print out the size
		// std::cout << "E:" << this->EL.size() << ", O:" << this->OL.size() << std::endl;
		// check here in the future
		if (this->OL.empty())
		{
			if (this->EL.size() == 1)
			{
				double ret = this->EL[0].tFXCalcu();
			//	delete this;
				return ret;
			}else
			{
				std::cout <<"Error "<< "E:" << this->EL.size() << ", O:" << this->OL.size() << std::endl;
				__asm{int 3};
			}
		}
		else
		{
			// search throw the OL list;
			// return index to split
			// funX(index);

			int spliter = this->tSplitEOE(this->OL);
			
			if (spliter==-1)
			{
				std::cout <<"ERROR spliter ==-1"<< std::endl;
				__asm{int 3}
			}

			std::vector <tFXValue>	SEL_A;
			std::vector <tFXValue>	SEL_B;
			std::vector <tFXOperator> SOL_A;
			std::vector <tFXOperator> SOL_B;

			SEL_A.clear();
			SEL_B.clear();
			SOL_A.clear();
			SOL_B.clear();

			for (int i = 0; i<this->EL.size(); i++)
			{
				if (i<=spliter)
				{
					SEL_A.push_back(this->EL[i]);
					if (i!=spliter)
					SOL_A.push_back(this->OL[i]);
				}
				else
				{
					SEL_B.push_back(this->EL[i]);
					if (i< this->OL.size())
					SOL_B.push_back(this->OL[i]);
				}
			}

			tFXValue A(SEL_A, SOL_A);
			tFXValue B(SEL_B, SOL_B);

			 // Doing the assembly
			switch(this->OL[spliter].tGetType())
			{
			case tFXOperator::ADD: { double ret = (A.tFXCalcu() + B.tFXCalcu());/* delete this;*/ return ret; }
			case tFXOperator::SUB: { double ret = (A.tFXCalcu() - B.tFXCalcu());/* delete this;*/ return ret; }
			case tFXOperator::MUL: { double ret = (A.tFXCalcu() * B.tFXCalcu());/* delete this;*/ return ret; }
			case tFXOperator::DIV: { double ret = (A.tFXCalcu() / B.tFXCalcu());/* delete this;*/ return ret; }
			case tFXOperator::DOT: { double ret = (A.tFXCalcu() * B.tFXCalcu());/* delete this;*/ return ret; }
			default:
				{
					std::cout <<"unrecognised sign char"<<this->OL[spliter].tFXPrintStr()<< std::endl;
					__asm{int 3}
				};
			}
		}
	}
}

void tFXValue::tFXPrintNode(void)
{
	if (this->SL.size() != 1)
	{
		std::cout << "$(" << this->SL.size() << ")" << std::endl;		
		//std::cout << "[";
		this->tFXPrint_SL();
		//std::cout<< ")" << std::endl;
		std::cout << "E(" << this->EL.size() << ")" << std::endl;
		std::cout << "O(" << this->OL.size() << ")" << std::endl;

		for (int i = 0; i < EL.size(); i++)
		{
			std::cout << "#";
			this->EL[i].tFXPrintNode();
		}
	}
	else // this is end node
		std::cout << "%" << this->SL[0] << std::endl;
}	

void tFXValue::tFXPrint_SL(void)
{
	for (int i = 0; i< this->SL.size();i++)
	{
		std::cout << "." << this->SL[i];
	}
	std::cout << std::endl;
}

int tFXValue::tSplitEOE(std::vector <tFXOperator> SOL)
{
	int add_idx = -1;
	int mul_idx = -1;
	int dot_idx = -1;

	for (int i = 0; i< SOL.size(); i++)
	{
		switch (SOL[i].tGetType())
		{
		case tFXOperator::ADD: 
		case tFXOperator::SUB: add_idx = i; break;
		case tFXOperator::MUL:
		case tFXOperator::DIV: mul_idx = i; break;
		case tFXOperator::DOT: dot_idx = i; break;
		//default try catch throw
		}
	}

	if (add_idx != -1)
		return add_idx;
	
	if (mul_idx != -1)
		return mul_idx;
	
	if (dot_idx != -1)
		return dot_idx;

	return -1;
}

// risk management
void tFXValue::tCheckStr(const std::string str)
{
	// no illeague charactors
	// charactor allowed >> a~z A~Z 0~9 _ +-*/ ()
	// ileague charactor check // in the future change it into 
	std::size_t found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz()+-/*0123456789.ABCDEFGHIJKLMNOPQRSTUVWXYZ_	");
	if (found != std::string::npos)
		throw 10001;
	
	// stack check bracket 
	int count = 0;
	for (int i = 0; i<str.size(); i++)
	{
		switch (str[i])
		{
		case '(': count++; break;
		case ')': count--; break;
		default: continue;
		}
	}
	// after this check 
	if (count != 0)
		throw 10002;
	
	// repeating sign
	int signcount = 0;
	for (int i = 0; i<str.size(); i++)
	{
		switch (str[i])
		{
		case '*': signcount++; break;
		case '/': signcount++; break;
		case '+': signcount++; break;
		case '-': signcount++; break;
		default: signcount &= -2;
		}

		if (signcount >= 2)
			throw 10003;
	}

}

void tFXValue::tErrorMappingComments(int merrno)
{
	switch (merrno)
	{
	case 10001: std::cout << "Syntax Error: illeague charactor" << std::endl; break;
	case 10002: std::cout << "Syntax Error: brackets number not match " << std::endl; break;
	case 10003: std::cout << "Syntax Error: repeating sign" << std::endl; break;

	case 30001: std::cout << "Syntax Error: illeague operator " << std::endl; break;
	//case 10004: "";
	//case 10005: "";
	}
}







