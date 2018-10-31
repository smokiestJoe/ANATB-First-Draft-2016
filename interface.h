#include<iostream>
#include"gameWorld.h"
#ifndef INTERFACE_H_
#define INTERFACE_H_
class gameInterface: public gameWorld{

private:

public:
	void build_game_interface(std::ostream&);
	void build_mini_map(std::ostream&);
};
#endif