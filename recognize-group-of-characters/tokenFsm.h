#ifndef TOKEN_FSM
#define TOKEN_FSM

#include <string>
#include <vector>
#include "fsm.h"

// an inherited finite automata which
// extends a memory for storing group of characters
class tokenFsm: public fsm {
	public:

	// temporary string to be inserted into tokensList
	std::string temStr;

	// list of tokens to be constructed from raw code
	std::vector<std::string> tokensList;

	// state 0 reads characters
	// state 1 reads spaces
	tokenFsm();

	// if machine is on state 0, it stores characters into temporary string
	// till it reaches a space, the temporary string is inserted into tokensList
	void readCharacter(char c_in);

	// machine reads the whole string by iterating on its characters with readCharacter
	void readString(std::string str_in);

	// print recognized tokens
	void printTokens();
};

#endif
