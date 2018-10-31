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

#include "gameWorld.h"
#include "commands.h"
//
// LOAD DIRECTION ARRAY
void gameCommands::load_character_array(){

	command_array[0] = 'W';
	command_array[1] = 'S';
	command_array[2] = 'A';
	command_array[3] = 'D';
	command_array[4] = 'w';
	command_array[5] = 's';
	command_array[6] = 'a';
	command_array[7] = 'd';
	command_array[8] = 'Q';
	command_array[9] = 'q';
	command_array[10] = 'E';
	command_array[11] = 'e';
	command_array[12] = 'r';
	command_array[13] = 'R';
	command_array[14] = 't';
	command_array[15] = 'T';
	command_array[16] = 'H';
	command_array[17] = 'h';
	command_array[18] = 'N';
	command_array[19] = 'n';
	command_array[20] = 'M';
	command_array[21] = 'm';
	command_array[22] = 'P';
	command_array[23] = 'p';
}
//
// GRAB ALL MENU CHARS
char gameCommands::main_menu_select(){
	char command = _getch();
	return command;
}
char gameCommands::char_command(char state){
	std::cout<<"Enter Your Command: ";
	char command = _getch();
	return command;
}

//
// VALIDATE MENU COMMAND
std::string gameCommands::validate_char_command(char validate){
	bool choice=false;int find;
	for(int i=0; i <= 23; i++){if(validate == command_array[i]){choice = true;find = i;break;}}
	if(choice){
		if(find>=0 && find<=7){return "MOVE";}
		else if(find>=8 && find<=9){return "PICKUP";}
		else if(find>=10 && find<=11){return "USE";}
		else if(find>=12 && find<=13){return "EAT";}
		else if(find>=14 && find<=15){return "INSPECT";}
		else if(find>=16 && find<=17){return "HELP";}
		else if(find>=18 && find<=19){return "SAVE";}
		else if(find>=20 && find<=21){return "MENU";}
		else if(find>=22 && find<=23){return "QUIT";}
	}
	else{return "INVALID-RESPONSE";}
}
//
// GRAB PICKUP OBJECT
std::string gameCommands::process_pickup(){
	std::string pickup_object;std::cout<<"Pickup: ";std::getline(std::cin,pickup_object);
	return pickup_object;
}
//
// GRAB USE OBJECT
std::string gameCommands::process_use(){
	std::string use_object;std::cout<<"Use: ";std::getline(std::cin,use_object);
	return use_object;	
}
//
// GRAB INTERACTION OBJECT
std::string gameCommands::process_interaction(std::string use_object, std::string display_item){
	std::string interaction_object;std::cout<<"Use "+display_item+" with: ";std::getline(std::cin,interaction_object);
	return interaction_object;
}
//
// GRAB USE OBJECT
std::string gameCommands::process_eat(){
	std::string eat_object;std::cout<<"Eat: ";std::getline(std::cin,eat_object);
	return eat_object;	
}
//
// GRAB INSPECT OBJECT
std::string gameCommands::process_inspection(){	
	std::string inspect_object;std::cout<<"Inspect: ";std::getline(std::cin,inspect_object);
	return inspect_object;	
}
//
// SAVE GAME
std::string gameCommands::save_game(){
	std::string save_error = "SAVE_ERROR",file_error = "FILE_ERROR",name_error = "NAME_ERROR";
	std::string save_file_name;std::cout<<"Name your game save: ";std::getline(std::cin,save_file_name);
	
	int file_count = 0;
	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile(L"c:\\ANATB\\*.*",&data);
	
	if( h!=INVALID_HANDLE_VALUE ) {
		do{
			char* nPtr = new char [lstrlen( data.cFileName ) + 1];
			for( int i = 0; i < lstrlen( data.cFileName ); i++ )
				nPtr[i] = char( data.cFileName[i] );
				nPtr[lstrlen( data.cFileName )] = '\0';				
				if(nPtr[0]!='.'){file_count++;}
		} while(FindNextFile(h,&data));
	} 
	else 
		std::cout << "Error: No such folder." << std::endl;
		FindClose(h);

	if(file_count<10){
		if (save_file_name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos || save_file_name==""){
			return save_error;
		}
		else if(save_file_name.length()>10){
			return name_error;
		}
		else{return save_file_name;	}
	}
	else{return file_error;}
}	