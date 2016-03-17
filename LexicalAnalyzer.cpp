#include "LexicalAnalyzer.h"


char *EnumTypes[] =
{
	"nil",
	"identifer",
	"symbol",
	"operator",
	"preprocessor",
	"int",
	"decimal",
	"string",
	"keyword",
	"error",
	"endline",
	"color"
};


CToken::CToken() : TokenType(nilT)
{

}

CToken::~CToken()
{

}

void CToken::setTokenName(string name)
{
	TokenName = name;
}
//////////////////////////////////////////////////////////////////////
// CLexicalAnalyzer Class
//////////////////////////////////////////////////////////////////////


// Construction/Destruction

CLexicalAnalyzer::CLexicalAnalyzer()
{
	setSymbol(CSymbol("==", operatorT));
	setSymbol(CSymbol("[", symbolT));
	setSymbol(CSymbol("]", symbolT));
	setSymbol(CSymbol("(", symbolT));
	setSymbol(CSymbol(")", symbolT));
	setKeyword(CSymbol("Penup", keyT));
	setKeyword(CSymbol("Pendown", keyT));
	setKeyword(CSymbol("Forward", keyT));
	setKeyword(CSymbol("Back", keyT));
	setKeyword(CSymbol("Right", keyT));
	setKeyword(CSymbol("Left", keyT));
	setKeyword(CSymbol("Create", keyT));
	setKeyword(CSymbol("If", keyT));
	setKeyword(CSymbol("Color", keyT));
	setKeyword(CSymbol("Setcolor", keyT));
	setKeyword(CSymbol("Repeat", keyT));
	setKeyword(CSymbol("Define", keyT));
	setKeyword(CSymbol("Call", keyT));
	setKeyword(CSymbol("End", keyT));
	setColor(CSymbol("red", colorT));
	setColor(CSymbol("orange", colorT));
	setColor(CSymbol("yellow", colorT));
	setColor(CSymbol("green", colorT));
	setColor(CSymbol("blue", colorT));
	setColor(CSymbol("purple", colorT));
	setColor(CSymbol("white", colorT));
	setColor(CSymbol("black", colorT));
}

CLexicalAnalyzer::~CLexicalAnalyzer()
{

}


// CSymbol Class

CSymbol::CSymbol(string string, int type) : SymbolString(string), TokenType(type)
{

}

CSymbol::~CSymbol()
{

}



void CLexicalAnalyzer::setSymbol(CSymbol Symbol)
{
	SymbolTable.emplace_back(Symbol);
}

void CLexicalAnalyzer::setKeyword(CSymbol Symbol)
{
	KeywordTable.emplace_back(Symbol);
}
void CLexicalAnalyzer::setColor(CSymbol Symbol)
{
	ColorTable.emplace_back(Symbol);
}
CSymbol::CSymbol()
{

}

void CLexicalAnalyzer::String2TokenSequence(string sequence)
{
	CToken token;

	//This loop goes to every character and tokenize the string
	for (int i = 0; i< sequence.length(); i++)
	{
		token.TokenName.clear();	//reset for next iteration
		token.TokenType = nilT;

		//if character is a space or tab, skip
		if (sequence[i] == ' ' || sequence[i] == '\t')
			continue;
		//else if the character is a "
		else if (sequence[i] == '\"')
		{
			i++;
			token.TokenType = stringT;

			while(i< sequence.length() && sequence[i] != '\"')
			{
				token.TokenName += sequence[i];
				i++;
			}

			AddToken(token);
		}
		//check for comment // or /*
		else if (sequence[i] == '/')
		{
			//check for 2 slashes on comment
			if ((i + 1) < sequence.length()) {	//Check for outofbounds
				if (sequence[i + 1] == '/') {	//check for second slash or star, do star seperately 

					token.TokenType = preT;
					token.TokenName = sequence;

					AddToken(token);
					i = sequence.length();	//get to end of line to skip to next line
				}
			}
		}

		else if (sequence[i] == '#')
		{
			token.TokenType = preT;

			while (i < sequence.length())
			{
				token.TokenName += sequence[i];
				i++;
			}
			AddToken(token);		
		}
		//else if the character is a newline... nor for strings
		else if (sequence[i] == '\\')	
		{
			if (i + 1 < sequence.length() && sequence[i + 1] == 'n') {
				token.TokenType = endlineT;
				i++; //for firstslash
				i++; //for n
				AddToken(token);
			}
		}
		//else if the character is a digit or a decimal point...
		else if (isdigit(sequence[i]))	//take out decimal point?
		{
			token.TokenType = intT;

			//while the character is within bounds and is either a 
			//digit or decimal point...
			while ((isdigit(sequence[i]) || sequence[i] == '.'))
			{
				if (sequence[i] == '.') 
					token.TokenType = decimalT;

				token.TokenName += sequence[i];
				i++;
			}
			i--;//Need to decrement it because in the for loop, i will be incremented
			//if (token.TokenType == intT) token.TokenInt = atoi(token.TokenName);
			//else if (token.TokenType == decimalT) token.TokenDecimal = atof(token.TokenName);

			AddToken(token);
		}
		//else if the character is still neither number, newline or quotes,
		//symbol
		else if (token.TokenType == nilT)
		{
			//if the following sequence string matches the string of one of
			//the symbol in the symbol table...
			//see how long the token to search is and get it

			//PEEK FOR COMPARSION
			string search(1, sequence[i]);
			//peek +-=|&
			if ((i+1) < sequence.length()) {	//Check for outofbounds
				if (!isspace(sequence[i + 1])) {	//check for space
					if ((sequence[i + 1] == '+' || sequence[i + 1] == '-' ||
						sequence[i + 1] == '=' || sequence[i + 1] == '|' || sequence[i + 1] == '&' ||
						sequence[i + 1] == '>' || sequence[i + 1] == '<'))
					{	
						search.resize(2, sequence[i + 1]);	//checking to see if it is a 2 char operator
						token.TokenName = search;
						i++;	//if 2nd found got to move ahead one, ex: << on next loop it will be on < not the space 
					}
				}
			}
			
			CSymbol foundCSymbol;
			auto it = std::find_if(SymbolTable.cbegin(), SymbolTable.cend(), [search](CSymbol a) { return a.GetSymbolString()==search; });	//is sequence in symbolTable?
			if (it != SymbolTable.cend())
			{
				foundCSymbol = *it;
				token.TokenName = foundCSymbol.SymbolString;
				token.TokenType = foundCSymbol.TokenType;
				
				AddToken(token);
			}		
		}
		//still, check for keywords 
		if (token.TokenType == nilT) 
		{
			int oldi = i;	//reset i if not found;

			if (i < sequence.length() && isalpha(sequence[i]))
			{
				string found;

				while (i < sequence.length() && isalpha(sequence[i])) 
				{
					found += sequence[i];
					//token.TokenType = foundCSymbol.TokenType;
					i++;	
				}
				auto it = std::find_if(KeywordTable.cbegin(), KeywordTable.cend(), [found](CSymbol a) { return a.GetSymbolString() == found; });	//is sequence in symbolTable?
				if (it != KeywordTable.cend()) 
				{
					CSymbol foundSymbol = *it;
					token.TokenName = foundSymbol.SymbolString;
					token.TokenType = foundSymbol.TokenType;
					
					AddToken(token);
				}
				else
				{
					i = oldi;
				}

			}
		}
		//color check
		if (token.TokenType == nilT)
		{
			int oldi = i;	//reset i if not found;
			if (i < sequence.length() && isalpha(sequence[i]))
			{
				string found;

				while (i < sequence.length() && isalpha(sequence[i]))
				{
					found += sequence[i];
					//token.TokenType = foundCSymbol.TokenType;
					i++;
				}


				auto itColor = std::find_if(ColorTable.cbegin(), ColorTable.cend(), [found](CSymbol b) { return b.GetSymbolString() == found; });
				if (itColor != ColorTable.cend())
				{
					CSymbol foundColor = *itColor;
					token.TokenName = foundColor.SymbolString;
					token.TokenType = foundColor.TokenType;
					--i;	//for ends on length bug in while loop
					AddToken(token);
				}
				else
				{
					i = oldi;
				}
			}
		}
		//still, if the character is still not one of the symbols, check
		//whether it is an identifier 
		if (token.TokenType == nilT)
		{
			//if character at sequence[i] is not either digit or alphabets, 
			//or space don't even bother scanning- it must be an error
			if (i<sequence.length() && (isalpha(sequence[i]) || isdigit(sequence[i])))
			{
				//condition: i within bounds and the character is either a character or digit or '_'
				while (i<sequence.length() && (isalpha(sequence[i]) || isdigit(sequence[i]) || sequence[i] == '_'))
				{
					token.TokenType = idT;
					token.TokenName += sequence[i];
					i++;
				}
				if (i<sequence.length()) //if i is within bounds of the string
					if (sequence[i] != ' '/* && !isalpha(sequence[i])
										  && !isdigit(sequence[i])*/)
						i--;
				if (token.TokenType != nilT)
					AddToken(token);
			}
		}
		//still, if the character is not an identifier, an error has occured
		if (token.TokenType == nilT)
		{
			token.TokenType = errorT;
			AddToken(token);
		}

		if ((i+1) == sequence.length())
		{
			token.TokenName = '$';
			token.TokenType = endlineT;
			AddToken(token);

		}
	}
}

void CLexicalAnalyzer::GetAllToken()
{
	std::ostream_iterator<CToken> out_it(std::cout);

	std::copy( cbegin(), cend(), out_it);
}

std::ostream& operator<<(std::ostream& os, const CToken& obj)
{
	os << " " << obj.getTokenName() << " " << EnumTypes[obj.getTokenType()] << " " << obj.TokenValue <<'\n';
	return os;
}

void CLexicalAnalyzer::AddToken(CToken token)
{
	TokenSequence.emplace_back(token);
}

bool CLexicalAnalyzer::IsSequenceEmpty()
{
	return TokenSequence.empty();
}

void CLexicalAnalyzer::ClearAllTokens()
{
	while (!TokenSequence.empty())
		TokenSequence.clear();
}

void CLexicalAnalyzer::ClearToken(CToken a) {
	while (!TokenSequence.empty())
		TokenSequence.remove(a);
		
}
void CLexicalAnalyzer::PreprocessingID() {

	for (auto itToken = begin(); itToken != end(); ++itToken) {

		if (itToken->TokenType == 1)
		{
			auto idV = find(IDbegin(), IDend(), itToken->TokenName);

			CToken n;
			n.TokenName = itToken->TokenName;
			n.TokenType = itToken->TokenType;

			if (idV != IDValue.cend())	//found in IDValueTable
			{
				if (itToken->TokenType == 3 && itToken->TokenName == "=") {
					++itToken;	//go to next
					if (itToken->TokenType == 5 || itToken->TokenType == 6 || itToken->TokenType == 7) {
						idV->TokenValue = itToken->TokenValue;
						idV->TokenValueType = itToken->TokenValueType;
					}
				}
			}
			else          //not found
			{
				itToken++;	//go to next item after identifer
				if (itToken->TokenType == 3 && itToken->TokenName == "=") {
					++itToken;	//go to next
					if (itToken->TokenType == 5 || itToken->TokenType == 6 || itToken->TokenType == 7) {
						n.TokenValue = itToken->TokenName;	//assign Value of identifer to identifer TokenValue (a)
						n.TokenValueType = itToken->TokenType;	//assign ValueType to TokenValueType
					}
				}

				IDValue.emplace_back(n);
			}
		}
	}
}

/*
Take #define store as keyword and remove
Then find all versions of defineName and replace with defineValue in TokenSequence

***Could run into a problem, when I replace value with define name, it's looking for a type and I'll keep it an id but I have decimal, int, and string
	Not sure what to do with that.  Sounds like a pain in my ass.  I have a feeling that will come back to bite me in my ass, making another seperate pain.
*/
void CLexicalAnalyzer::PreprocessingDefine()
{
	//Look for PreProcess Types
	//preprocess 4
	list<string> foundDefine;	//holds all #define found in TokenSequence

	auto itFindDefineTS = begin();

	while (itFindDefineTS != end()) {
		itFindDefineTS = find_if(itFindDefineTS, end(), [](CToken &n) {
			
			return (n.TokenType == 4 && (n.TokenName.find("#define") != std::string::npos));
		});

		if (itFindDefineTS != end()) {
			foundDefine.emplace_back(itFindDefineTS->TokenName);
			++itFindDefineTS;
		}
	}

	remove_if(begin(), end(), [](CToken &n)
	{
		return (n.TokenType == 4 && (n.TokenName.find("#define") != std::string::npos));
	});

	std::for_each(foundDefine.begin(), foundDefine.end(), [&](string &s) {

		string defn(s);
		string define("#define ");

		std::size_t found = defn.find("#define ");	//find first space, which is after #define

		if (found != std::string::npos && ((found + 1) < defn.length())) 
			defn.erase(found, define.length());	//erase #define_ from string left with NAME 0 
		else
			throw std::invalid_argument("STRING FORMATTING ERROR, 3 parts to #define, #define NAME 0");

		int pos = defn.find_first_of(' ');		//a space will seperate NAME VALUE
		string value = defn.substr(pos + 1), name = defn.substr(0, pos);	//split into name and value strings

		//find TokenSequence in KeywordTable
		auto itFindKT = std::find(KTbegin(), KTend(), name);		

		if (itFindKT != KeywordTable.end())	//found
		{
			//update value?
		}
		else        //not found
		{
			CSymbol c;
			c.SymbolString = name;		//copy tokenname
			c.TokenType = 8;	
			KeywordTable.emplace_back(c);
		}

		std::for_each(begin(), end(), [name, value](CToken &n) {

			if (n.TokenName == name)
			{
				n.TokenName = value;
			}
		});
	});
}

void CLexicalAnalyzer::PreprocessingComments()
{
	auto new_end = remove_if(begin(), end(), [](CToken &n)
	{
		return (n.TokenType == 4 && n.TokenName[0] == '/' && n.TokenName[1] == '/');
	});
}
