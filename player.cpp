#include<chrono>
#include<iostream>
#include<future>
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
#include "player.h"
#include "gameWorld.h"

// VER 0.7
//
void gamePlayer::set_player_array_spaces(){
	food_array_spaces;
	item_array_spaces;
}
// LOAD DEFAULT PLAYER ARRAYS
void gamePlayer::set_player_new_items(){
	for(int i = 0; i<7; i++){item_array[i] = "-Empty-";}
	item_array_spaces = 7;
}
void gamePlayer::set_player_new_food(){
	for(int i = 0; i<6; i++){food_array[i] = "-Empty-";}
	food_array_spaces=6;
}

// SET PLAYER HEALTH
void gamePlayer::set_player_new_health(){
	player_health=100;
}

// SET NEW PLAYER LIGHT COUNT
void gamePlayer::set_player_lighter_count(){
	lighter_count = 0;
}
// UPDATE PLAYER HEALTH
void gamePlayer::update_player_health(int K){
	player_health=K;
	if(player_health>100){player_health=100;}
}

// GET ITEM SPACES REMAINING
int gamePlayer::get_item_array_spaces(){
	return item_array_spaces;
}

// GET FOOD SPACES REMAINING
int gamePlayer::get_food_array_spaces(){
	return food_array_spaces;
}

// BUILD PLAYER HEALTH BAR
void gamePlayer::build_player_health(std::ostream& os){
	std::string health_prefix = "  Health: ";
	std::string health_string = std::to_string(player_health);
	std::string final_health_string = health_prefix + health_string;
	os<<final_health_string<<std::endl;
}

// BUILD PLAYER ARRAYS
void gamePlayer::build_player_arrays(std::ostream& os){
	// ITEM ARRAY
	os<<"Your Items:"<<std::endl;
	os<<std::string(15,H_STRAIGHT_LINE)<<std::endl;
	for(int i = 0; i<7; i++){
		std::string player_item = item_array[i];
		std::size_t found = player_item.find(":");
		if (found!=std::string::npos){
			std::string show_item = player_item.substr(0,found);
			std::transform(show_item.begin(),show_item.end(),show_item.begin(), ::tolower);
			show_item[0] = toupper(show_item[0]);
			os<<show_item<<std::endl;}
		else{os<<player_item<<std::endl;}
	}
	// FOOD ARRAY
	os<<std::string(15,H_STRAIGHT_LINE)<<std::endl;
	os<<"Your Food:"<<std::endl;
	os<<std::string(15,H_STRAIGHT_LINE)<<std::endl;
	for(int i = 0; i<6; i++){
		std::string player_food = food_array[i];
		std::size_t found = player_food.find(":");
		if (found!=std::string::npos){
			std::string show_food = player_food.substr(0,found);
			std::transform(show_food.begin(),show_food.end(),show_food.begin(), ::tolower);
			show_food[0] = toupper(show_food[0]);		
			os<<show_food<<std::endl;}
		else{os<<player_food<<std::endl;}
	}
}

// ASSIGN ITEM TO THE CORRECT INVENTORY
void gamePlayer::add_item_to_player_array(std::string item_parse){
	int i = 6 - food_array_spaces;
	int j = 7 - item_array_spaces;
	std::string check_type = item_parse.substr(item_parse.find(":") + 1);
	if(check_type == "FOO"){food_array[i]=item_parse;food_array_spaces--;} // IS FOOD
	else{item_array[j]=item_parse;item_array_spaces --;}
}

// PROCESS USE COMMAND
int gamePlayer::process_use_command(std::string item_check){
	bool flag = false,flag2 = false;
	std::string item_array_line;
	std::string food_array_line;
	std::string for_array_comparison;
	std::transform(item_check.begin(),item_check.end(),item_check.begin(), ::toupper);
	
	for(int i = 0; i<7; i++){
		item_array_line = item_array[i];
		for_array_comparison = item_array_line.substr(0,item_array_line.find(":"));
		if(for_array_comparison == item_check){item_in_hand = item_array[i];return 1;}
		else{flag=true;}}
	if (flag==true){
		for(int i = 0; i<6; i++){food_array_line = food_array[i];
			for_array_comparison = food_array_line.substr(0,food_array_line.find(":"));
			if(for_array_comparison == item_check){return 2;}
			else{flag2=true;}}		
	}
	if(flag2==true){if(item_check == "LATCH" || item_check == "BUTTON" || item_check == "LADDER" || item_check == "STAIRS" || item_check == "PIANO" || item_check == "DRAIN PIPE"){return 3;}}
return 0;
}

// PROCESS EAT COMMAND
int gamePlayer::process_eat_command(std::string item_check){
	bool flag = false;
	std::string item_array_line;
	std::string food_array_line;
	std::string for_array_comparison;
	std::transform(item_check.begin(),item_check.end(),item_check.begin(), ::toupper);
	
	for(int i = 0; i<6; i++){
		food_array_line = food_array[i];
		for_array_comparison = food_array_line.substr(0,food_array_line.find(":"));
		if(for_array_comparison == item_check){item_in_hand = food_array[i];return 1;}
		else{flag=true;}}
	if (flag==true){for(int i = 0; i<7; i++){item_array_line = item_array[i];
			for_array_comparison = item_array_line.substr(0,item_array_line.find(":"));
			if(for_array_comparison == item_check){return 2;}}
	}		
return 0;
}
// 
// GET ITEM IN HAND
std::string gamePlayer::get_item_in_hand(){
	return item_in_hand;
}
// 
// POP ITEM OUT OF ARRAY
void gamePlayer::pop_item(std::string item_to_remove){
	std::string out_buffer;
	int i = 0;

	if(item_to_remove == "LIGHTER:P12"){lighter_count = lighter_count +1;}
	if(item_to_remove != "LIGHTER:P12"||(item_to_remove == "LIGHTER:P12" && lighter_count ==4)){
		while(out_buffer != item_to_remove){
			out_buffer = item_array[i];
			if(out_buffer != item_to_remove){
				i++;}}
		if(i != 6){
			while(i<6){item_array[i]=item_array[i+1];i++;}
			item_array[6] = "-Empty-";}
		else{item_array[i] = "-Empty-";}
		item_array_spaces = item_array_spaces + 1;
	}
	
}

// POP FOOD OUT OF ARRAY
void gamePlayer::pop_food(std::string item_to_remove){
	std::string out_buffer;
	int i = 0;
	while(out_buffer != item_to_remove){
		out_buffer = food_array[i];
		if(out_buffer != item_to_remove){
			i++;}}
	if(i != 5){
		while(i<5){food_array[i]=food_array[i+1];i++;}
			food_array[5] = "-Empty-";}
	else{food_array[i] = "-Empty-";}
	food_array_spaces = food_array_spaces + 1;
}
// EAT AN ITEM
int gamePlayer::eat_item(std::string eat_me, int K){

	std::transform(eat_me.begin(),eat_me.end(),eat_me.begin(),::toupper);
	if(eat_me == "APPLE"){K=K+10;}
	if(eat_me == "BANANA"){K=K+15;}
	if(eat_me == "CRISPS"){K=K+10;}
	if(eat_me == "CARROT"){K=K+20;}
	if(eat_me == "TURNIP"){K=K+5;}
	return K;

}

// SAVE GAME 
void gamePlayer::save_player(std::string file_name){
	int c=0;
	std::ofstream temp_file("c:/ANATB/save-"+file_name+".txt", std::ios::app);
	while(c<7){temp_file<<item_array[c]<<std::endl;c++;}
	c=0;
	while(c<6){temp_file<<food_array[c]<<std::endl;c++;}
	temp_file<<player_health<<std::endl;
	temp_file<<food_array_spaces<<std::endl;
	temp_file<<item_array_spaces<<std::endl;
	temp_file<<lighter_count<<std::endl;
	temp_file<<"<--EOF PLAYER-->"<<std::endl;
}

//
// LOAD FROM FILE
int gamePlayer::load_player_saved_game(std::string file_name){
	int load_counter = 0,j=0,k=0,ret_val=0,left_char = 0;
	std::string array_coords,line_right,line_right_no_tild,bool_string,text_file_line;
	std::fstream fstream_text_file_name("c:\\ANATB\\"+file_name);
	if(!fstream_text_file_name){

		system("CLS");
		std::cout<<file_name;	
		std::cout<<"STARTING NEW GAME!"<<std::endl;
		Sleep(5000);
	}
	else{
		if (fstream_text_file_name.is_open()){
			while(getline(fstream_text_file_name,text_file_line)){
									
				if(load_counter>=756&& load_counter<=762){ // ITEM ARRAY
					item_array[j]=text_file_line;j++;		
				}
				else if(load_counter>=763&& load_counter<=768){ // FOOD ARRAY
					food_array[k]=text_file_line;k++;
				}					
				else if(load_counter==769){	// HEALTH
					player_health=std::stoi(text_file_line);		
					ret_val = player_health;
				}
				else if(load_counter==770){	// FOOD SPACE
					food_array_spaces=std::stoi(text_file_line);
				}
				else if(load_counter==771){	//ITEM SPACE
					item_array_spaces=std::stoi(text_file_line);
				}
				else if(load_counter==772){	//LIGHTER COUNT
					lighter_count=std::stoi( text_file_line );
				}
				else if(load_counter==773){
					if(text_file_line=="<--EOF PLAYER-->"){
						std::cout<<"PLAYER FILE FOUND"<<std::endl;
					//	system("PAUSE");
						break;
					}
					else{
						std::cout<<"PLAYER FILE NOT FOUND"<<std::endl;
					//	system("PAUSE");
						break;
					}
				}	
				load_counter++;
				
			}//EOF WHILE F-STREAM
			std::cout<<"Textfile loaded OK"<<std::endl;
			fstream_text_file_name.close();
		}
	}
	return ret_val;
}