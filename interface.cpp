#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<algorithm>
#include"windows.h"
//
#include "interface.h"
#include "gameWorld.h"
/*
//
// BUILD GAME INTERFACE
void gameWorld::build_game_interface(std::ostream& os){	
	std::string response_prefix = " RESPONSE: ";
	std::string complete_response = response_prefix + response_string;
	os<<complete_response<<std::endl;
	os<<std::string(65,H_STRAIGHT_LINE)<<std::string(1,TOP_T)<<std::string(6,H_STRAIGHT_LINE)<<">MAP<"<<std::string(6,H_STRAIGHT_LINE)<<std::endl;
	os<<std::setw(15)<<"1: GO NORTH"<< std::setw(15) <<"2: GO SOUTH"<< std::setw(15)<<"3: GO WEST"<<std::setw(15)<<"4: GO EAST"<<std::setw(6)<<std::endl;
	os<<std::setw(66)<<std::endl;
	os<<std::setw(13)<<"5: PICKUP"<< std::setw(12)<<"6: USE"<< std::setw(17)<<"7: PUSH"<<std::setw(15)<<"8: PULL"<<std::setw(9)<<std::endl;
	os<<std::setw(66)<<std::endl;
	os<<std::setw(14)<<"9: INSPECT"<< std::setw(12) <<"10: EAT"<< std::setw(19)<<"11: ATTACK"<<std::setw(13)<<"12: EXIT"<<std::setw(8)<<std::endl;
}
*/
//
// BUILD MINI MAP
void gameInterface::build_mini_map(std::ostream& os){/*RETAINED FOR TEMPLATE REAONS */} 
