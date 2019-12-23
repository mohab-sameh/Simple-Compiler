#include "fsm.h"
#include "state.h"

void fsm::addState(state st_in) {
	states.push_back(st_in);
}

void fsm::readCharacter(char c_in) {
	// read a character by nextState,
	// then assign new next state's index to currentStateIndex
	currentStateIndex = states[currentStateIndex].readCharacter(c_in);

	// if nextStateIndex is negative,
	// then that value is an encoding, not an index of next state
	if (currentStateIndex < 0) {
		returnEncoding = currentStateIndex;
	}
}
