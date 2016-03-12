#include "LexicalAnalyzer.h"
#include <fstream>
#include <sstream>
#include <iostream>

int main() 
{
	CLexicalAnalyzer Lexic;

	std::vector<CSymbol> CustomTypes;

	CustomTypes.emplace_back(CSymbol("==", operatorT));
	CustomTypes.emplace_back(CSymbol("[", symbolT));
	CustomTypes.emplace_back(CSymbol("]", symbolT));
	CustomTypes.emplace_back(CSymbol("(", symbolT));
	CustomTypes.emplace_back(CSymbol(")", symbolT));

	Lexic.setKeyword(CSymbol("Penup", keyT));
	Lexic.setKeyword(CSymbol("Pendown", keyT));
	Lexic.setKeyword(CSymbol("Forward", keyT));
	Lexic.setKeyword(CSymbol("Back", keyT));
	Lexic.setKeyword(CSymbol("Right", keyT));
	Lexic.setKeyword(CSymbol("Left", keyT));
	Lexic.setKeyword(CSymbol("Create", keyT));
	Lexic.setKeyword(CSymbol("If", keyT));
	Lexic.setKeyword(CSymbol("Color", keyT));
	Lexic.setKeyword(CSymbol("Setcolor", keyT));
	Lexic.setKeyword(CSymbol("Repeat", keyT));
	Lexic.setKeyword(CSymbol("Define", keyT));
	Lexic.setKeyword(CSymbol("Call", keyT));
	Lexic.setKeyword(CSymbol("End", keyT));
	Lexic.setColor(CSymbol("red", colorT));
	Lexic.setColor(CSymbol("orange", colorT));
	Lexic.setColor(CSymbol("yellow", colorT));
	Lexic.setColor(CSymbol("green", colorT));
	Lexic.setColor(CSymbol("blue", colorT));
	Lexic.setColor(CSymbol("purple", colorT));
	Lexic.setColor(CSymbol("white", colorT));
	Lexic.setColor(CSymbol("black", colorT));

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

	Lexic.GetAllToken();
	//Lexic.PreprocessingDefine();
	//Lexic.PreprocessingID();
	//Lexic.PreprocessingComments();
	std::cout << '\n' << '\n' << '\n';
	std::cout << '\n' << '\n' << '\n';

	string blank;
	std::cin >> blank;
	return 0;
}