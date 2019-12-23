#ifndef FSM
#define FSM

#include <vector>
#include "state.h"

class fsm {
	public:

	// either an index of next state, or an encoding
	int currentStateIndex;
	int returnEncoding;

	// states of the finite state automata
	std::vector<state> states;

	// add a state to the automata
	void addState(state st_in);

	// reads a character by current state, assigns stateOutput
	virtual void readCharacter(char c_in);
};
#endif
