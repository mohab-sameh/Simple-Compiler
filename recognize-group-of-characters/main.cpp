#include <string>

#include "fsm.h"
#include "state.h"
#include "tokenFsm.h"

int main() {
	// raw code should be read from a file
	std::string rawCode = "cc cc ";

	// instantiate an object from finite automata which tokenizes
	tokenFsm tfa;

	// run the automata on user's raw code
	tfa.readString(rawCode);

	// print automata's obtained list
	tfa.printTokens();

	return 0;
}
