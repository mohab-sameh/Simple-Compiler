#ifndef STATE
#define STATE

#include <map>

class state {
	public:

	// a dictionary which maps characters to states index
	std::map<char, int> transitions;

	// sets transitions of states,
	// so that when it reads character c, it returns state index i
	// note that i returns an encoding as well
	void setTransition(char c, int i);

	// state executes reading a character
	int readCharacter(char c);
};

#endif
