#include<iostream>
#include"gameWorld.h"
#ifndef PLAYER_H_
#define PLAYER_H_
class gamePlayer: public gameWorld{
private:
	std::string food_array[6];
	std::string item_array[7];
	int player_health;
	int food_array_spaces;
	int item_array_spaces;
	std::string item_in_hand;
	int lighter_count;

public:
	void set_player_new_health();
	void set_player_array_spaces();
	void set_player_lighter_count();
	void set_player_new_items();
	void set_player_new_food();

	int get_food_array_spaces();
	int get_item_array_spaces();
	int process_use_command(std::string);
	int process_eat_command(std::string);

	int eat_item(std::string, int);

	std::string get_item_in_hand();

	void pop_item(std::string);
	void pop_food(std::string);
	void add_item_to_player_array(std::string);
	//
	// VER 0.7
	void build_player_health(std::ostream&);
	void build_player_arrays(std::ostream&);
	void save_player(std::string);
	void update_player_health(int);
	int load_player_saved_game(std::string);

	


};// EOF GAME PLAYER

#endif