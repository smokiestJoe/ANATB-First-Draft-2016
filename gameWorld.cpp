// GAME WORLD CLASS
// GOVERNS ALL ITEMS BELONGING TO THE WORLD
// J.Rose
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include"windows.h"
#include<direct.h>
//




//
#include "gameWorld.h"

// VER 0.7
// CONSTRUCTOR
gameWorld::gameWorld(){std::cout<<"CONSTRUCTOR"<<std::endl;}

// LOAD TEXT FILES
void gameWorld::load_new_game_text_files(){
	// 
	int array_load_counter = 0;
	int left_char = 0;
	std::string file_array[7]={"ng-room-names.txt", "ng-room-descriptions.txt","ng-door-status.txt","ng-room-items.txt","ng-room-interactions.txt", "ng-mini-map.txt", "ng-solo-instance.txt"};
	std::string file_name;
	std::string array_buffer;
	std::string text_file_line;
	//
	while(array_load_counter < 7){
		if(array_load_counter == 3 || array_load_counter == 4 ||  array_load_counter == 6){left_char=0;}
		else{left_char=1;}
		file_name = file_array[array_load_counter];
		std::fstream fstream_text_file_name(file_name);
		if(!fstream_text_file_name){std::cout<<"Could not Find Room File"<<std::endl;}
			//
			if (fstream_text_file_name.is_open()){
				while(getline(fstream_text_file_name,text_file_line)){
					// Co-ordinate Conversion
					std::string array_coords = text_file_line.substr (0,3);   // Room co-ordinates
					std::string line_right = text_file_line.substr(text_file_line.find("~") + left_char); // Description
					char X = array_coords[0];
					char Y = array_coords[1];
					char Z = array_coords[2];
					int Xi = X - '0';
					int Yi = Y - '0';
					int Zi = Z - '0';
					
					// Assign Arrays
					if(array_load_counter == 0){room_names[Xi][Yi][Zi]=line_right;visited[Xi][Yi][Zi]=false;}
					if(array_load_counter == 1){room_descriptions[Xi][Yi][Zi]=line_right;}
					if(array_load_counter == 2){door_status[Xi][Yi][Zi]=line_right;}	
					if(array_load_counter == 3){room_items[Xi][Yi][Zi]=line_right;}
					if(array_load_counter == 4){room_instances[Xi][Yi][Zi]=line_right;}
					if(array_load_counter == 5){
						if(line_right=="CROSS"){mini_map[Xi][Yi][Zi]=206;}
						else if(line_right=="BOTTOM_LEFT"){mini_map[Xi][Yi][Zi]=200;}
						else if(line_right=="BOTTOM_RIGHT"){mini_map[Xi][Yi][Zi]=188;}
						else if(line_right=="BOTTOM_T"){mini_map[Xi][Yi][Zi]=202;}
						else if(line_right=="TOP_LEFT"){mini_map[Xi][Yi][Zi]=201;}
						else if(line_right=="TOP_RIGHT"){mini_map[Xi][Yi][Zi]=187;}
						else if(line_right=="TOP_T"){mini_map[Xi][Yi][Zi]=203;}
						else if(line_right=="LEFT_T"){mini_map[Xi][Yi][Zi]=204;}
						else if(line_right=="RIGHT_T"){mini_map[Xi][Yi][Zi]=185;}
						else if(line_right=="V_STRAIGHT"){mini_map[Xi][Yi][Zi]=186;}
						else if(line_right=="H_STRAIGHT"){mini_map[Xi][Yi][Zi]=205;}
						else if(line_right=="DEAD"){mini_map[Xi][Yi][Zi]=210;}
						else if(line_right=="NULL"){mini_map[Xi][Yi][Zi]=' ';}
					}
					if(array_load_counter == 6){solo_use_items[Xi][Yi][Zi]=line_right;}
				//	std::cout<<line_right<<std::endl;
				}//EOF WHILE F-STREAM
			std::cout<<"Textfile loaded OK"<<std::endl;
			fstream_text_file_name.close();
		}// EOF TEXT FILE OPEN
	// GO NEXT
	array_load_counter++;
	}// EOF WHILE
}

// LOAD GUI GRAPHICS
void gameWorld::load_gui_gfx(){
	 H_STRAIGHT_LINE = 205; V_STRAIGHT_LINE = 186;
	 TOP_LEFT = 201;TOP_T = 203;TOP_RIGHT = 187; 
	 LEFT_T = 204;CROSS = 206;RIGHT_T = 185;
	 BOTTOM_LEFT = 200;BOTTOM_T = 202;BOTTOM_RIGHT = 188; 
}

// SET STARTING ROOM
void gameWorld::set_room_new_game(){X_pos=3;Y_pos=0;Z_pos=0;}

// SET VISITED
void gameWorld::set_room_visited(){
	visited[X_pos][Y_pos][Z_pos]=true;
}

// SET CLEAR
int gameWorld::set_clear(){
	std::string item_clear = room_items[X_pos][Y_pos][Z_pos], interaction_clear = room_instances[X_pos][Y_pos][Z_pos];
	if((item_clear == "~ " && interaction_clear == "~ ")||(item_clear == "~" && interaction_clear == "~")){return 1;}
	else{return 0;}
}
// SET RESPONSE STRING
void gameWorld::set_response_string(std::string new_response){
	if(new_response == "INVALID-RESPONSE"){response_string = "You have entered an Invalid Option. Please Try Again.";}
	else if(new_response == "MOVE"){response_string = "You have moved into a new room.";}
	else if(new_response == "PICKUP"){response_string = "Name the object you wish to pickup.";}
	else if(new_response == "USE"){response_string = "What would you like to use?";}
	else if(new_response == "EAT"){response_string = "What would you like to eat?";}
	else if(new_response == "INSPECT"){response_string = "Inspect what?";}
	else{response_string = new_response;}
}
// SET PUZZLE FLAGS
void gameWorld::set_puzzle_flags(){
	puzzle_one_flag_one=false;puzzle_one_flag_two=false;puzzle_one_flag_three=false;puzzle_one_flag_four=false;puzzle_one_master=false;ladder_flag=false;
	fire_flag=false;flag_gramophone=false;flag_toolkit=false;button_push=false;puzzle_piano_flag_master=false;puzzle_oil_flag_master=false;flag_fuse_done=false;
	piano_count=0;oil_count=0;

}
// BUILD ROOM NAMES
void gameWorld::build_room_name(std::ostream& os){
	std::string room_name = room_names[X_pos][Y_pos][Z_pos];
	std::string room_name_prefix = "Room Name: ";
	std::string room_name_complete = room_name_prefix + room_name;
	os<<room_name_complete<<std::endl;
}
//
// BUILD ROOM DESCRIPTIONS
void gameWorld::build_room_description(std::ostream& os){
	std::string room_description = room_descriptions[X_pos][Y_pos][Z_pos];
	std::string word;
	std::string word_array[200];

	int total_length = room_description.length();
	std::string max_line_array[17];
	std::string new_line = "";
	int new_line_length=0,i=0,j=0,k=0,m=0,n=0,p=0,
		word_count=0,max_lines=18,max_chars_per_line=65, 
		desc_length=room_description.length(),word_length=0,
		delete_me=0,test_length=0;
	bool line_flag = false;

	while(room_description.length() != 0){
		word = room_description.substr(0, room_description.find(" "));		
		word_length = word.length();
		delete_me = word_length+1;
		word_array[i] = word;

		if(delete_me > room_description.length()){
			delete_me = room_description.length();}
		room_description.erase(0,delete_me);
		i++;word_count=i;}

	while(k<word_count){
		std::string get_word = word_array[k];
		test_length = get_word.length();
		new_line_length = new_line.length();
		if(test_length + new_line_length < max_chars_per_line){
			new_line = new_line + get_word+" ";}
		else{k--;max_line_array[m] = new_line; new_line = "";m++;}
		k++;}
		if(k==word_count && new_line!=""){
			max_line_array[m] = new_line;
			new_line = "";
			m++;}
	while(n<m){n++;}
	for(p=0;p<n;p++){os<<max_line_array[p]<<std::endl;}
}
//
// BUILD GAME INTERFACE
void gameWorld::build_game_interface(std::ostream& os){	
	std::string response_prefix = "BARN BOT 2000: ";
	std::string complete_response = response_prefix + response_string;
	os<<complete_response<<std::endl;
	os<<std::string(65,H_STRAIGHT_LINE)<<std::string(1,TOP_T)<<std::string(6,H_STRAIGHT_LINE)<<">MAP<"<<std::string(6,H_STRAIGHT_LINE)<<std::endl;
	os<<std::setw(15)<<"W: GO NORTH"<< std::setw(15) <<"S: GO SOUTH"<< std::setw(15)<<"A: GO WEST"<<std::setw(15)<<"D: GO EAST"<<std::setw(6)<<std::endl;
	os<<std::setw(66)<<std::endl;
	os<<std::setw(13)<<"Q: PICKUP"<< std::setw(12)<<"E: USE"<< std::setw(16)<<"R: EAT"<<std::setw(19)<<"T: INSPECT"<<std::setw(9)<<std::endl;
	os<<std::setw(66)<<std::endl;
	os<<std::setw(11)<<"H: HELP"<< std::setw(15) <<"N: SAVE"<< std::setw(16)<<"M: MENU"<<std::setw(15)<<"P: QUIT"<<std::setw(8)<<std::endl;
}

//
// MOVE PLAYER
std::string gameWorld::move_player(char direction){
	std::string checkDoor=door_status[X_pos][Y_pos][Z_pos];std::string north=checkDoor.substr(0,1);std::string south=checkDoor.substr(1,1);std::string west=checkDoor.substr(2,1);std::string east=checkDoor.substr(3,1);
	std::string move;
	//NORTH
	if((direction == '1' || (direction == 'W' || direction == 'w')) && Y_pos < 4){ 
		if(north == "Y"){move="You moved North.";Y_pos++;visited[X_pos][Y_pos][Z_pos]=true;}
		else if(north == "N"){move="You cannot transverse solid objects.";}
		else if(north == "L"){if(X_pos==0&&Y_pos==0&&Z_pos==0){move="A raging fire blocks your path.";}else{move="The Northern Door is locked";}}
		return move;}
	// SOUTH
	else if((direction == '2'  || (direction == 'S' || direction == 's')) && Y_pos > 0){ 
		if(south == "Y"){move="You moved South";Y_pos--;visited[X_pos][Y_pos][Z_pos]=true;}
		else if(south == "N"){move="You cannot transverse solid objects.";}
		else if(south == "L"){if(X_pos==6&&Y_pos==2&&Z_pos==1){move="It's too dark!";}else{move="The Southern Door is locked";}}
		return move;}
	// WEST
	else if((direction == '3'  || (direction == 'A' || direction == 'a')) && X_pos > 0){ 
		if(west == "Y"){move="You moved West";X_pos--;visited[X_pos][Y_pos][Z_pos]=true;}
		else if(west == "N"){move="You cannot transverse solid objects.";}
		else if(west == "L"){move="The Western Door is locked";}
		return move;}
	// EAST
	else if((direction == '4'  || (direction == 'D' || direction == 'd')) && X_pos < 6){ 
		if(east == "Y"){move="You moved East";X_pos ++;visited[X_pos][Y_pos][Z_pos]=true;}
		else if(east == "N"){move="You cannot transverse solid objects.";}
		else if(east == "L"){move="The Eastern Door is locked";}
		return move;}
	// OUTER EDGE
	else{move="You cannot transverse solid objects.";return move;}
}
//
// VALIDATE OBJECT STRING
std::string gameWorld::validate_pickup_string(int item_space, int food_space ,std::string input_string){
	std::transform(input_string.begin(),input_string.end(),input_string.begin(), ::toupper);

	std::string buffer;std::string item_line;std::string tilda_check;std::string item_member;std::string text_to_change;
	std::string to_player_array;std::string change_room_description;std::string string_to_change_buffer;std::string validation_string;
	std::string validated;std::string check_first;std::string item_string = room_items[X_pos][Y_pos][Z_pos];
	std::size_t input_length;std::size_t found;int validate;

	found = item_string.find(input_string);input_length = input_string.length();
	if (found!=std::string::npos){
		validate=input_length+1;validation_string = item_string.substr(found,validate);validated=validation_string.substr(input_length,1);check_first = item_string.substr(found -1, 1); // CHECK FIRST DIGIT
		if(validated != ":" || check_first != "~"){} // VERIFY THAT MATCH IS ON COMPLETE WORD
		else{
			int start=found;int last=item_string.find('~',+start);
			// CREATE STRINGS
			buffer = item_string.substr(start,last);item_line = buffer.substr(buffer.find(":") +1 );item_member=item_line.substr(0,3);
			// CHECK PLAYER ARRAY FOR TYPE & SPACE
			if((item_member == "FOO" && food_space >= 0) || (item_member != "FOO" && item_space >= 0)){
				string_to_change_buffer = item_line;item_line.erase (item_line.begin()+3, item_line.end());text_to_change=string_to_change_buffer.substr(string_to_change_buffer.find(":") + 1);
				// VALIDATE NEW DESCRIPTION
				tilda_check = text_to_change.back();
				if(tilda_check == "~"){text_to_change = text_to_change.substr(0, text_to_change.size()-1);}
				to_player_array = input_string +":"+item_line;change_room_description = room_descriptions[X_pos][Y_pos][Z_pos];found = change_room_description.find(text_to_change);
				// CHANGE ROOM DESCRIPTION
				if(found!=std::string::npos){
					int start=found;int last=change_room_description.find('.',+start);int buff=last-start;change_room_description.erase(start,buff);room_descriptions[X_pos][Y_pos][Z_pos]=change_room_description;
				}
				// ERASE FROM ROOM
				std::size_t finish = item_string.find('~',+start);item_string.erase (start, finish);room_items[X_pos][Y_pos][Z_pos] = item_string; 			
			}
		}
	}
	//std::cout<<"ROOM ITEMS REMAINING"<<room_items[X_pos][Y_pos][Z_pos]<<std::endl; //FOR DEBUG
	return to_player_array;
}
//
// VALIDATE USE STRING
int gameWorld::process_total_use_command(std::string item_in_hand, std::string interaction){
	// ITEM IN HAND
	//std::cout<<"ITEM IN HAND IS "<<item_in_hand<<std::endl;
	std::size_t found = item_in_hand.find(":", +0);
	int code_start = found + 1;
	int code_end = found + 3;
	std::string check_code = item_in_hand.substr(code_start, code_end); // CODE FOR THE ITEM DOING THE INTERACTING
	std::string item_in_hand_name = item_in_hand.substr(0, found); // ITEM IN HAND DISPLAY NAME
	
	// INTERACTION
	std::string room_interaction = room_instances[X_pos][Y_pos][Z_pos];
	std::transform(interaction.begin(),interaction.end(),interaction.begin(),::toupper);	
	std::size_t match = room_interaction.find(interaction); // LOOK FOR INTERACTION OBJECT
	int interaction_code_start = room_interaction.find(":",+ match);
	std::string interaction_code_string = room_interaction.substr(interaction_code_start+1, 3); 
	//std::cout<<"ROOM INTERACTION STRING IS "<<room_interaction<<std::endl;
	
	// IDENTIFIER
	std::string prefix = check_code.substr(0,1);
	//std::cout<<"PREFIX IS "<<prefix<<std::endl;

	if(match!=std::string::npos){ // IF THERE IS A STRING MATCH
		std::string validate = room_interaction.substr(match-1,1);
		if(validate != "~"){return 0;}
		else{
			if(check_code == interaction_code_string){				
					// PIANO PUZZLE
					if(check_code == "P11"){piano_count = piano_count + 1;}
					if(piano_count== 4){puzzle_piano_flag_master=true;}
					// END PIANO PUZZLE
					int start = match;
					int last = room_interaction.find('~',+start);
					// CREATE STRINGS
					std::string buffer = room_interaction.substr(start,last);
					std::string item_line = buffer.substr(buffer.find(":") +1 );
					std::string item_member = item_line.substr(0,3);
					// CHECK PLAYER ARRAY FOR TYPE & SPACE
					std::string string_to_change_buffer = item_line;
					item_line.erase (item_line.begin()+3, item_line.end()); 
					std::string text_to_change = string_to_change_buffer.substr(string_to_change_buffer.find(":") + 1);
					//std::cout<<"TEXT TO CHANGE "<<text_to_change<<std::endl;
					std::string tilda_check;
					// VALIDATE NEW DESCRIPTION
					tilda_check = text_to_change.back();
					if(tilda_check == "~"){	
						text_to_change = text_to_change.substr(0, text_to_change.size()-1);
						//std::cout<<"TEXT TO CHANGE "<<text_to_change<<std::endl;
					}
					std::string  change_room_description = room_descriptions[X_pos][Y_pos][Z_pos]; 
					found = change_room_description.find(text_to_change);
				
				if(interaction!="PIANO"||(interaction == "PIANO" && piano_count==4)){	
					// CHANGE ROOM DESCRIPTION
					if(found!=std::string::npos){
						int start = found;
						int last = change_room_description.find('.',+start);
						int buff = last - start;
						change_room_description.erase(start,buff);   
						room_descriptions[X_pos][Y_pos][Z_pos] = change_room_description;
					}
					if(interaction != "PIANO"){
						// ERASE FROM ROOM
						std::size_t finish = room_interaction.find('~',+start);
						room_interaction.erase (start, finish);
						room_instances[X_pos][Y_pos][Z_pos] = room_interaction; 
					}
					//
				}// END PIANO CLAUSE
				// FOR DOORS
				if(prefix == "D" || prefix == "F"){
					if(prefix == "F"){
						fire_flag = true;
					}
					int unlock_other_side_x;
					int unlock_other_side_y;
					std::string unlock_door;
					std::string unlock_me;
	
						// SPECIFIC CODE FOR DOOR UNLOCKING
					
							//response_string = "OPENS A DOOR";
							std::string unlock_door_string = door_status[X_pos][Y_pos][Z_pos];
							std::string northern_door = unlock_door_string.substr(0,1);
							std::string southern_door = unlock_door_string.substr(1,1);
							std::string western_door = unlock_door_string.substr(2,1);
							std::string eastern_door = unlock_door_string.substr(3,1);
							std::cout<<northern_door<<southern_door<<western_door<<eastern_door<<std::endl;

							if(northern_door == "L"){
								// NOT TESTED
								unlock_other_side_y = Y_pos + 1;
								unlock_door = door_status[X_pos][unlock_other_side_y][Z_pos];
								unlock_me = unlock_door.substr(1,1);
								unlock_me = "Y";
								unlock_door[1] = unlock_me[0];
								door_status[X_pos][unlock_other_side_y][Z_pos] = unlock_door;
								// UNLOCK ROOM DOOR
								unlock_door = door_status[X_pos][Y_pos][Z_pos];
								unlock_me = unlock_door.substr(0,1);
								unlock_me = "Y";
								unlock_door[0] = unlock_me[0];
								door_status[X_pos][Y_pos][Z_pos] = unlock_door;
							}
							else if(southern_door =="L"){					
								// NOT TESTED
								unlock_other_side_y = Y_pos - 1;
								unlock_door = door_status[X_pos][unlock_other_side_y][Z_pos];
								unlock_me = unlock_door.substr(0,1);
								unlock_me = "Y";
								unlock_door[0] = unlock_me[0];
								door_status[X_pos][unlock_other_side_y][Z_pos] = unlock_door;
								// UNLOCK ROOM DOOR
								unlock_door = door_status[X_pos][Y_pos][Z_pos];
								unlock_me = unlock_door.substr(0,1);
								unlock_me = "Y";
								unlock_door[1] = unlock_me[0];
								door_status[X_pos][Y_pos][Z_pos] = unlock_door;
							}
							else if(western_door == "L"){
								// UNLOCK OTHER SIDE
								unlock_other_side_x = X_pos - 1;
								unlock_door = door_status[unlock_other_side_x][Y_pos][Z_pos];
								unlock_me = unlock_door.substr(3,1);
								unlock_me = "Y";
								unlock_door[3] = unlock_me[0];
								door_status[unlock_other_side_x][Y_pos][Z_pos] = unlock_door;
								// UNLOCK ROOM DOOR
								unlock_door = door_status[X_pos][Y_pos][Z_pos];
								unlock_me = unlock_door.substr(2,1);
								unlock_me = "Y";
								unlock_door[2] = unlock_me[0];
								door_status[X_pos][Y_pos][Z_pos] = unlock_door;
							}
							else if(eastern_door == "L"){
								// UNLOCK OTHER SIDE
								unlock_other_side_x = X_pos + 1;
								unlock_door = door_status[unlock_other_side_x][Y_pos][Z_pos];
								unlock_me = unlock_door.substr(2,1);
								unlock_me = "Y";
								unlock_door[2] = unlock_me[0];
								door_status[unlock_other_side_x][Y_pos][Z_pos] = unlock_door;
								// UNLOCK ROOM DOOR
								unlock_door = door_status[X_pos][Y_pos][Z_pos];
								unlock_me = unlock_door.substr(3,1);
								unlock_me = "Y";
								unlock_door[3] = unlock_me[0];
								door_status[X_pos][Y_pos][Z_pos] = unlock_door;				
							}
					
							
				}//PREFIX - DOORS AND FIRE
				else if(prefix == "P"){
	
					// START PUZZLE ONE
					if(check_code == "PO1"){puzzle_one_flag_one=true;}
					if(check_code == "PO2"){puzzle_one_flag_two=true;}
					if(check_code == "PO3"){puzzle_one_flag_three=true;}
					if(check_code == "PO4"){puzzle_one_flag_four=true;}
					if(puzzle_one_flag_one==true&&puzzle_one_flag_two==true&&puzzle_one_flag_three==true&&puzzle_one_flag_four==true){puzzle_one_master=true;}
					// END PUZZLE ONE	

					// OIL LAMP P:12
					if(check_code == "P12"){oil_count = oil_count + 1;}
					if(oil_count== 4){door_status[6][2][1]="YYYN";door_status[6][1][1]="YNNN";}
					if(check_code =="P21"){flag_toolkit=true;door_status[0][3][2]="NYNY";door_status[0][2][2]="YNNN";}
					if(check_code =="P2O"){flag_gramophone=true;door_status[1][3][2]="NYYY";door_status[1][2][2]="YNNN";}
		
				}
				else if(prefix == "C"){
					if(check_code == "COR"){flag_fuse_done=true;door_status[6][1][0]="YYNN";door_status[6][0][0]="YNYN";}
				}
				return 1;
			}// INTERACTION STRING
			
			else if(check_code != interaction_code_string){return 0;}			
		}// ELSE VALIDATE

	}// END IF MATCH
	return 0;
}
// SOLO STRING
int gameWorld::do_solo_use(std::string solo_use_string){
	std::string check_line;check_line=solo_use_items[X_pos][Y_pos][Z_pos];
	std::string description_line; description_line = room_descriptions[X_pos][Y_pos][Z_pos];

	std::string unlock_me;
	std::string top_lock ;
	std::string bottom_lock;

	std::string buffer;
	std::string buffer2;
	int get_length=0,last=0;


	int c = check_line.find(solo_use_string);
	if(c > 0){
		if(solo_use_string == "LATCH"){
			if(X_pos==1&&Y_pos==4&&Z_pos==0||X_pos==2&&Y_pos==2&&Z_pos==1){ // DOWN TO UP
				top_lock = door_status[X_pos][Y_pos][Z_pos];bottom_lock = door_status[X_pos][Y_pos-1][Z_pos];unlock_me="Y";top_lock[1]=unlock_me[0];	
				bottom_lock[0]=unlock_me[0];door_status[X_pos][Y_pos][Z_pos]=top_lock;door_status[X_pos][Y_pos-1][Z_pos]=bottom_lock;
				get_length=solo_use_string.length();check_line.erase(c,get_length);solo_use_items[X_pos][Y_pos][Z_pos]=check_line;}

			else if(X_pos==0&&Y_pos==2&&Z_pos==0||X_pos==4&&Y_pos==2&&Z_pos==0){ // LEFT TO RIGHT
				top_lock = door_status[X_pos][Y_pos][Z_pos];bottom_lock = door_status[X_pos+1][Y_pos][Z_pos];unlock_me="Y";top_lock[3]=unlock_me[0];
				bottom_lock[2]=unlock_me[0];door_status[X_pos][Y_pos][Z_pos]=top_lock;door_status[X_pos+1][Y_pos][Z_pos]=bottom_lock;
				get_length=solo_use_string.length();check_line.erase(c,get_length);solo_use_items[X_pos][Y_pos][Z_pos]=check_line;}

			else if(X_pos==5&&Y_pos==1&&Z_pos==0){// RIGHT TO LEFT
				top_lock = door_status[X_pos][Y_pos][Z_pos];bottom_lock = door_status[X_pos-1][Y_pos][Z_pos];unlock_me="Y";top_lock[2]=unlock_me[0];
				bottom_lock[3]=unlock_me[0];door_status[X_pos][Y_pos][Z_pos]=top_lock;door_status[X_pos-1][Y_pos][Z_pos]=bottom_lock;
				get_length=solo_use_string.length();check_line.erase(c,get_length);
				solo_use_items[X_pos][Y_pos][Z_pos]=check_line;}

			std::string to_remove=", which is latched shut";
			int rem_lngth = to_remove.length();
			int rem_start = description_line.find(to_remove);

			if(rem_start >0){
				description_line.erase(rem_start, rem_lngth);
				room_descriptions[X_pos][Y_pos][Z_pos] = description_line;
			}
			return 1;
		} // END LATCH

		else if(solo_use_string == "BUTTON"){
			if(X_pos==0&&Y_pos==2&&Z_pos==0){
				buffer=room_instances[X_pos][Y_pos][Z_pos];
				if(puzzle_one_master==true){
					last =buffer.find("~",+c);
					buffer.erase(c,last);
					room_instances[X_pos][Y_pos][Z_pos]=buffer;
					ladder_flag = true;
					solo_use_items[X_pos][Y_pos][Z_pos]=solo_use_items[X_pos][Y_pos][Z_pos]+"~LADDER";
					puzzle_one_master = false;
					button_push = true;
					room_descriptions[X_pos][Y_pos][Z_pos] ="A room that appears to hold a secret entrance to the upper level. The walls, ceiling and floor are all a sparse white. Nothing breaks the decor with the exception of a button that sits on the southern wall and the ladder that ascends into the ceiling, though the button now seems inactive. Apart from the door in the northern wall, the only other exit is up the ladder or the door to the east. Apart from staring at the sparsity of the room and attempting to identify different shades of white, so far at which you have been unsuccessful, there is little to do except move on. What a strange room indeed, you think to yourself.";		
					return 2;
				}
				else{return 3;}
			}
		}// END BUTTON

		else if(solo_use_string == "LADDER"){
			if(X_pos==0&&Y_pos==2&&Z_pos==0){
				if(ladder_flag == true){Z_pos = Z_pos+1;return 4;}
				else{return 0;}}
			else if(X_pos==0&&Y_pos==2&&Z_pos==1){Z_pos = Z_pos-1;return 4;}
			else{return 0;}
		}// END LADDER

		else if(solo_use_string == "STAIRS"){
			// MAIN
			if(X_pos==6&&Y_pos==3&&Z_pos==0){Z_pos=Z_pos+1;return 4;}
			else if(X_pos==6&&Y_pos==3&&Z_pos==1){Z_pos=Z_pos-1;return 4;}
			// SECRET
			else if(X_pos==3&&Y_pos==3&&Z_pos==1){Z_pos=Z_pos+1;return 4;}
			else if(X_pos==3&&Y_pos==3&&Z_pos==2){Z_pos=Z_pos-1;return 4;}
			else{return 0;}
		}// END STAIRS

		// PIANO
		else if(solo_use_string == "PIANO"){
			if(piano_count != 4){return 5;}
			else{door_status[3][2][1] = "YYNY";door_status[3][3][1] = "NYNN";
			room_instances[5][2][0]="~";return 6;}
		}// END PIANO
		
		else if(solo_use_string == "DRAIN PIPE"){Z_pos = Z_pos-2;return 1;}// END DRAIN PIPE
	}// END FOUND
	else{return 0;}
}

// 
std::string gameWorld::process_inspection_comamnd(std::string inspect){
	std::transform(inspect.begin(),inspect.end(),inspect.begin(), ::toupper);
	std::string inspect_response;
	
	if(inspect == "LOCKED DOOR"){
		if(X_pos==2&&Y_pos==1&&Z_pos==0){inspect_response = "It looks like it fits a standard key.";}	
		else if(X_pos==1&&Y_pos==1&&Z_pos==0){inspect_response = "The lock is made of Brass.";}
		else if(X_pos==2&&Y_pos==3&&Z_pos==0){inspect_response = "The lock is embossed with red jewels";}
		else if(X_pos==6&&Y_pos==1&&Z_pos==0){inspect_response = "The door requires power to open.";}
		else if(X_pos==4&&Y_pos==1&&Z_pos==0){inspect_response = "The lock is made of solid gold.";}
		else if(X_pos==1&&Y_pos==2&&Z_pos==1){inspect_response = "The keyhole looks very small.";}
		else if(X_pos==2&&Y_pos==3&&Z_pos==1){inspect_response = "This door is unlocked by using the Card Reader.";}
		else if(X_pos==3&&Y_pos==2&&Z_pos==1){inspect_response = "A musical note has been painted on to the door.";}
		else if(X_pos==4&&Y_pos==2&&Z_pos==1){inspect_response = "The sign on the door says \"Earl's Room\".";}
		else if(X_pos==5&&Y_pos==2&&Z_pos==1){inspect_response = "The lock is old and ornate.";}
		else if(X_pos==0&&Y_pos==3&&Z_pos==2){inspect_response = "No visible lock, could be locked by a mechanism.";}
		else if(X_pos==1&&Y_pos==3&&Z_pos==2){inspect_response = "The door appears to be jammed in its frame.";}
		else if(X_pos==4&&Y_pos==2&&Z_pos==2){inspect_response = "The door is locked by with a key pad.";}
	}

	else if(inspect == "CIRCUIT BREAKER"){
		if(X_pos==0&&Y_pos==0&&Z_pos==0){
			if(puzzle_one_flag_four == true){inspect_response = "The power has been restored.";}
			else{inspect_response = "Looks like it is missing some wiring.";}}
	}

	else if(inspect == "FUSE BOX"){
		if(X_pos==5&&Y_pos==3&&Z_pos==0){
			if(flag_fuse_done == true){inspect_response = "The power to the south eastern door has been restored";}
			else{inspect_response = "Looks like it is missing a power cable";}}
	}

	else if(inspect == "FIRE"){
		if(X_pos==0&&Y_pos==0&&Z_pos==0){
			if(fire_flag == true){inspect_response = "The fire is out now.";}
			else{inspect_response = "It's hotter than the Sun's oven!";}}
	}

	else if(inspect == "PIANO"){
		if(X_pos==5&&Y_pos==2&&Z_pos==0){
			if(piano_count < 4){inspect_response ="The piano is unplayable in its current state.";}
			else{inspect_response ="I hope it sounds as good as it looks.";}}
	}

	else if(inspect == "BEN AFFLECK"){if(X_pos==2&&Y_pos==2&&Z_pos==1){inspect_response ="Oh Ben, what has she done? Why are you so sticky?";}}
	else if(inspect == "MATT DAMON"){if(X_pos==2&&Y_pos==2&&Z_pos==1){inspect_response ="I wonder where his trousers went.";}}
	else if(inspect == "LEO DICAPRIO"){if(X_pos==2&&Y_pos==2&&Z_pos==1){inspect_response ="If only I could loosen his chains, poor guy.";}}

	else if(inspect == "BUTTON"){
		if(X_pos==0&&Y_pos==2&&Z_pos==0){
			if(puzzle_one_master == false && button_push == false){
				inspect_response ="The button looks non-functional.";}
			if(puzzle_one_master == true){
				inspect_response ="Looks like it's powered and actvates something.";}
			else if(puzzle_one_master == false && button_push == true){
				inspect_response ="It's done its job, it looks deactivated.";}
		}
	}

	else if(inspect == "LADDER"){
		if(X_pos==0&&Y_pos==2&&Z_pos==0){
			if(button_push == true){inspect_response ="It goes up.";}}
		else if(X_pos==0&&Y_pos==2&&Z_pos==1){
			inspect_response ="It goes down.";}
	}

	else if(inspect == "STAIRS"){
		if(X_pos==6&&Y_pos==3&&Z_pos==0  ||  X_pos==6&&Y_pos==3&&Z_pos==1 ){
			if(X_pos==6&&Y_pos==3&&Z_pos==0){inspect_response ="Marvellous craftsmanship, ascending to the upper floor.";}
			else{inspect_response ="Marvellous craftsmanship, descending to the lower floor.";}}

		else if(X_pos==3&&Y_pos==3&&Z_pos==1 || X_pos==3&&Y_pos==3&&Z_pos==2){
			if(X_pos==3&&Y_pos==3&&Z_pos==1){
				inspect_response ="An ascending metal masterpiece.";}
			else{inspect_response ="A descending metal masterpiece.";}}
	}

	else if(inspect == "SHELF"){
		if(X_pos==2&&Y_pos==4&&Z_pos==0){
			if(puzzle_one_flag_one == true){inspect_response ="The collection is adoreable.";}
			else{inspect_response ="The shelf is missing a figurine.";}}
	}

	else if(inspect == "CLOCK"){
		if(X_pos==0&&Y_pos==4&&Z_pos==0){
			if(puzzle_one_flag_two == true){inspect_response ="It is ticking along nicely.";}
			else{inspect_response ="It looks like it is missing some gears.";}}
	}

	else if(inspect == "PHOTO FRAME"){
		if(X_pos==4&&Y_pos==1&&Z_pos==0){
			if(puzzle_one_flag_three == true){inspect_response ="The photograph looks much nicer in a frame.";}
			else{inspect_response ="Someone has removed the photograph";}}
	}

	else if(inspect == "OIL LAMP"){


	}

	else if(inspect == "GRAMOPHONE"){
		if(X_pos==0&&Y_pos==2&&Z_pos==2){
			if(flag_gramophone == true){
				inspect_response ="It's really loud! Funky, but loud.";}
			else{inspect_response ="If only I had a record to play.";}}
	}

	else if(inspect == "TOOLKIT"){
		if(X_pos==2&&Y_pos==2&&Z_pos==2){
			if(flag_toolkit == true){inspect_response ="Looks like it is providing power to something.";}
			else{inspect_response ="It is missing a tool. It looks like it could be a Spanner.";}}
	}

	else if(inspect == "CARD READER"){
		if(X_pos==2&&Y_pos==3&&Z_pos==1){inspect_response ="It looks like it reads Key Cards.";}
	}

	else if(inspect == "KEY PAD"){
		if(X_pos==4&&Y_pos==2&&Z_pos==2){inspect_response ="It works with a Key Code.";}
	}

	else if(inspect == "DRAIN PIPE"){
		if(X_pos==4&&Y_pos==3&&Z_pos==2){inspect_response ="Looks like the safest way down.";}
		else if(X_pos==4&&Y_pos==3&&Z_pos==0){inspect_response ="No way I can climb that.";}
	}
	else{
		inspect_response ="Noting of interest.";
	}

	return inspect_response;

}

//
/// GET
//
int gameWorld::get_x_pos(){return X_pos;}
int gameWorld::get_y_pos(){return Y_pos;}
int gameWorld::get_z_pos(){return Z_pos;}

/******************************************************** LAB TESTING SAVE GAME *******************************************************/
void gameWorld::create_save_dir(){
	_mkdir("c:/ANATB");
}

/*******************************************************/
void gameWorld::save_write(std::string file_name){
	int x_write=0,y_write=0,z_write=0;
	int array_line_counter=0;

	std::string X_string,Y_string,Z_string;

	std::ofstream temp_file("c:/ANATB/save-"+file_name+".txt");


	if(!temp_file){std::cout<<"Could not Find Room File"<<std::endl;}

	// ROOM DESCRIPTIONS
	while(z_write<3){
		while(y_write<5){
			while(x_write<7){	
				X_string = std::to_string(x_write);	Y_string = std::to_string(y_write);Z_string = std::to_string(z_write);
				temp_file<<X_string<<Y_string<<Z_string<<"~"<<room_descriptions[x_write][y_write][z_write]<<std::endl;
				x_write++;array_line_counter++;
			}
			x_write = 0;y_write++;
		}
		x_write=0;y_write=0;z_write++;
	}


	// DOOR STATUS
	x_write=0;y_write=0;z_write=0;
	while(z_write<3){
		while(y_write<5){
			while(x_write<7){		
				X_string = std::to_string(x_write);Y_string = std::to_string(y_write);Z_string = std::to_string(z_write);
				temp_file<<X_string<<Y_string<<Z_string<<"~"<<door_status[x_write][y_write][z_write]<<std::endl;
				x_write++;array_line_counter++;
			}
			x_write=0;y_write++;
		}
		x_write=0;y_write=0;z_write++;
	}
	
	// ROOM INSTANCES
	x_write=0;y_write=0;z_write=0;
	while(z_write<3){
		while(y_write<5){
			while(x_write<7){
				X_string = std::to_string(x_write);Y_string = std::to_string(y_write);Z_string = std::to_string(z_write);
				temp_file<<X_string<<Y_string<<Z_string<<room_instances[x_write][y_write][z_write]<<std::endl;
				x_write++;array_line_counter++;
			}
			x_write=0;y_write++;
		}
		x_write=0;y_write=0;z_write++;
	}


	// ROOM ITEMS
	x_write=0;y_write=0;z_write=0;
	while(z_write<3){
		while(y_write<5){
			while(x_write<7){
				X_string = std::to_string(x_write);Y_string = std::to_string(y_write);Z_string = std::to_string(z_write);
				temp_file<<X_string<<Y_string<<Z_string<<room_items[x_write][y_write][z_write]<<std::endl;
				x_write++;array_line_counter++;
			}
			x_write=0;y_write++;
		}
		x_write=0;y_write=0;z_write++;
	}

	// ROOM SOLO USE
	x_write=0;y_write=0;z_write=0;
	while(z_write<3){
		while(y_write<5){
			while(x_write<7){
				X_string = std::to_string(x_write);Y_string = std::to_string(y_write);Z_string = std::to_string(z_write);
				temp_file<<X_string<<Y_string<<Z_string<<solo_use_items[x_write][y_write][z_write]<<std::endl;
				x_write++;array_line_counter++;
			}

			x_write=0;y_write++;
		}
		x_write=0;y_write=0;z_write++;
	}

	// VISITED
	x_write=0;y_write=0;z_write=0;
	while(z_write<3){
		while(y_write<5){
			while(x_write<7){			
				X_string = std::to_string(x_write);Y_string = std::to_string(y_write);Z_string = std::to_string(z_write);
				temp_file<<X_string<<Y_string<<Z_string<<"~"<<visited[x_write][y_write][z_write]<<std::endl;
				x_write++;array_line_counter++;
			}
			x_write = 0;y_write++;
		}
		x_write=0;y_write=0;z_write++;
	}
	//	std::string count_string = std::to_string(array_line_counter); 106 ROOMS, 105 COUNT

	//	temp_file<<count_string<<std::endl;

	temp_file<<X_pos<<std::endl;
	temp_file<<Y_pos<<std::endl;
	temp_file<<Z_pos<<std::endl;	
	temp_file<<puzzle_one_flag_one<<std::endl;
	temp_file<<puzzle_one_flag_two<<std::endl;
	temp_file<<puzzle_one_flag_three<<std::endl;
	temp_file<<puzzle_one_flag_four<<std::endl;
	temp_file<<puzzle_one_master<<std::endl;
	temp_file<<ladder_flag<<std::endl;
	temp_file<<flag_fuse_done<<std::endl;
	temp_file<<fire_flag<<std::endl;
	temp_file<<flag_gramophone<<std::endl;
	temp_file<<flag_toolkit<<std::endl;
	temp_file<<button_push<<std::endl;
	temp_file<<puzzle_piano_flag_master<<std::endl;
	temp_file<<puzzle_oil_flag_master<<std::endl;
	temp_file<<piano_count<<std::endl;
	temp_file<<oil_count<<std::endl;

	temp_file<<"<--EOF GAMEWORLD-->"<<std::endl;
}

// LOAD SAVED GAME FILES
void gameWorld::load_gw_saved_game_files(std::string file_name){
	int load_counter = 0;
	int left_char = 0;
	std::string text_file_line;
	std::fstream fstream_text_file_name("c:\\ANATB\\"+file_name);
	if(!fstream_text_file_name){
		system("CLS");
		std::cout<<file_name;
		//std::cout<<"CANNOT FIND GAME SAVE!!"<<std::endl;			
		std::cout<<"STARTING NEW GAME!"<<std::endl;
		Sleep(5000);

	}
	else{
		if (fstream_text_file_name.is_open()){
			while(getline(fstream_text_file_name,text_file_line)){
				// Co-ordinate Conversion
				std::string array_coords;
				std::string line_right;
				std::string line_right_no_tild;
				std::string bool_string;
						
				char X, Y, Z;
				int Xi, Yi, Zi;

				bool_string = text_file_line.substr (0,1);   
				if(text_file_line.length()>1&&text_file_line.substr(0,1)!="<"){

					array_coords = text_file_line.substr (0,3);   // Room co-ordinates
					line_right = text_file_line.substr(text_file_line.find("~") + left_char); // Description
					line_right_no_tild = text_file_line.substr(text_file_line.find("~") + 1); // Description

					X = array_coords[0];Y = array_coords[1]; Z = array_coords[2];
					Xi = X - '0'; Yi = Y - '0';Zi = Z - '0';		
				}
				// STRING ARRAY					
				if(load_counter>=0 && load_counter<=104){room_descriptions[Xi][Yi][Zi]=line_right_no_tild;}			
				else if(load_counter>=105 && load_counter<=209){door_status[Xi][Yi][Zi]=line_right_no_tild;} // DOORS						
				else if(load_counter>=210 && load_counter<=314){room_instances[Xi][Yi][Zi]=line_right;} // INSTANCES				
			
				else if(load_counter>=315 && load_counter<=419){room_items[Xi][Yi][Zi]=line_right;} // ITEMS			
				else if(load_counter>=420 && load_counter<=524){solo_use_items[Xi][Yi][Zi]=line_right;} // SOLO USE
		
				// BOOL ARRAY
				if(load_counter>=525 && load_counter<=629){ // VISITED
					if(line_right_no_tild =="0"){visited[Xi][Yi][Zi]=false;}
					else if(line_right_no_tild =="1"){visited[Xi][Yi][Zi]=true;}
					else{system("CLS");std::cout<<"FATAL ERROR"<<std::endl;Sleep(5000);break;exit(1);}
				//	std::cout<<"VISITED: "<<visited[Xi][Yi][Zi]<<std::endl;
					//system("PAUSE");
				}
				// INTEGER
				else if(load_counter==630){X_pos=std::stoi( bool_string );} // X_Pos Loaded
				else if(load_counter==631){Y_pos =std::stoi( bool_string );} //Y_Pos Loaded		
				else if(load_counter==632){Z_pos=std::stoi( bool_string );} // Z_Pos Loaded		

				// BOOL FLAGS
				else if(load_counter==633){
					if(bool_string == "0"){puzzle_one_flag_one=false;}	 // PUZZLE 1 FLAG ONE
					else if(bool_string =="1"){puzzle_one_flag_one=true;}}
				else if(load_counter==634){
					if(bool_string == "0"){puzzle_one_flag_two=false;}	 // PUZZLE 1 FLAG TWO
					else if(bool_string =="1"){puzzle_one_flag_two=true;}}

				else if(load_counter==635){
					if(bool_string == "0"){puzzle_one_flag_three=false;}	 // PUZZLE 1 FLAG THREE
					else if(bool_string =="1"){puzzle_one_flag_three=true;}} 

				else if(load_counter==636){
					if(bool_string == "0"){puzzle_one_flag_four=false;}	 // PUZZLE 1 FLAG FOUR
					else if(bool_string =="1"){puzzle_one_flag_four=true;}}

				else if(load_counter==637){
					if(bool_string == "0"){puzzle_one_master=false;}	 // PUZZLE 1 MASTER
					else if(bool_string =="1"){puzzle_one_master=true;}}		

				else if(load_counter==638){
					if(bool_string == "0"){ladder_flag=false;}	 // LADDER
					else if(bool_string =="1"){ladder_flag=true;}} 

				else if(load_counter==639){	
					if(bool_string == "0"){flag_fuse_done=false;}	 // FUSE
					else if(bool_string =="1"){flag_fuse_done=true;}}

				else if(load_counter==640){
					if(bool_string == "0"){fire_flag=false;}	 // FIRE
					else if(bool_string =="1"){fire_flag=true;}} 

				else if(load_counter==641){
					if(bool_string == "0"){flag_gramophone=false;}	 // GRAMOPHONE	
					else if(bool_string =="1"){flag_gramophone=true;}} 

				else if(load_counter==642){	
					if(bool_string == "0"){flag_toolkit=false;}	 // TOOLKIT
					else if(bool_string =="1"){flag_toolkit=true;}}

				else if(load_counter==643){	
					if(bool_string == "0"){button_push=false;}	 // BUTTON PUSH	
					else if(bool_string =="1"){button_push=true;}} // BUTTON PUSH		

				else if(load_counter==644){
					if(bool_string == "0"){puzzle_piano_flag_master=false;}	 // PIANO MASTER
					else if(bool_string =="1"){puzzle_piano_flag_master=true;}} // PIANO MASTER	

				else if(load_counter==645){
					if(bool_string == "0"){puzzle_oil_flag_master=false;}	 // OIL MASTER
					else if(bool_string =="1"){puzzle_oil_flag_master=true;}} // OIL MASTER			

				// INTEGER COUNTERS
				else if(load_counter==646){piano_count=std::stoi( bool_string );} // INT PIANO COUNT	
				else if(load_counter==647){oil_count=std::stoi( bool_string );} // INT OIL COUNT
				
				else if(load_counter==648){
					if(text_file_line=="<--EOF GAMEWORLD-->"){
						std::cout<<"GAMEWORLD FOUND"<<std::endl;
					//	system("PAUSE");
						break;

					}
					else{
						std::cout<<"GAMEWORLD NOT FOUND"<<std::endl;
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

}

