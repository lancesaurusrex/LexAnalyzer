#pragma once

#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<iterator>
#include<iostream>
#include<map>
#include<ctype.h>

using std::string;
using std::list;
using std::vector;

enum { nilT, idT, symbolT, operatorT, preT, intT, decimalT, stringT, keyT, errorT, endlineT};

//This class is a token
class CToken
{
	friend class CLexicalAnalyzer;
	friend std::ostream& operator<<(std::ostream& os, const CToken& dt);
public:
	CToken();
	virtual ~CToken();
	int getTokenType() const { return TokenType; }
	string getTokenName() const  { return TokenName; }
	
	//int getTokenInt() { return TokenInt; }
	//double getTokenReal() { return TokenReal; }

protected:
	int TokenType;

	string TokenName;
	//union
	//{
	//	int TokenInt;
	//	double TokenReal;
	//};
};


//This class represent one symbol
class CSymbol
{
public:
	CSymbol();
	CSymbol(string string, int type);
	virtual ~CSymbol();

	string SymbolString;
	int TokenType;

	string GetSymbolString() { return SymbolString; }

	//bool operator < (CSymbol &Symbol);
	//bool operator <= (CSymbol &Symbol);

	//bool operator > (CSymbol &Symbol);
	//bool operator >= (CSymbol &Symbol);

};

//This class is the lexical analyser
class CLexicalAnalyzer
{
public:
	//void SetCurrentPosition(POSITION pos);
	//POSITION GetCurrentPosition();
	void ClearAllTokens();
	void GetAllToken();
	//bool IsAllAlphaOrDigit(string s, int begin, int length);
	bool IsSequenceEmpty();
	void AddToken(CToken token);
	void String2TokenSequence(string sequence);
	void setSymbol(CSymbol Symbol);
	void setKeyword(CSymbol Symbol);
	CLexicalAnalyzer();
	virtual ~CLexicalAnalyzer();
	typedef list<CToken>::const_iterator const_iterator;
	const_iterator begin() { return TokenSequence.cbegin(); }
	const_iterator end() { return TokenSequence.cend(); }
	

protected:
	vector<CSymbol> SymbolTable;
	list<CToken> TokenSequence;
	vector<CSymbol> KeywordTable;

};



