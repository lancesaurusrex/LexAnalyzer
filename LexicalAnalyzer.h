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
	void setTokenName(string name);
	bool operator==(const CToken& other) {
		return (this->TokenType == other.TokenType && this->TokenName == other.TokenName);
	}

protected:
	int TokenType;
	string TokenName;
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
};

//This class is the lexical analyser
class CLexicalAnalyzer
{
public:
	void ClearAllTokens();
	void GetAllToken();
	void ClearToken(CToken a);
	//bool IsAllAlphaOrDigit(string s, int begin, int length);
	bool IsSequenceEmpty();
	void AddToken(CToken token);
	void String2TokenSequence(string sequence);
	void setSymbol(CSymbol Symbol);
	void setKeyword(CSymbol Symbol);
	void PreprocessingDefine();
	void PreprocessingComments();
	CLexicalAnalyzer();
	virtual ~CLexicalAnalyzer();
	//TokenSequence iterators
	typedef list<CToken>::iterator CTiterator;
	CTiterator begin() { return TokenSequence.begin(); }
	CTiterator end() { return TokenSequence.end(); }
	typedef list<CToken>::const_iterator CTconst_iterator;
	CTconst_iterator cbegin() { return TokenSequence.cbegin(); }
	CTconst_iterator cend() { return TokenSequence.cend(); }
	//SymbolTable iterators
	typedef vector<CSymbol>::const_iterator STconst_iterator;
	STconst_iterator STbegin() { return SymbolTable.cbegin(); }
	STconst_iterator STend() { return SymbolTable.cend(); }

protected:
	vector<CSymbol> SymbolTable;
	list<CToken> TokenSequence;
	vector<CSymbol> KeywordTable;

};



