#include <iostream>
#include <string>

#include "state.h"
#include "tokenFsm.h"

tokenFsm::tokenFsm() {
	// index of state a is 0
	state a;
	a.setTransition('c', 0);
	a.setTransition(' ', 1);
	addState(a);

	// index of state b is 1
	state b;
	b.setTransition(' ', 1);
	b.setTransition('c', 0);
	addState(b);

	// set initial state to state a
	currentStateIndex = 0;
	// initialize temporary string
	temStr = "";
}

void tokenFsm::readCharacter(char c_in) {
	fsm::readCharacter(c_in);

	// if machine is in state 0, store characters
	// if in state 1, push stored characters
	if (currentStateIndex == 1) {
		tokensList.push_back(temStr);
		temStr = "";
	}
	else {
		temStr = temStr + c_in;
	}
}

void tokenFsm::readString(std::string str_in) {
	for (int i=0; i<str_in.length(); i++) {
		readCharacter(str_in[i]);
	}
}

void tokenFsm::printTokens() {
	for (int i=0; i<tokensList.size(); i++) {
		std::cout << tokensList[i] << "\n";
	}
}
