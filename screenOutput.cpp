#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<algorithm>
#include<limits>
#define NOMINMAX
#include"windows.h"
#include "gameWorld.h"
#include "screenOutput.h"

//
void myxy(int x, int y){
  COORD p = { x, y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

// SET GOOD/BAD RESPONSES
void screenOutput::load_game_world_values(){
	std::string file_name = "ng-mini-map.txt";
	std::string text_file_line;
	std::fstream fstream_text_file_name(file_name);

	if(!fstream_text_file_name){std::cout<<"Could not Find Room File"<<std::endl;}
			//
		if (fstream_text_file_name.is_open()){
			while(getline(fstream_text_file_name,text_file_line)){
					// Co-ordinate Conversion
				std::string array_coords = text_file_line.substr (0,3);   // Room co-ordinates
				std::string line_right = text_file_line.substr(text_file_line.find("~") + 1); // Description
				char X = array_coords[0];
				char Y = array_coords[1];
				char Z = array_coords[2];
				int Xi = X - '0';
				int Yi = Y - '0';
				int Zi = Z - '0';
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
					visited[Xi][Yi][Zi] = false;
				}//EOF WHILE F-STREAM
			std::cout<<"Textfile loaded OK"<<std::endl;
			fstream_text_file_name.close();
		}// EOF TEXT FILE OPEN
	// GO NEXT
}
//
void::screenOutput::set_coordinates(int x, int y, int z){
	X_pos=x;Y_pos=y;Z_pos=z;
}

void screenOutput::set_good_bad_response(int x){
	if(x==0){good_bad=false;}
	else if(x==1){good_bad=true;}
}

void screenOutput::set_new_heath_colour(){
	health_colour=100;
}

void screenOutput::set_health_colours(int K){
	health_colour=K;
	if(health_colour>100){health_colour=100;}
}

void screenOutput::set_map_clear(int C, int x, int y, int z){
	if(C==0){map_clear[x][y][z]=false;}
	else if(C==1){map_clear[x][y][z]=true;}
}
// BUILD SCREEN DISPLAY TOP SECTION
void screenOutput::screen_output_top(std::istream& is1, std::istream& is2, std::size_t width){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);  // BLUE 
	std::cout<<TOP_LEFT<<std::string(15,H_STRAIGHT_LINE)<<TOP_T<<std::string(67,H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl; //83
	std::string line1;std::string line2;std::string pad;
	const int i=67;int w=16;int k;int j;int t;int health_bar;int far_right;int K;
	if(health_colour >=85 && health_colour <= 100){K = 10;}
	else if(health_colour >=50 && health_colour < 85){K = 14;}
	else if(health_colour >=20 && health_colour < 50){K = 12;}
	else if(health_colour < 20){K=4;}
    while(std::getline(is1, line1)){
        if(line1.size() < width){
			std::getline(is2, line2);
			// LEFT SIDE
			std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, K);std::cout<< line1;// WHITE
			// SET PADDING;
			health_bar = line1.length();
			w = w - health_bar; 
			SetConsoleTextAttribute(hConsole, 11); std::cout<<std::setw(w)<<V_STRAIGHT_LINE; // BLUE
			// RIGHT SIDE
			j=line2.length(); k=i-j; k=k/2;
			SetConsoleTextAttribute(hConsole, 13);std::cout <<std::string(k,' ')<< line2;// PINK
			far_right = k+j;t=i-far_right;t=t+1;
			SetConsoleTextAttribute(hConsole, 11);std::cout<<std::setw(t)<<V_STRAIGHT_LINE<<std::endl; // BLUE
		}
    }
}

// BUILD SCREEN DISPLAY MIDDLE SECTION
void screenOutput::screen_output_middle(std::istream& is1, std::istream& is2, std::size_t width){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout<<LEFT_T<<std::string(15,H_STRAIGHT_LINE)<<CROSS<<std::string(67,H_STRAIGHT_LINE)<<RIGHT_T<<std::endl; //83
	std::string line1;std::string line2;std::string pad;
	int line_counter=0;char x;char y;const int w=16;const int n=67;int q;int r ;int l;int c;int m;

	 while(std::getline(is1, line1)){
		 // CORRECT SCREEN BUILD
		 if(line_counter == 1 || line_counter == 9 || line_counter == 11){x=LEFT_T;y=RIGHT_T;}
		 else{x=V_STRAIGHT_LINE;y=V_STRAIGHT_LINE;}
		 // CORRECT COLOURS
		 if(line_counter == 0 || line_counter == 10){c=13;} // SET PINK (MENU TITLES)
		 else if(line_counter == 1 || line_counter == 9 || line_counter == 11){c=11;} // SET BLUE (GFX)
		 else{if(line1 == "-Empty-"){c=8;}else{c=14;}
		 } // SET WHITE (MENU ITEMS)
		 if(line1.size() < width){
			std::getline(is2, line2);
			// LEFT SIDE
			std::cout<<x;SetConsoleTextAttribute(hConsole, c); // (PINK/WHITE) (YELLOW/GREY)
			q=line1.length();r=w-q;r=r/2;r=w-r;r=r-1;l=w-r;
			std::cout <<std::setw(r)<<line1;SetConsoleTextAttribute(hConsole, 11);std::cout<<std::setw(l)<<y; // BLUE
			// RIGHT
			SetConsoleTextAttribute(hConsole, 7);m=n-line2.length();std::cout<<' '<< line2; // GREY
			SetConsoleTextAttribute(hConsole, 11);std::cout<<std::setw(m)<<V_STRAIGHT_LINE<<std::endl;// BLUE
		}
		line_counter++;
	}
}

// BUILD SCREEN DISPLAY BOTTOM SECTION
void screenOutput::screen_output_bottom(std::istream& is1, std::istream& is2, std::size_t width){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout<<LEFT_T<<std::string(15,H_STRAIGHT_LINE)<<BOTTOM_T<<std::string(67,H_STRAIGHT_LINE)<<RIGHT_T<<std::endl; //83
	std::string line1;std::string line2;std::string pad;
	int line_counter=0;char x;char y;const int Q=84;int a, j, map_vertical_line_counter=4, map_horizontal_line_counter=0, map_dimension_line_counter=Z_pos;
	visited[X_pos][Y_pos][Z_pos]=true;
    while(std::getline(is1, line1)){
       if(line_counter==1){x=LEFT_T;y=RIGHT_T;a=11;}
	   else{x=V_STRAIGHT_LINE;y=x;a=13;}//
	   if(line_counter==0){if(good_bad==true){a=2;}else{a=4;}}
       if(line1.size() < width)
            //LEFT
		    pad = std::string(width - line1.size(), ' ');
		    std::getline(is2, line2);
			std::cout<<x;SetConsoleTextAttribute(hConsole, a);std::cout<<line1;  // PINK
			if(line_counter<1){SetConsoleTextAttribute(hConsole, 11);j=Q-line1.length();}
			else{SetConsoleTextAttribute(hConsole, 11);j=Q-line1.length()-18;}
			std::cout<<std::setw(j)<<y;SetConsoleTextAttribute(hConsole, 11);  // BLUE 
			//RIGHT
			if(line_counter>1){SetConsoleTextAttribute(hConsole, 7);std::cout<<std::string(5, ' ')<<line2;SetConsoleTextAttribute(hConsole, 11);} // GREY
			else{SetConsoleTextAttribute(hConsole, 7);std::cout<<line2;SetConsoleTextAttribute(hConsole, 11);} // GREY
			char T;int S;
			if(line_counter > 1){	
				for(map_horizontal_line_counter=0;map_horizontal_line_counter<7;map_horizontal_line_counter++){
					// COLOUR X, Y
					if(visited[map_horizontal_line_counter][map_vertical_line_counter][map_dimension_line_counter]){
						if(map_clear[map_horizontal_line_counter][map_vertical_line_counter][map_dimension_line_counter]){S=10;}
						else{S=6;}
					}
					else if(!visited[map_horizontal_line_counter][map_vertical_line_counter][map_dimension_line_counter]){S=4;}
					// BRICK X, Y
					if(map_horizontal_line_counter == X_pos && map_vertical_line_counter == Y_pos){T=178;}
					else{T=mini_map[map_horizontal_line_counter][map_vertical_line_counter][map_dimension_line_counter];}
					SetConsoleTextAttribute(hConsole, S);
					std::cout<<T;	
				}
				map_vertical_line_counter--;
			}
			SetConsoleTextAttribute(hConsole, 11);
			if(line_counter>1){std::cout<<std::setw(6)<<V_STRAIGHT_LINE<<std::endl;}
			else{std::cout<<std::endl;}
			line_counter++;
		}
		while(std::getline(is2, line2)) {
			auto pad = std::string(width, ' ');
		}
		std::cout<<LEFT_T<<std::string(65,H_STRAIGHT_LINE)<<std::string(1,BOTTOM_T)<<std::string(17,H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
		std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<BOTTOM_LEFT<<std::string(83, H_STRAIGHT_LINE)<<BOTTOM_RIGHT; //83
		
		SetConsoleTextAttribute(hConsole, 7); // WHITE - FOR CIN
}

//
void::screenOutput::do_pre_load(){	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout<<TOP_LEFT<<std::string(83,H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;
	for(int i=0; i<14; i++){std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;}
	std::cout<<V_STRAIGHT_LINE<<std::setw(36);SetConsoleTextAttribute(hConsole, 13);std::cout<<"Big Earl's";SetConsoleTextAttribute(hConsole, 11);std::cout<<" Computer Barn";
	SetConsoleTextAttribute(hConsole, 14);std::cout<<" Presents";SetConsoleTextAttribute(hConsole, 11);std::cout<<std::setw(25)<<V_STRAIGHT_LINE<<std::endl;
	for(int i=0; i<14; i++){std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;}
	std::cout<<BOTTOM_LEFT<<std::string(83,H_STRAIGHT_LINE)<<BOTTOM_RIGHT;
	Sleep(3000);system ("CLS");

	std::cout<<TOP_LEFT<<std::string(83,H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl;
	for(int i=0; i<15; i++){std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;}
	std::cout<<V_STRAIGHT_LINE<<std::setw(40);SetConsoleTextAttribute(hConsole, 2);std::cout<<"A Game by Joseph";SetConsoleTextAttribute(hConsole, 8);std::cout<<" \"SmokiestJoe\"";
	SetConsoleTextAttribute(hConsole, 2); std::cout<<" Rose";SetConsoleTextAttribute(hConsole, 11);std::cout<<std::setw(25)<<V_STRAIGHT_LINE<<std::endl;
	for(int i=0; i<14; i++){std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;}
	std::cout<<BOTTOM_LEFT<<std::string(83,H_STRAIGHT_LINE)<<BOTTOM_RIGHT;
	Sleep(2000);system ("CLS");
}

//
char::screenOutput::do_title_screen(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);


	system("CLS");	
	std::string load_array[4] = {"New  Game","Load Game","About","Exit to Windows"};
	const int line_length = 83;
	std::string out_name, f_out;
	
	int assign_load_space=0,menu_pointer=0,space_buffer=0,l_space=0,r_space=0;
	bool load_flag=true;
	
	// SCREEN BUILD BEGINS
	while(true){
		system("CLS");
		SetConsoleTextAttribute(hConsole, 11);
		
		std::cout<<TOP_LEFT<<std::string(83,H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl;
		std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 12);std::cout<<std::string(28,' ')<<"  __                                "<<std::setw(20);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 12);std::cout<<std::string(28,' ')<<" /  |      /| | /      /    /       "<<std::setw(20);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 12);std::cout<<std::string(28,' ')<<"(___|     ( | |   ___ (___ (___     "<<std::setw(20);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 12);std::cout<<std::string(28,' ')<<"|   )     | | )| |   )|   )|        "<<std::setw(20);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 12);std::cout<<std::string(28,' ')<<"|  /      | |/ | |__/ |  / |__      "<<std::setw(20);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 12);std::cout<<std::string(28,' ')<<"                 __/                "<<std::setw(20);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 14);std::cout<<std::string(38,' ')<<"      /					"<<std::setw(5);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 14);std::cout<<std::string(38,' ')<<" ___ (___            			"<<std::setw(5);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 14);std::cout<<std::string(38,' ')<<"|   )|               			"<<std::setw(5);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 14);std::cout<<std::string(38,' ')<<"|__/||__   	                         "<<std::setw(4);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<std::string(23,' ')<<"  __                 __                "<<std::setw(22);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<std::string(23,' ')<<" /|  /             |/  |               "<<std::setw(22);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<std::string(23,' ')<<"( | (___  ___      |___| ___  ___  ___ "<<std::setw(22);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<std::string(23,' ')<<"  | |   )|___)     |   )|   )|   )|   )"<<std::setw(22);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<std::string(23,' ')<<"  | |  / |__       |__/ |__/||    |  / "<<std::setw(22);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<LEFT_T<<std::string(83,H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
		std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<std::string(30,' ')<<"A Text Adventure Showcase"<<std::setw(29);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
		std::cout<<LEFT_T<<std::string(83,H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
		std::cout<<V_STRAIGHT_LINE<<std::string(83,' ')<<V_STRAIGHT_LINE<<std::endl;


		for(int i=0;i<4;i++){
			if(i==menu_pointer){
				std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::string menu_line = load_array[i];
					int j = line_length-menu_line.length();int k = j/=2;
					std::cout<<std::string(k,' ')<<load_array[i]<<std::string(k,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
					std::cout<<V_STRAIGHT_LINE<<std::string(83,' ')<<V_STRAIGHT_LINE<<std::endl;}
				else{
					std::cout<<V_STRAIGHT_LINE;	SetConsoleTextAttribute(hConsole, 7);std::string menu_line = load_array[i];
					int j = line_length-menu_line.length();int k = j/=2;
					std::cout<<std::string(k,' ')<<load_array[i]<<std::string(k,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
					std::cout<<V_STRAIGHT_LINE<<std::string(83,' ')<<V_STRAIGHT_LINE<<std::endl;}				
			}
			SetConsoleTextAttribute(hConsole, 11);		
			std::cout<<BOTTOM_LEFT<<std::string(83,H_STRAIGHT_LINE)<<BOTTOM_RIGHT;

			while(!GetAsyncKeyState(VK_RETURN)){		
				if(GetAsyncKeyState(VK_UP)!=0){
					menu_pointer-=1;
					if(menu_pointer==-1){menu_pointer=3;}break;
				}
				else if(GetAsyncKeyState(VK_DOWN)!=0){
					menu_pointer+=1;
					if(menu_pointer==4){menu_pointer=0;}break;
				}
				else if(GetAsyncKeyState(VK_RETURN)!=0){	
					std::cin.ignore(std::numeric_limits<std::streamsize>::max()-1, '\n'); 
					switch(menu_pointer){
					case 0:{return '1';}break;case 1:{return '2';}break;case 2:{return '3';}break;case 3:{return '4';}break;}	
					break;
				}
			}
			Sleep(150);
		}
	return '0';
} 

// DO CONFIRM EXIT TO MENU
void screenOutput::exit_to_main_menu(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout<<TOP_LEFT<<std::string(83,H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl;
	for(int i=0; i<15; i++){std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;}
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 8);std::cout<<std::setw(56)<<"Quit to the main Menu? Y/N"<<std::setw(28);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	for(int i=0; i<14; i++){std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;}
	std::cout<<BOTTOM_LEFT<<std::string(83,H_STRAIGHT_LINE)<<BOTTOM_RIGHT;
}

// DO CONFIRM EXIT TO WINDOWS
void screenOutput::exit_to_windows(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout<<TOP_LEFT<<std::string(83,H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl;
	for(int i=0; i<15; i++){std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;}
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 8);std::cout<<std::setw(53)<<"Exit to Windows? Y/N"<<std::setw(31);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	for(int i=0; i<14; i++){std::cout<<V_STRAIGHT_LINE<<std::setw(84)<<V_STRAIGHT_LINE<<std::endl;}
	std::cout<<BOTTOM_LEFT<<std::string(83,H_STRAIGHT_LINE)<<BOTTOM_RIGHT;
}

// DO GAME OVER
void screenOutput::game_over(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);

	std::cout<<TOP_LEFT<<std::string(83,H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 144);std::cout<<"_________________";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|     R.I.P     |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(18,' ')<<"________________";SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 144);std::cout<<"________________"<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(18,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|                                               |";SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(18,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|            IN LOVING MEMORY OF YOU            |";SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(18,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|                                               |";SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(18,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|                   YOU  DIED                   |";SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(18,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|                                               |";SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(18,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|_______________    GAME OVER    _______________|";SetConsoleTextAttribute(hConsole, 144);std::cout<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 152);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|               |";SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(34,' ');SetConsoleTextAttribute(hConsole, 128);std::cout<<"|_______________|";SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(32,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(17,' ')<<"                                                  "<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 042);std::cout<<std::string(17,' ')<<"                                                  "<<std::string(16,' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<BOTTOM_LEFT<<std::string(83,H_STRAIGHT_LINE)<<BOTTOM_RIGHT;
}

// HELP SCREEN
void screenOutput::help_screen(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	
	std::cout<<TOP_LEFT<<std::string(11,H_STRAIGHT_LINE)<<TOP_T<<std::string(71, H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl;

	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<" GAME PLAY ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"The game is a simplistic text adventure that combines single button    ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"inputs with written English commands. To activate a \"mode\" you press   ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"the corresponding key and then write your command into the console.    ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"A brief overview is listed below.                                      ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<LEFT_T<<std::string(11,H_STRAIGHT_LINE)<<CROSS<<std::string(71, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;

	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<"PICKUP (Q) ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"Then type the name of the item that you wish to pickup and it appears  ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"in your inventory on the left of the screen.                           ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;

	std::cout<<LEFT_T<<std::string(11,H_STRAIGHT_LINE)<<CROSS<<std::string(71, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<"  USE (E)  ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"You may wish to use items in your inventory, or interact with objects  ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;

	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"in The Barn. This one command caters for all of your needs.            ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<LEFT_T<<std::string(11,H_STRAIGHT_LINE)<<CROSS<<std::string(71, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<"  EAT (R)  ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"Reasonably self explanatory, though be careful what you chew on!       ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;


	std::cout<<LEFT_T<<std::string(11,H_STRAIGHT_LINE)<<CROSS<<std::string(71, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<"INSPECT (T)";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"On occasion you may want to take a closer look at something either in  ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"The Barn, or in your inventory. Simply type the name of the object you ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"wish to look at and if there is anything further to discover, the      ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"BARN BOT 2000 will tell you so!                                        ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;

	std::cout<<LEFT_T<<std::string(11,H_STRAIGHT_LINE)<<CROSS<<std::string(71, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<"  HEALTH   ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"You lose health over time during your run of The Barn. If you lose all ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"of your health, it is game over for you. Do not despair however, for   ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"your health can be replenished by eating various foods found around    ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"The Barn.                                                              ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	
	std::cout<<LEFT_T<<std::string(11,H_STRAIGHT_LINE)<<CROSS<<std::string(71, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
	std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<" MINI MAP  ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"So you don't get too lost on your travels, you have been provided with ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"a Mini-Map. The map has three colour states to aid you with your quest.";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"RED means that you have not yet visited that room. YELLOW means you    ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"have visited, but there are still things to pickup or interact with.   ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(11, ' ')<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 7);std::cout<<"GREEN means room complete. No need to hang around or visit again.      ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<LEFT_T<<std::string(11,H_STRAIGHT_LINE)<<BOTTOM_T<<std::string(71, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
	std::cout<<V_STRAIGHT_LINE<<std::string(83, ' ')<<V_STRAIGHT_LINE<<std::endl;
	std::cout<<BOTTOM_LEFT<<std::string(83,H_STRAIGHT_LINE)<<BOTTOM_RIGHT;
}

//
void screenOutput::intro(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	
	system("CLS");

	std::string special_order = "SPECIAL ORDER 937\n";
	std::string priority = "PRIORITY ONE\nINSURE RETURN OF ORGANISM FOR ANALYSIS.\nALL OTHER CONSIDERATIONS SECONDARY.\n";
	std::string crew_ex = "CREW EXPENDABLE.";
	std::string whoops = "\n\n\nOOPS, SORRY, WRONG MESSAGE.";

	int x=0;
	while(special_order[x]!='\0'){std::cout<<special_order[x];Sleep(50);x++;}
	Sleep(1000);std::cout<<"\n\n";
	
	x=0;
	while(priority[x]!='\0'){std::cout<<priority[x];Sleep(50);x++;}
	Sleep(1000);std::cout<<"\n\n";

	x=0;
	while(crew_ex[x]!='\0'){std::cout<<crew_ex[x];Sleep(50);x++;}
	Sleep(2000);

	x=0;
	while(whoops[x]!='\0'){std::cout<<whoops[x];Sleep(50);x++;}
	Sleep(1000);

	system("CLS");SetConsoleTextAttribute(hConsole, 7);
	x=0;
	std::string intro = "\n\nYou went for a walk. Nothing uncommon about that, most people do. The night was dark and the moon shone brightly, so you decided to stretch your legs and take a wander.\n\nWhile you were out and about, you came across a building. Looking at its structure,\nit appeared to be some kind of Barn. Being a person of a curious nature, you decided\nto inspect further, as your curiosity got the better of you.\n\nTo your eyes, the building looked abandoned. Long abandoned. So you decided to take acloser look. As you walked the perimeter, you came across what would once upon a time\nago have been the entrance. Because you found it extremely difficult to mind your ownbusiness, you took a look inside. Visibility was poor, so you entered The Barn.\n\nThat is where our story begins. The story of you and your night...";
	std::string ANATB= "\n\n\nYour Night at The Barn.";

	while(intro[x]!='\0'){std::cout<<intro[x];Sleep(50);x++;}
	Sleep(2000);

	x = 0;
	while(ANATB[x]!='\0'){std::cout<<ANATB[x];Sleep(50);x++;}
	Sleep(1000);

	COORD p = { 0, 31 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	system("PAUSE");
}

//
void screenOutput::ending(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);
	system("CLS");
	std::string ending_line_one = "\nThere it is. You escaped The Barn. You stand there, full of disbelief at the events\nthat occurred during your Night at The Barn. You turn and to your amazement, instead of seeing The Barn, there is nothing but fields. Fields, darkness and moonlight.\n\nYou walk off into the night unnerved at what you have seen. Were you hallucinating?\nWas it a dream? Are you under hypnosis?";
	std::string no_gag = "\n\nNo.";
	std::string dir_gag = " You are looking in the wrong direction."; 
	std::string ending_line_two = "\n\nYou turn a little further and see The Barn. Old, dilapidated, derelict. You have no\ninterest in going back the way you came, so you decide to push on into the night.";
	std::string ending_line_three = "\n\nHow long have you been wandering now? Minutes? Hours? Whichever direction you travel in, you are just greeted by more fields and darkness. There is no sign of the road\nfrom which you came, nor any sign of civilisation save one building on the horizon.";
	std::string ending_line_four = "\n\nWith your options dwindling and your hunger pang growing, you chose your last best\nhope for finding your way home. You head toward the building, confident that the\noccupants there will help you.";
	std::string ending_line_five = "\n\nAs you approach, there is but one thought on your mind.";
	std::string ending_line_six = "\n\nWho, these days...";
	std::string ending_line_seven = "\n\n...Lives in a castle?";
	int x=0;
	while(ending_line_one[x]!='\0'){std::cout<<ending_line_one[x];Sleep(50);x++;}
	Sleep(1000);
	x=0;
	while(no_gag[x]!='\0'){std::cout<<no_gag[x];Sleep(50);x++;}
	Sleep(1000);
	x=0;
	while(dir_gag[x]!='\0'){std::cout<<dir_gag[x];Sleep(50);x++;}
	Sleep(500);
	x=0;
	while(ending_line_two[x]!='\0'){std::cout<<ending_line_two[x];Sleep(50);x++;}
	Sleep(2000);
	x=0;
	while(ending_line_three[x]!='\0'){std::cout<<ending_line_three[x];Sleep(50);x++;}
	Sleep(1000);
	x=0;
	while(ending_line_four[x]!='\0'){std::cout<<ending_line_four[x];Sleep(50);x++;}
	Sleep(1000);
	x=0;
	while(ending_line_five[x]!='\0'){std::cout<<ending_line_five[x];Sleep(50);x++;}
	Sleep(1000);
	x=0;
	while(ending_line_six[x]!='\0'){std::cout<<ending_line_six[x];Sleep(50);x++;}
	Sleep(2000);
	x=0;
	while(ending_line_seven[x]!='\0'){std::cout<<ending_line_seven[x];Sleep(50);x++;}
	Sleep(1000);std::cout<<"\n\n";

	system("PAUSE");
	SetConsoleTextAttribute(hConsole, 11);

}

//
void screenOutput::save_map(std::string file_name){
	int x_write=0,y_write=0,z_write=0;
	std::string X_string,Y_string,Z_string;
	std::ofstream temp_file("c:/ANATB/save-"+file_name+".txt", std::ios::app);

	x_write=0;y_write=0;z_write=0;

	while(z_write<3){
		while(y_write<5){
			while(x_write<7){
				X_string = std::to_string(x_write);Y_string = std::to_string(y_write);Z_string = std::to_string(z_write);
				temp_file<<X_string<<Y_string<<Z_string<<"~"<<map_clear[x_write][y_write][z_write]<<std::endl;
				x_write++;
			}
			x_write=0;y_write++;
		}
		x_write=0;y_write=0;z_write++;
	}
	temp_file<<health_colour<<std::endl;
	temp_file<<"<--EOF SCREENOUTPUT-->"<<std::endl;
}

// LOAD SAVED GAME
std::string screenOutput::load_saved_game(){
	
	system("CLS");	
	std::string load_array[10] = {"Free Slot","Free Slot","Free Slot","Free Slot","Free Slot","Free Slot","Free Slot","Free Slot","Free Slot","Free Slot"};
	std::string out_name, f_out;
	const int max_char=10;
	int assign_load_space=0,menu_pointer=0,space_buffer=0,l_space=0,r_space=0;
	bool load_flag=true;
	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile(L"c:\\ANATB\\*.*",&data);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// RETRIEVE SAVE FILES
	if( h!=INVALID_HANDLE_VALUE ){
		do{
			char*   nPtr = new char [lstrlen( data.cFileName ) + 1];
			for( int i = 0; i < lstrlen( data.cFileName ); i++ )
				nPtr[i] = char( data.cFileName[i] );
				nPtr[lstrlen( data.cFileName )] = '\0';
			if(nPtr[0]!='.' && assign_load_space <10){
				load_array[assign_load_space] = nPtr;
				assign_load_space++;
			}
		} while(FindNextFile(h,&data));
	} 
	else 
		std::cout << "Error: No such folder." << std::endl;
		FindClose(h);
	
	// CHECK FOR NO SAVE
	if(load_array[0] == "Free Slot"){
		SetConsoleTextAttribute(hConsole, 12);
		std::cout<<"No game files found. Starting new game."<<std::endl;
		Sleep(2000);
		return "1";
	}
	else

	// SCREEN BUILD BEGINS
		while(true){
			system("CLS");
			SetConsoleTextAttribute(hConsole, 11);
			std::cout<<TOP_LEFT<<std::string(83,H_STRAIGHT_LINE)<<TOP_RIGHT<<std::endl;
			std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 13);std::cout<<std::setw(52)<<"SELECT YOUR FILE"<<std::setw(32);SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::endl;
			std::cout<<LEFT_T<<std::string(14, H_STRAIGHT_LINE)<<TOP_T<<std::string(68, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
			std::cout<<V_STRAIGHT_LINE;SetConsoleTextAttribute(hConsole, 14);std::cout<<"  FILE NAME:  ";SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::string(68, ' ')<<V_STRAIGHT_LINE<<std::endl;
			std::cout<<LEFT_T<<std::string(14, H_STRAIGHT_LINE)<<RIGHT_T<<std::string(68, ' ')<<V_STRAIGHT_LINE<<std::endl;

			for(int i=0;i<10;i++){
				if(i==menu_pointer){
					std::cout<<V_STRAIGHT_LINE<<std::string(2,' ');SetConsoleTextAttribute(hConsole, 13);		
					out_name = load_array[i].substr(load_array[i].find("-") + 1);
					f_out = out_name.substr(0,out_name.find("."));space_buffer = max_char-f_out.length();f_out[0] = toupper(f_out[0]);
					if(space_buffer % 2 == 0){l_space=space_buffer/2;r_space=space_buffer/2;}
					else{l_space=space_buffer/2;r_space = max_char-(l_space+f_out.length());}
					std::cout<<std::string(l_space, ' ')<<f_out<<std::string(r_space, ' ')<<std::string(2, ' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::string(68, ' ')<<V_STRAIGHT_LINE<<std::endl;
					std::cout<<V_STRAIGHT_LINE<<std::string(14,'_')<<V_STRAIGHT_LINE<<std::string(68, ' ')<<V_STRAIGHT_LINE<<std::endl;
				}
				else if(i!=menu_pointer && i<assign_load_space){
					std::cout<<V_STRAIGHT_LINE<<std::string(2,' ');SetConsoleTextAttribute(hConsole, 2);
					out_name = load_array[i].substr(load_array[i].find("-") + 1);
					f_out = out_name.substr(0,out_name.find("."));space_buffer = max_char-f_out.length();f_out[0] = toupper(f_out[0]);
					if(space_buffer % 2 == 0){l_space=space_buffer/2;r_space=space_buffer/2;}
					else{l_space=space_buffer/2;r_space=max_char-(l_space+f_out.length());}
					std::cout<<std::string(l_space, ' ')<<f_out<<std::string(r_space, ' ')<<std::string(2, ' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::string(68, ' ')<<V_STRAIGHT_LINE<<std::endl;
					std::cout<<V_STRAIGHT_LINE<<std::string(14,'_')<<V_STRAIGHT_LINE<<std::string(68, ' ')<<V_STRAIGHT_LINE<<std::endl;
				}
				else{
					std::cout<<V_STRAIGHT_LINE<<std::string(2,' ');SetConsoleTextAttribute(hConsole, 8);
					out_name = load_array[i].substr(load_array[i].find("-") + 1);
					f_out = out_name.substr(0,out_name.find("."));space_buffer = max_char-f_out.length();
					if(space_buffer % 2 == 0){l_space=space_buffer/2;r_space=space_buffer/2;}
					else{l_space=space_buffer/2;r_space=max_char-(l_space+f_out.length());}
					std::cout<<std::string(l_space, ' ')<<f_out<<std::string(r_space, ' ')<<std::string(2, ' ');SetConsoleTextAttribute(hConsole, 11);std::cout<<V_STRAIGHT_LINE<<std::string(68, ' ')<<V_STRAIGHT_LINE<<std::endl;
					std::cout<<V_STRAIGHT_LINE<<std::string(14,'_')<<V_STRAIGHT_LINE<<std::string(68, ' ')<<V_STRAIGHT_LINE<<std::endl;
				}				
			}
			std::cout<<LEFT_T<<std::string(14,H_STRAIGHT_LINE)<<BOTTOM_T<<std::string(68, H_STRAIGHT_LINE)<<RIGHT_T<<std::endl;
			std::cout<<V_STRAIGHT_LINE<<std::string(1, ' ')<<TOP_LEFT<<std::string(79, H_STRAIGHT_LINE)<<TOP_RIGHT<<std::string(1, ' ')<<V_STRAIGHT_LINE<<std::endl;
			std::cout<<V_STRAIGHT_LINE<<std::string(1, ' ')<<V_STRAIGHT_LINE<<std::string(79, ' ')<<V_STRAIGHT_LINE<<std::string(1, ' ')<<V_STRAIGHT_LINE<<std::endl;
			std::cout<<V_STRAIGHT_LINE<<std::string(1, ' ')<<V_STRAIGHT_LINE<<std::string(79, ' ')<<V_STRAIGHT_LINE<<std::string(1, ' ')<<V_STRAIGHT_LINE<<std::endl;
			std::cout<<V_STRAIGHT_LINE<<std::string(1, ' ')<<V_STRAIGHT_LINE<<std::string(79, ' ')<<V_STRAIGHT_LINE<<std::string(1, ' ')<<V_STRAIGHT_LINE<<std::endl;
			std::cout<<V_STRAIGHT_LINE<<std::string(1, ' ')<<BOTTOM_LEFT<<std::string(79, H_STRAIGHT_LINE)<<BOTTOM_RIGHT<<std::string(1, ' ')<<V_STRAIGHT_LINE<<std::endl;
			std::cout<<BOTTOM_LEFT<<std::string(83,H_STRAIGHT_LINE)<<BOTTOM_RIGHT;
			
			SetConsoleTextAttribute(hConsole, 7);
			myxy(28,6);	
			std::cout<<"Select your save from the list on the left."<<std::endl;
			myxy(17,7);	
			std::cout<<"Use the Arrow Keys to scroll and press Enter to select your choice."<<std::endl;
			SetConsoleTextAttribute(hConsole, 11);


			while(!GetAsyncKeyState(VK_RETURN)||!GetAsyncKeyState(VK_ESCAPE)){		
				if(GetAsyncKeyState(VK_UP)!=0){
					menu_pointer-=1;
					if(menu_pointer==-1){menu_pointer=assign_load_space-1;}break;}
				else if(GetAsyncKeyState(VK_DOWN)!=0){
					menu_pointer+=1;
					if(menu_pointer==assign_load_space){menu_pointer=0;}break;}
				else if(GetAsyncKeyState(VK_RETURN)!=0){	
					std::cin.ignore(std::numeric_limits<std::streamsize>::max()-1, '\n'); 
					return load_array[menu_pointer];break;}
				else if(GetAsyncKeyState(VK_ESCAPE)!=0){return "2";break;}}
			Sleep(150);
		}
	return 0;
}
//
// LOAD FROM FILE
void screenOutput::load_player_saved_game_state(std::string file_name){
	int load_counter=0,left_char=0;
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
				// Co-ordinate Conversion			
				char X, Y, Z;
				int Xi, Yi, Zi;
				bool_string = text_file_line.substr (0,1);   

				if(text_file_line.length()>1&&text_file_line.substr(0,1)!="<"&&load_counter!=754){
					array_coords = text_file_line.substr (0,3);   // Room co-ordinates
					line_right = text_file_line.substr(text_file_line.find("~") + left_char); 
					line_right_no_tild = text_file_line.substr(text_file_line.find("~") + 1); 
					X = array_coords[0];Y = array_coords[1]; Z = array_coords[2];
					Xi = X - '0'; Yi = Y - '0';Zi = Z - '0';		
				}
				// BOOL ARRAY
				if(load_counter>=525 && load_counter<=629){ // VISITED
					if(line_right_no_tild =="0"){visited[Xi][Yi][Zi]=false;}
					else if(line_right_no_tild =="1"){visited[Xi][Yi][Zi]=true;}
					else{system("CLS");std::cout<<"FATAL ERROR"<<std::endl;Sleep(5000);break;exit(1);}
				}
								
				if(load_counter>=649 && load_counter<=753){
					if(line_right_no_tild == "0"){map_clear[Xi][Yi][Zi]=false;}	
					else if(line_right_no_tild == "1"){map_clear[Xi][Yi][Zi]=true;}
					else{system("CLS");std::cout<<"FATAL ERROR"<<std::endl;Sleep(5000);break;exit(1);}
				}

				else if(load_counter==754){health_colour=std::stoi( text_file_line );}					
					
				else if(load_counter==755){
					if(text_file_line=="<--EOF SCREENOUTPUT-->"){break;}
					else{system("CLS");std::cout<<"FATAL ERROR"<<std::endl;Sleep(5000);break;exit(1);}
				}
				load_counter++;
				
			}//EOF WHILE F-STREAM
			std::cout<<"Textfile loaded OK"<<std::endl;
			fstream_text_file_name.close();
		}
	}	
}