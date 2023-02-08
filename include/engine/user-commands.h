#ifndef _USER_COMMANDS_H_
#define _USER_COMMANDS_H_

namespace MyCommands	{
	/**
	 * @brief Enumeration of all possible commands passed to the 
	 * takeCommand member function of the Player class 
	*/
	enum Commands	{
		PAUSE,
		EXIT,
		ACCELERATE,
		DONT_ACCELERATE,
		SHOOT,
		DONT_SHOOT
	};
}

#endif