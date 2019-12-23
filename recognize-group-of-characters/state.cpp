#include "state.h"

void state::setTransition(char c, int i) {
	transitions[c] = i;
}

int state::readCharacter(char c) {
	return transitions[c];
}
