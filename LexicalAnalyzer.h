#pragma once

#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<iterator>
#include<iostream>
#include<map>
#include<ctype.h>
#include<sstream>

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
	bool operator==(const CToken& other) { return (*this == other); }
	bool operator==(const string& other) const {
		return (this->TokenName.compare(other) == 0);
	}
	

protected:
	int TokenType;
	string TokenName;
	string TokenValue;
	int TokenValueType;
};

//This class represent one symbol
class CSymbol
{
public:
	CSymbol();
	CSymbol(string string, int type);
	virtual ~CSymbol();
	bool operator== (const string& other) const{
		return (this->SymbolString.compare(other) == 0);
	}

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
	void PreprocessingID();
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
	typedef vector<CSymbol>::const_iterator KTconst_iterator;
	KTconst_iterator KTbegin() { return KeywordTable.cbegin(); }
	KTconst_iterator KTend() { return KeywordTable.cend(); }
	typedef list<CToken>::iterator IDiterator;
	IDiterator IDbegin() { return IDValue.begin(); }
	IDiterator IDend() { return IDValue.end(); }

protected:
	vector<CSymbol> SymbolTable;
	list<CToken> TokenSequence;
	list<CToken> IDValue;
	vector<CSymbol> KeywordTable;

};



