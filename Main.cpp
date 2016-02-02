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
	Lexic.setKeyword(CSymbol("if", keyT));
	Lexic.setKeyword(CSymbol("else", keyT));
	Lexic.setKeyword(CSymbol("for", keyT));
	Lexic.setKeyword(CSymbol("while", keyT));
	Lexic.setKeyword(CSymbol("void", keyT));
	Lexic.setKeyword(CSymbol("int", keyT));
	Lexic.setKeyword(CSymbol("double", keyT));
	Lexic.setKeyword(CSymbol("float", keyT));
	Lexic.setKeyword(CSymbol("string", keyT));


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

	for (std::string line; std::getline(infile1, line);)
	{
		Lexic.String2TokenSequence(line);
	}

	for (std::string line; std::getline(infile2, line);)
	{
		Lexic.String2TokenSequence(line);
	}
	Lexic.GetAllToken();
	Lexic.PreprocessingDefine();
	Lexic.PreprocessingID();
	Lexic.PreprocessingComments();
	std::cout << "SPACE       00" << '\n';
	std::cout << "SPACE       00" << '\n';
	std::cout << "SPACE       00" << '\n' << '\n' << '\n';
	Lexic.GetAllToken();
	string blank;
	std::cin >> blank;
	return 0;
}