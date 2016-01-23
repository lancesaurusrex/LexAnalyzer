#include "LexicalAnalyzer.h"
#include <fstream>
#include <sstream>
#include <iostream>

int main() 
{
	CLexicalAnalyzer Lexic;

	std::vector<CSymbol> CustomTypes;
	CSymbol ee("{", 2);
	//CustomTypes.emplace_back(ee);
	CustomTypes.emplace_back(CSymbol("=", operatorT));
	CustomTypes.emplace_back(CSymbol("+", operatorT));
	CustomTypes.emplace_back(CSymbol("-", operatorT));
	CustomTypes.emplace_back(CSymbol("*", operatorT));
	CustomTypes.emplace_back(CSymbol("/", operatorT));
	CustomTypes.emplace_back(CSymbol("+=", operatorT));
	CustomTypes.emplace_back(CSymbol("-=", operatorT));
	CustomTypes.emplace_back(CSymbol("*=", operatorT));
	CustomTypes.emplace_back(CSymbol("/=", operatorT));
	CustomTypes.emplace_back(CSymbol("%", operatorT));
	CustomTypes.emplace_back(CSymbol("++", operatorT));
	CustomTypes.emplace_back(CSymbol("--", operatorT));
	CustomTypes.emplace_back(CSymbol("==", operatorT));
	CustomTypes.emplace_back(CSymbol("!=", operatorT));
	CustomTypes.emplace_back(CSymbol(">", operatorT));
	CustomTypes.emplace_back(CSymbol("<", operatorT));
	CustomTypes.emplace_back(CSymbol("<<", operatorT));
	CustomTypes.emplace_back(CSymbol(">>", operatorT));
	CustomTypes.emplace_back(CSymbol(">=", operatorT));
	CustomTypes.emplace_back(CSymbol("<=", operatorT));
	CustomTypes.emplace_back(CSymbol("&&", operatorT));
	CustomTypes.emplace_back(CSymbol("||", operatorT));
	CustomTypes.emplace_back(CSymbol("!", operatorT));
	CustomTypes.emplace_back(CSymbol("&", operatorT));
	CustomTypes.emplace_back(CSymbol("|", operatorT));
	CustomTypes.emplace_back(CSymbol("^", operatorT));
	CustomTypes.emplace_back(CSymbol(".", operatorT));
	CustomTypes.emplace_back(CSymbol("(", symbolT));
	CustomTypes.emplace_back(CSymbol(")", symbolT));
	CustomTypes.emplace_back(CSymbol("{", symbolT));
	CustomTypes.emplace_back(CSymbol("}", symbolT));
	CustomTypes.emplace_back(CSymbol(",", symbolT));
	CustomTypes.emplace_back(CSymbol(";", symbolT));
	CustomTypes.emplace_back(CSymbol("#", preT));
	CustomTypes.emplace_back(CSymbol("//", preT));
	Lexic.setKeyword(CSymbol("cout", keyT));
	Lexic.setKeyword(CSymbol("cin", keyT));

	/*for (int i = 0; i < 1; ++i) 
	{
		string a = "+";
		int b = operatorT;
		CSymbol fork(a, b);
		CustomTypes.emplace_back(fork);
	}*/

	for each(CSymbol cs in CustomTypes) 
	{
		Lexic.setSymbol(cs);
	}

	std::ifstream infile("Text.txt");
	std::ifstream infile1("Text1.txt");
	std::ifstream infile2("Text2.txt");

	std::string line;
	for (std::string line; std::getline(infile, line); )
	{
		Lexic.String2TokenSequence(line);		
	}
	//Lexic.GetAllToken();
	for (std::string line; std::getline(infile1, line);)
	{
		Lexic.String2TokenSequence(line);
	}
	//Lexic.GetAllToken();
	for (std::string line; std::getline(infile2, line);)
	{
		Lexic.String2TokenSequence(line);
	}
	Lexic.GetAllToken();

	string blank;
	std::cin >> blank;
	return 0;
}