#include<iostream>
#include"gameWorld.h"
#ifndef COMMANDS_H_
#define COMMANDS_H_
class gameCommands: public gameWorld{

private:
	char command_array[11];

public:
	void load_character_array();

	std::string validate_char_command(char);
	std::string process_pickup();
	std::string process_use();
	std::string process_interaction(std::string, std::string);
	std::string process_eat();
	std::string process_inspection();

	char main_menu_select();	
	char char_command(char);		

	std::string save_game();
};
#endif