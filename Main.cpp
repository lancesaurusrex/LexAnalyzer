#include "LexicalAnalyzer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <locale> 

using namespace std;

list<CToken>::const_iterator currentToken;
bool Program(CLexicalAnalyzer &c);
bool Definition();
bool DataDef();
bool FuncDef();
bool Type();

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
		//prsea here
	}
	currentToken = Lexic.cbegin();
	if (Program(Lexic)){}

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
	std::cout << '\n' << '\n' << '\n';
	std::cout << '\n' << '\n' << '\n';
	
	std::cout << '\n' << '\n' << '\n';
	std::cout << '\n' << '\n' << '\n'; 
	Lexic.GetAllToken();
	string blank;
	std::cin >> blank;
	return 0;
}

bool Program(CLexicalAnalyzer &c)
{
	
	list<CToken>::const_iterator temp;
	temp = currentToken;


	if (currentToken == c.cend())
		return false;

	if (Definition())
	{
		cout << "Definition =>Statement Statlist" << endl;
		if (Definition()){
			
			return true;
		}
	}
	else
		return false;
}

bool Definition()
{
	list<CToken>::const_iterator temp;
	temp = currentToken;

	//If true goes into brackets
	if (DataDef())
	{
		Definition();
	}

	if (FuncDef())
	{

	}
	return true;
}

//enum { nilT, idT, symbolT, operatorT, preT, intT, decimalT, stringT, keyT, errorT, endlineT};
bool DataDef() {
	list<CToken>::const_iterator temp;
	temp = currentToken;

	if (Type())
		return true;
	else
		return false;
}

bool FuncDef() {
	list<CToken>::const_iterator temp;
	temp = currentToken;

	return true;//compiler bitch
}

bool Type() {
	list<CToken>::const_iterator temp;
	temp = currentToken;
	//keyword int decimal string
	if (currentToken->getTokenType() == 8) {
		if (currentToken->getTokenName() == "int" || currentToken->getTokenName() == "double" || currentToken->getTokenName() == "string") {
			currentToken++;
			if (Expression())
				return true;
		}
	}

	return false;
}

bool string_is_valid(const std::string &str)
{
	return find_if(str.begin(), str.end(),
		[](char c) { return !(isalnum(c) || (c == ' ')); }) == str.end();
}

bool Expression() {
	if (Indentifer()){//id sym exp}

	if (IDNext()) {}

}

bool Indentifer() {
	list<CToken>::const_iterator temp;
	temp = currentToken;

	if ((string_is_valid(currentToken->getTokenName))){
		//is id
		currentToken++;
		if (AssignSym()){//is assignsym gobacktoxpr}
		else if (CompSym()){//is compsym go \backtoxpr}
		else//idnext
	}
	else
		return false;
}