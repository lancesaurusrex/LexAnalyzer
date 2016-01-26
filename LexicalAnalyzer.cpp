#include "LexicalAnalyzer.h"



//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
//#endif
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
	"endline"
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
		//else if the character is a newline...
		else if (sequence[i] == '\r' && sequence[i + 1] == '\n')	//bug?  is newline and /r the equiv of one or two characters?
		{
			token.TokenType = endlineT;
			i++;
			AddToken(token);
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
	}
}

void CLexicalAnalyzer::GetAllToken()
{
	std::ostream_iterator<CToken> out_it(std::cout);

	std::copy( cbegin(), cend(), out_it);
}

std::ostream& operator<<(std::ostream& os, const CToken& obj)
{
	os << " " << obj.getTokenName() << " " << EnumTypes[obj.getTokenType()] << '\n';
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

	for (auto itT = begin(); itT != end(); ++itT) {

		if (itT->TokenType == 1)
		{
			auto idV = find(IDbegin(), IDend(), itT->TokenName);
			CToken n;
			n.TokenName = itT->TokenName;
			n.TokenType = itT->TokenType;

			if (idV != IDValue.cend())	//found
			{
				if (itT->TokenType == 3 && itT->TokenName == "=") {
					++itT;	//go to next
					if (itT->TokenType == 5 || itT->TokenType == 6 || itT->TokenType == 7) {
						idV->TokenValue = itT->TokenValue;
						idV->TokenValueType = itT->TokenValueType;
					}
				}
			}
			else          //not found
			{
				itT++;	//go to next item after identifer
				if (itT->TokenType == 3 && itT->TokenName == "=") {
					++itT;	//go to next
					if (itT->TokenType == 5 || itT->TokenType == 6 || itT->TokenType == 7) {
						n.TokenValue = itT->TokenName;	//assign Value of identifer to identifer TokenValue (a)
						n.TokenValueType = itT->TokenType;	//assign ValueType to TokenValueType
					}
				}

				IDValue.emplace_back(n);
				
			}
		}
	}
}

void CLexicalAnalyzer::PreprocessingDefine()
{
	//Look for PreProcess Types
	//preprocess 4
	
			//might have to move this into find id in keywordtable func
			//for (auto it = temp.cbegin(); it != temp.cend(); ++it)
			//{ 
			//	if (*it == "#define"){
			//	
			//		//++it;	//it is #define go to next word;
			//		//vector<CSymbol>::const_iterator itfind;	
			//		//itfind = std::find(KTbegin(), KTend(), *it);
			//		//if (itfind != KeywordTable.cend())	//found in Keyword Table, update value
			//		//{
			//		//	++it;	//go to value
			//		//}
			//	}
			//
			//}

			//if (std::getline(ss, defn, ' ')) //get first word, it has to be #define
			//{	
			//	if (defn == "#define")	//check if #define
			//	{	
			//		while (std::getline(ss, defn, ' '))		//get rest of words
			//		{	
			//			if (!isdigit(stoi(defn))) //if word is not digit store as id
			//			{
			//				//find in keyword table if not found add to TokenSequence
			//				std::find(cbegin(), cend(), defn);
			//				

			//			}	
			//		}
			//	}
			//	else {} //errortype 
			//}

			
			//std::size_t found = n.TokenName.find(defn);	//find #define
			//int i = 0;
			////n.TokenName = "GGGGGG";		
			//
			//if (found != std::string::npos)
			//while (i != n.TokenName.size()) {
			//	defn = " ";		//let it find spaces
			//	
			//	found = n.TokenName.find_first_of(defn);		//find spaces in words
			//	int i = found;		//go ahead one of space
			//	
			//	int prevspace = i;
			//	//trimspace of string
			//	string defn = n.TokenName.substr(prevspace, i);
			//}

	auto itFindDef = find_if(begin(), end(), [&](CToken &n) {

		return (n.TokenType == 4);
	});

	string defn;
	std::stringstream ss(itFindDef->TokenName);
	list<string> temp;
	while (std::getline(ss, defn, ' '))
	{
		temp.push_back(defn);
	}
	defn = "#define";
	auto itdef = find(temp.begin(), temp.end(), defn);

	if (temp.size() == 3) {
		if (itdef != temp.end())
		{
			++itdef;	//go to next iteration identifer
			auto itfind = std::find(KTbegin(), KTend(), *itdef);		//find identifer
			if (itfind != KeywordTable.end())	//found
			{
				//update value
			}
			else        //not found
			{				
					CSymbol c;
					c.SymbolString = *itdef;		//copy tokenname
					c.TokenType = 8;	//might need to change to keyword
					KeywordTable.emplace_back(c);
			}
		}
	}
	else
	{
		throw std::invalid_argument("not enough or too much in temp list");
	}

	
	auto tempit = temp.cbegin();
	std::advance(tempit, 1);
	itFindDef->TokenName = *tempit;
	std::advance(tempit, 1);
	itFindDef->TokenType = 8;
	itFindDef->TokenValue = *tempit;
	itFindDef->TokenValueType = 0;	//not sure what this is tired of doing this
	//add to valuetable
	

	//remove name from TokenSequence didn't work full name didnt match partial
	//remove_if(begin(), end(), [&](CToken &n) {
	//	auto tempit = temp.cbegin();
	//	std::advance(tempit, 1);	//go forward one
	//	return (n.TokenName == *tempit);
	//});
}

void CLexicalAnalyzer::PreprocessingComments()
{
	auto new_end = remove_if(begin(), end(), [](CToken &n)
	{
		return (n.TokenType == 4 && n.TokenName[0] == '/' && n.TokenName[1] == '/');
	});

	//std::for_each(begin(), end(), [this](CToken &n)
	//{
	//	if (n.TokenType == 4 && (!n.TokenName.empty()) && n.TokenName[0] == '/' && n.TokenName[1] == '/')
	//	{
	//		ClearToken(n);
	//	}
	//	return n;
	//});
}
