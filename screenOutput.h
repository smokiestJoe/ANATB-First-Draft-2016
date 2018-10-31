#include<iostream>
#include"gameWorld.h"

#ifndef SCREENOUTPUT_H_
#define SCREENOUTPUT_H_

class screenOutput: public gameWorld{
private:
	int health_colour;
	bool good_bad;
	bool map_clear[7][5][3];

public:
	void set_good_bad_response(int);
	void set_health_colours(int);
	void set_new_heath_colour();

	void screen_output_top(std::istream&, std::istream&, std::size_t);
	void screen_output_middle(std::istream&, std::istream&, std::size_t);
	void screen_output_bottom(std::istream&, std::istream&, std::size_t);
	void set_coordinates(int, int, int);
	void load_game_world_values();
	void set_map_clear(int, int, int, int);
	void save_map(std::string);

	void do_pre_load();
	char do_title_screen();
	void exit_to_main_menu();
	void exit_to_windows();
	void game_over();
	void help_screen();

	void intro();
	void ending();

	std::string load_saved_game();
	void load_player_saved_game_state(std::string);
};
#endif