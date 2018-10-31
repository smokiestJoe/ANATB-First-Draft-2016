// SYSTEM LIBRARIES
#include<chrono>
#include<iostream>
#include<future>
#include<string>
#include<sstream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<tchar.h>
#include<cwchar>
#include<strsafe.h>
#include<algorithm>
// PERSONAL LIBRAIRES
#include "gameWorld.h"
#include "player.h"
#include "screenOutput.h"
#include "interface.h"
#include "commands.h"

// INITIALISE SCREEN OUTPUT CLASS
screenOutput newScreenOutput;

char main_menu_select='0', game_menu_select='0';

bool refresh=false,game_engine_flag=true,new_game_flag=true;
int K;

// PROTOTYPES
void timer(){ // PLAYER HEALTH TIMER
	do{
		auto start = std::chrono::high_resolution_clock::now();
		for(int i=0;i<120;++i){std::this_thread::sleep_until(start + (i+1)*std::chrono::seconds(1));}
		K = K - 5;
	}while(K > 0);
	system ("CLS");newScreenOutput.game_over();	new_game_flag = false;	
	main_menu_select = '0';
}


// RESET CURSOR
/** WINDOWS AND LINUX PLATFORMS **/
#ifdef _WIN32
void gotoxy(int x, int y){
  COORD p = { x, y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
#else

/** LINUX **/
#include <unistd.h>
#include <term.h>

void gotoxy(int x, int y){
  int err;
  if (!cur_term)
  if (setupterm(NULL, STDOUT_FILENO, &err) == ERR)
     return;
     putp(tparm(tigetstr("cup"), y, x, 0, 0, 0, 0, 0, 0, 0));
}
#endif 

int main(){
/********************************** MSDN LIBRARY (WINDOWS ONLY) ******************************/
	// MSDN LIBRARY - SET TITLE (WINDOWS)
   TCHAR szOldTitle[MAX_PATH];
   TCHAR szNewTitle[MAX_PATH];
   if( GetConsoleTitle(szOldTitle, MAX_PATH) ){
      StringCchPrintf(szNewTitle, MAX_PATH, TEXT("A Night At The Barn"), szOldTitle);
      if( !SetConsoleTitle(szNewTitle) ){
         _tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
         return 1;
      }
      else{
         _tprintf(TEXT("SetConsoleTitle succeeded.\n"));
      }
   }
   // MSDN LIBRARY - SET FONT SIZE (WINDOWS)
   	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                  
	cfi.dwFontSize.Y = 24;                
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Font Consolas
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
   //
   // MSDN SET CONSOLE SIZE W: 1000, H: 810
	HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect); 
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1000, 750, TRUE);

	// MAXIMISE BOX & DRAG RESIZE DISABLE
	HWND consoleWindow  = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow , GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX)& ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);

	// REMOVE SCROLL BAR BY DEFINING ROWS AND COLUMNS
    system("MODE CON COLS=85 LINES=32");
	   


/************************************* END MSDN LIBRARY *************************************/

	// INITIALISE GAME OBJECTS
	gameInterface newGameInterface;
	gameCommands gameCommand;
	gameWorld newGame;
	gamePlayer newPlayer;
	
	
	// LOAD GFX AND COMMANDS
	newGame.load_gui_gfx();
	newPlayer.load_gui_gfx();
	newScreenOutput.load_gui_gfx();
	newGameInterface.load_gui_gfx();
	gameCommand.load_character_array();

	// VARIABLES
	std::string game_menu_selection = "",item_in_hand,response_buffer,room_item_line,item_parse_in,interaction,display_item,save_name,T;
	
	int item_array_space,food_array_space,use_status=0,pop_out_item=0,global_x,global_y,global_z;
	bool menu_flag=true, pickup_flag=false, use_flag=false, use_flag_2=false, eat_flag=false, inspect_flag=false, save_flag=false, set_game=true;

	system ("CLS");
	newScreenOutput.do_pre_load();


	do{ // MAIN MENU
		system ("CLS");
		main_menu_select = newScreenOutput.do_title_screen();
		//main_menu_select=gameCommand.main_menu_select();



		if(main_menu_select =='1' || main_menu_select =='2'){
				
			new_game_flag=true;	 // INITIALISE GAME START
			newGame.create_save_dir(); // CREATE DIR FOR SAVES
			newScreenOutput.load_game_world_values();	



			if(main_menu_select == '2'){
				// LOAD: LOAD GAME OBJECTS
			
				T = newScreenOutput.load_saved_game();
				if(T=="1"){
					main_menu_select='1';
					set_game=true;
				}
				else if(T=="2"){
					game_menu_selection="";new_game_flag=false;menu_flag=true;main_menu_select='0';set_game=false;
				}
				else{
					newGame.load_gw_saved_game_files(T);
					newScreenOutput.load_player_saved_game_state(T);
					K=newPlayer.load_player_saved_game(T);
					set_game=true;
				}
				// Bring up file screen
				// Let user select. (LOAD?DELETE)

				// Load file attributes
				// Load common attributes


			}


			if(main_menu_select == '1'){ // LOAD: NEW GAME OBJECTS
				// INTRO 
			//	newScreenOutput.intro(); /** TEMP INTRO DISABLE **/
				set_game=true;
				K=100;	

				newGame.load_new_game_text_files();
				newGame.set_room_new_game(); // SET START POSITION
				newGame.set_puzzle_flags();
				newGame.set_room_visited();

				newPlayer.set_player_new_health();
				newPlayer.set_player_array_spaces(); // ARRAYS TO 0
				newPlayer.set_player_new_items();
				newPlayer.set_player_new_food();
				newPlayer.set_player_lighter_count();				
			}
						
			

			if(set_game == true){
				auto future = std::async(timer); // START TIMER
				newScreenOutput.set_new_heath_colour(); // SET HEALTH COLOUR	
				response_buffer = ""; // CLEAR RESPONSE STRING

				do{
					system ("CLS");		
					newPlayer.update_player_health(K);

					global_x=newGame.get_x_pos(), global_y=newGame.get_y_pos(),global_z=newGame.get_z_pos();
					newScreenOutput.set_coordinates(global_x,global_y,global_z);
					newScreenOutput.set_map_clear(newGame.set_clear(),global_x,global_y,global_z);
	
					std::stringstream health_bar; // LEFT STREAM 1/3
					std::stringstream room_name; // RIGHT STREAM 1/3

					std::stringstream player_arrays; // LEFT STEAM 2/3
					std::stringstream room_description; // RIGHT STEAM 2/3
		
					std::stringstream game_interface; // LEFT STEAM 2/3
					std::stringstream game_mini_map; // RIGHT STEAM 2/3

					// 1/3 TOP SCREEN
					newPlayer.build_player_health(health_bar); // 1/3 BUILD LEFT SCREEN TOP
					newGame.build_room_name(room_name); // 1/3 BUILD RIGHT SCREEN TOP
					newScreenOutput.screen_output_top(health_bar, room_name, 17); // 1/3 OUTPUT SCREEN TOP

					// 2/3 MID SCREEN
					newPlayer.build_player_arrays(player_arrays); // 2/3 BUILD LEFT SCREEN MID
					newGame.build_room_description(room_description);// 2/3 BUILD RIGHT SCREEN MID
					newScreenOutput.screen_output_middle(player_arrays, room_description, 17); // 2/3 OUTPUT SCREEN MIDDLE

					// 3/3 BOTTOM SCREEN
					newGame.build_game_interface(game_interface); // 3/3 BUILD LEFT SCREEN BOTTOM
					newGameInterface.build_mini_map(game_mini_map); // 3/3 BUILD RIGHT SCREEN BOTTOM
					newScreenOutput.screen_output_bottom(game_interface, game_mini_map, 17); // 3/3 OUTPUT SCREEN BOTTOM

					// INPUT STATES

					// MENU MODE
					if(menu_flag == true){
						gotoxy(2,30);
						game_menu_select = gameCommand.char_command(game_menu_select); // PASS MENU INPUT 
						game_menu_selection = gameCommand.validate_char_command(game_menu_select); // VALIDATE MENU INPUT
						response_buffer = game_menu_selection;
					}
					// PICKUP MODE
					else if(pickup_flag == true){
						gotoxy(2,30);
						item_in_hand = gameCommand.process_pickup();
						if(item_in_hand !=""){
							item_array_space = newPlayer.get_item_array_spaces();
							food_array_space = newPlayer.get_food_array_spaces();		
							item_parse_in = newGame.validate_pickup_string(item_array_space, food_array_space, item_in_hand);
							if(item_parse_in != ""){newPlayer.add_item_to_player_array(item_parse_in);
								std::transform(item_in_hand.begin(),item_in_hand.end(),item_in_hand.begin(),::tolower);item_in_hand[0]=toupper(item_in_hand[0]);
								response_buffer = "You picked up the "+item_in_hand+".";newScreenOutput.set_good_bad_response(1);}
							else{response_buffer = "You cannot pick that up.";newScreenOutput.set_good_bad_response(0);}
							game_menu_selection = "";pickup_flag=false;menu_flag=true;
						}
						else{response_buffer = "Invalid Command. Please try again.";newScreenOutput.set_good_bad_response(0);
						game_menu_selection = "";pickup_flag=false;menu_flag=true;}
					}
					//USE MODE
					else if(use_flag == true){
						gotoxy(2,30);
						if(use_flag == true && use_flag_2 == false){		
							item_in_hand = gameCommand.process_use();
							if(item_in_hand !=""){
								display_item = item_in_hand;
								use_status = newPlayer.process_use_command(item_in_hand);
								item_in_hand = newPlayer.get_item_in_hand();
								// NO MATCH
								if(use_status == 0){response_buffer = "There is no such item.";	game_menu_selection="";use_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(0);}
								// MATCH
								else if(use_status == 1){std::transform(display_item.begin(),display_item.end(),display_item.begin(),::tolower);display_item[0]=toupper(item_in_hand[0]);response_buffer = "Use "+display_item+" with?";use_flag_2 = true;newScreenOutput.set_good_bad_response(1);}
								// WRONG MATCH
								else if(use_status == 2){response_buffer = "You cannot use that, though it does look edible.";game_menu_selection = "";use_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(0);}
								// FAIL
								else if(use_status == 3){
									std::transform(display_item.begin(),display_item.end(),display_item.begin(),::toupper);
									std::cout<<"THE GAME ITEM IS "<<display_item<<std::endl;
									if(display_item=="LATCH" || display_item=="BUTTON" ||display_item=="LADDER" || display_item == "STAIRS" || display_item == "PIANO" || display_item == "DRAIN PIPE"){
										int f =	newGame.do_solo_use(display_item);
										if(f==0){response_buffer = "There is no "+display_item+".";}
										else if(f==1){response_buffer = "You unlatched the door.";}
										else if(f==2){response_buffer = "A Ladder descends from the ceiling!";}
										else if(f==3){response_buffer = "Nothing happened...";}
										else if(f==4){response_buffer = "You used the "+display_item+".";}
										else if(f==5){response_buffer = "The Piano is currently unplayable";}
										else if(f==6){response_buffer = "Your Melody filled the Barn!";}
									}
									use_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(1);
								}
								else{response_buffer = "Invalid Command. Please try again.";game_menu_selection = "";use_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(0);}
							}
							else{response_buffer = "Invalid Command. Please try again.";game_menu_selection = "";use_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(0);}
						}
						// ACCEPTED INTERACTION
						else if(use_flag == true && use_flag_2 == true){
							gotoxy(2,30);
							interaction = gameCommand.process_interaction(item_in_hand, display_item);
							if(interaction != ""){
								pop_out_item = newGame.process_total_use_command(item_in_hand, interaction);
								if(pop_out_item == 1){newPlayer.pop_item(item_in_hand);response_buffer = "You used your "+display_item+".";newScreenOutput.set_good_bad_response(1);}
								else{response_buffer = "They don't work together.";newScreenOutput.set_good_bad_response(0);}
								game_menu_selection = "";use_flag=false;use_flag_2=false;menu_flag=true;
							}	
							else{response_buffer = "Invalid Command. Please try again.";newScreenOutput.set_good_bad_response(0);
								game_menu_selection = "";use_flag=false;use_flag_2=false;menu_flag=true;
							}
						}
					}
					// EAT MODE
					else if(eat_flag == true){
						gotoxy(2,30);
						item_in_hand = gameCommand.process_eat();
						if(item_in_hand != ""){
							display_item = item_in_hand;
							use_status = newPlayer.process_eat_command(item_in_hand);
							if(use_status == 0){response_buffer = "There is no such item.";	game_menu_selection="";eat_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(0);}	
							else if(use_status == 1){K = newPlayer.eat_item(item_in_hand, K);item_in_hand=newPlayer.get_item_in_hand();newPlayer.pop_food(item_in_hand);
									newScreenOutput.set_health_colours(K);std::transform(display_item.begin(),display_item.end(),display_item.begin(),::tolower);display_item[0]=toupper(item_in_hand[0]);
										response_buffer = "You have eaten a "+display_item+".";newScreenOutput.set_good_bad_response(1);game_menu_selection = "";eat_flag=false;menu_flag=true;}
							else if(use_status == 2){response_buffer = "You crack your tooth and lose health.";K=K-5;game_menu_selection = "";eat_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(0);newScreenOutput.set_health_colours(K);}
							else{response_buffer = "Invalid Command. Please try again.";game_menu_selection = "";eat_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(0);}
						}
						else{response_buffer = "Invalid Command. Please try again.";game_menu_selection = "";eat_flag=false;menu_flag=true;newScreenOutput.set_good_bad_response(0);}
						game_menu_selection = "";eat_flag=false;menu_flag=true;
					}
					// INSPECT MODE
					else if(inspect_flag == true){
						gotoxy(2,30);
						response_buffer = newGame.process_inspection_comamnd(gameCommand.process_inspection());
						if(response_buffer == ""){response_buffer = "Nothing of Interest.";}
						menu_flag = true;inspect_flag = false;
					}

					/** GAME STATES **/
					if(game_menu_selection == "MOVE"){
						response_buffer=newGame.move_player(game_menu_select);
						if(response_buffer == "You cannot transverse solid objects." || response_buffer.substr(0,3) == "The" || response_buffer == "A raging fire blocks your path."){
							newScreenOutput.set_good_bad_response(0);}
						else{newScreenOutput.set_good_bad_response(1);}}
					else if(game_menu_selection == "PICKUP"){game_menu_selection = "";menu_flag=false;pickup_flag=true;newScreenOutput.set_good_bad_response(1);}
					else if(game_menu_selection == "USE"){game_menu_selection="";menu_flag=false;use_flag=true;newScreenOutput.set_good_bad_response(1);}
					else if(game_menu_selection == "EAT"){game_menu_selection = "";menu_flag = false;eat_flag = true;}
					else if(game_menu_selection == "INSPECT"){game_menu_selection = "";menu_flag = false;inspect_flag = true;}

	/** NON EVENT DRIVEN COMMANDS **/


				
					// INGAME OPTION 9 (H): HELP SCREEN
					else if(game_menu_selection == "HELP"){			
						system("CLS");newScreenOutput.help_screen();gotoxy(2,30);system("PAUSE");
					}

					// INGAME OPTION 10 (N): SAVE GAME
					else if(game_menu_selection == "SAVE"){	
						menu_flag=false;game_menu_selection="";gotoxy(2,30);		
					
						save_name =	gameCommand.save_game();
						if (save_name != "SAVE_ERROR" && save_name != "FILE_ERROR" && save_name != "NAME_ERROR"){						
							newGame.save_write(save_name);newScreenOutput.save_map(save_name);newPlayer.save_player(save_name);
							newScreenOutput.set_good_bad_response(1);response_buffer="Game Saved.";save_name ="";menu_flag=true;}

						else if(save_name == "SAVE_ERROR"){
							newScreenOutput.set_good_bad_response(0);
							response_buffer = "You entered an invalid save name. Please try again.";
							menu_flag = true;}

						else if(save_name == "FILE_ERROR"){
							newScreenOutput.set_good_bad_response(0);
							response_buffer = "Too Many Save Files. Please Delete and try again.";
							menu_flag = true;}

						else if(save_name == "NAME_ERROR"){
							newScreenOutput.set_good_bad_response(0);
							response_buffer = "File name too long. Max 10 Characters.";
							menu_flag = true;}}

					// INGAME OPTION 11 (P): QUIT TO MENU
					else if(game_menu_selection == "MENU"){			
						char mm;system("CLS");newScreenOutput.exit_to_main_menu();mm=_getch();
						if(mm=='Y' || mm =='y'){game_menu_selection="";new_game_flag=false;menu_flag=true;main_menu_select='0';}}

					// INGAME OPTION 12 (P): EXIT TO WINDOWS
					else if(game_menu_selection == "QUIT"){			
						char mm;system("CLS");newScreenOutput.exit_to_windows();mm=_getch();
						if(mm== 'Y' || mm =='y'){exit(1);}}

					newScreenOutput.set_health_colours(K);
					newGame.set_response_string(response_buffer); // SET APT REPSONSE

					// FINISHED THE GAME
					if(global_x==4 && global_y==3 && global_z==0){
						if(game_menu_select == 'W' || game_menu_select == 'w'){						
							newScreenOutput.ending();new_game_flag=false;}}

				}while(new_game_flag == true); // END THE MAIN GAME
			} // END IF SET FLAG (FOR LOAD GAME TO RETURN TO MENU
		}//END IF 1 OR 2 (NEW OR LOAD GAME)
/*****************************************************************************/
		// MAIN MENU 3: ABOUT
		else if(main_menu_select =='3'){
			// ABOUT THE GAME
			system("CLS");
			std::cout<<"ABOUT US"<<std::endl;
			
			gotoxy(0,1);
			system("PAUSE");
		}

		// MAIN MENU 4: QUIT TO WINDOWS
		else if(main_menu_select =='4'){
			char mm;system("CLS");newScreenOutput.exit_to_windows();mm=_getch();
			if(mm=='Y'||mm =='y'){exit(1);}}

	}while(game_engine_flag == true);// END MAIN MENU

	return 0;

}// EOF MAIN


///////////////
