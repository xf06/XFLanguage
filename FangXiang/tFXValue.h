#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "tFXOperator.h"
#include "vld.h"

class tFXValue
{
public:
	// parsing string
	tFXValue(std::string formula);
	tFXValue(std::vector <std::string> SL);
	tFXValue(std::vector <tFXValue> SEL, std::vector <tFXOperator> SOL);
	~tFXValue();
	
	// Parse into [String List]
	void tFXParseSL(std::string formula); // error checking should be included here // in the future
	// Parse into [EOE List]
	void tFXParseEOE(void);	
	// Process (E)O(E)
	double tFXCalcu(void);

	// tFXPrint Ended
	void tFXPrintNode(void);
	// not in use
	double tGetValue(void);
	// Checking if EOE parsing correctly
	void tFXPrint_SL(void);

private:

	std::vector <std::string> SL;
	std::vector <tFXValue>	EL;
	std::vector <tFXOperator> OL;

	// string manipulation
	bool tEndNode(std::string);
	bool tConstNum(std::string str);
	bool tConstVar(std::string str);
	bool IsLeave(void);// true is L, false is NOT

	double tGetEndNodeValue(void);
	
	int tSplitEOE(std::vector <tFXOperator> SOL); //
	
	// risk management compile time error
	void tCheckStr(const std::string str);

	// risk management run time error
	void tErrorMappingComments(int merrno);

	// string parsing into SL 
	
};

// erro mapping comments
