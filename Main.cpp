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
bool Expression();
bool Identifier();
bool IODef();
bool Statement();

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

	}
	currentToken = Lexic.cbegin();
	if (Program(Lexic)){
		Program(Lexic);
		cout << "Parse great success!" << '\n' << '\n';
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
		if (currentToken->getTokenName() == "$") {
			cout << "Definition =>Data def|Funct def" << '\n';
			currentToken++;
			Program(c);
		}
		else
			cout << "expecting ;" << '\n';
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
		if (currentToken->getTokenName() == ";") {
			cout << "Data Def => Type Expr ;" << '\n';
			currentToken++;
			return true;
		}
	}

	if (FuncDef())
	{
		
	}

	if (IODef())
	{
		cout << "IO IOSym Exp" << '\n';
		return true;
	}

	if (Statement()){
		cout << "StatementDef => { Exp } || if ( EXP ) Statement";
		return true;
	}
	return false;
}

//enum { nilT, idT, symbolT, operatorT, preT, intT, decimalT, stringT, keyT, errorT, endlineT};
bool DataDef() {
	list<CToken>::const_iterator temp;
	temp = currentToken;

	if (Type()) {
		cout << "Type => int|double|string" << '\n';
		return true;
	}

	if (Expression()) {
		cout << "DD => Expr";
	}
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
			if (Expression()) {
				cout << "Expr => ID Assignsym Expr|ID Comp_sym Expr|ID_Next" << '\n';
				return true;
			}
		}
	}

	return false;
}

bool string_is_valid(const std::string &str)
{
	return find_if(str.begin(), str.end(),
		[](char c) { return !(isalnum(c)); }) == str.end();
}

bool Expression() {
	if (Identifier()) {

		if (Identifier()) {

			return true;
		}
	}

	return false;
}

bool Identifier() {
	list<CToken>::const_iterator temp;
	temp = currentToken;
	//Identifer assignsym || Identifier compsym

	//check for id and then peek ahead for sym and check
	if (currentToken->getTokenType() == 1 && (string_is_valid(currentToken->getTokenName())) ){

		temp++;		//peek ahead to symbol
		if (temp->getTokenType() == 3) {

			if (temp->getTokenName() == "=" || temp->getTokenName() == "+" ||
				temp->getTokenName() == "-" || temp->getTokenName() == "*" || temp->getTokenName() == "/") {

				cout << "ID Assignsym ";
				currentToken++;	//move forward from id
				currentToken++;	//move forward from assignsym;
				return true;
			}

			if (temp->getTokenName() == "!=" || temp->getTokenName() == "==" ||
				temp->getTokenName() == "<"  || temp->getTokenName() == ">" ||
				temp->getTokenName() == "<=" || temp->getTokenName() == ">=") {

				cout << "ID CompSym ";
				currentToken++;	//move forward from id
				currentToken++;	//move forward from compsym;
				return true;
			}
		}
		//is id but peek ahead not a sym
		else {
			currentToken++;	//move forward from id, next statement not sym
			return true;
		}

	}
	//not an id, ITS A string
	if (currentToken->getTokenType() == 7 && (string_is_valid(currentToken->getTokenName())))
	{
			currentToken++;	//go forward past string

			cout << "string" << '\n';
			return true;
		
	}

	if ((string_is_valid(currentToken->getTokenName()))) {
		if (currentToken->getTokenType() == 5) {

			currentToken++;

			cout << "int" << '\n';
			return true;
		}
	}
	//decimals wont pass the string_is_valid test
	if ( currentToken->getTokenType() == 6){ 
		currentToken++;

	cout << "double" << '\n';
	return true;
}
	return false;


}

bool IODef() {

	list<CToken>::const_iterator temp;
	temp = currentToken;

	if (currentToken->getTokenType() == 8){
		if (currentToken->getTokenName() == "cin" || currentToken->getTokenName() == "cout") {
			temp++;
			bool extLoop = true;

			while (extLoop == true){
				if (temp->getTokenType() == 3) {
					if (temp->getTokenName() == "<<" || temp->getTokenName() == ">>") {
						temp++;
						currentToken++;	//go forward over keyword
						currentToken++;	//go forward over extractor

						if (Identifier()) {
							temp++;	//peek for extractor or ;
							if (temp->getTokenName() == ";") {
								currentToken++;
								return true;
							}
								
						}
						else {
							cout << "Can't find ; at end of IO IOSYM ID" << '\n';
							return false;
						}
					}
				}
			}
		}
	}
	return false;
}

bool Statement() {

	list<CToken>::const_iterator temp;
	temp = currentToken;

	if (currentToken->getTokenName() == "if") {
		++currentToken;	//forward off of if
		if (currentToken->getTokenName() == "(") {
			++currentToken;	//forward off of (
			if (Expression()) {
				if (currentToken->getTokenName() == ")") {
					currentToken++;
					if (Statement()) {
						cout << "if ( Expression ) Statement " << '\n';
						return true;
					}
				}
				else
					cout << "No ) in" << temp->getTokenName() << "Statement" << '\n';
			}
		}
		else
			cout << "No ( in" << temp->getTokenName() << "Statement" << '\n';
	}

	if (currentToken->getTokenName() == "{"){
		currentToken++;
		temp++;
		if (temp->getTokenType() == 8) //peek next, if keyword go to type
			Type();
		else
			Expression();
		if (currentToken->getTokenName() == ";")
			currentToken++;
		else
			cout << "No ; at the end";
		if (currentToken->getTokenName() == "}")
		{
			currentToken++;
			cout << "{ Expression }" << '\n';
			return true;
		}
		else
			cout << "No { before " << temp->getTokenName() << " Expression" << '\n';

	}
	else
		cout << "No } after " << temp->getTokenName() << " Expression" << '\n';

	return false;
}