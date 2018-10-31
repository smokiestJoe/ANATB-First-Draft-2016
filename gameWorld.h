#include<iostream>
#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_
class gameWorld{

private:
	// VER 0.7
	std::string room_names[7][5][3];
	std::string room_descriptions[7][5][3];
	std::string door_status[7][5][3];
	std::string room_instances[7][5][3];
	std::string room_items[7][5][3];
	std::string solo_use_items[7][5][3];
	std::string response_string;
	std::string interaction;

	bool puzzle_one_flag_one;
	bool puzzle_one_flag_two;
	bool puzzle_one_flag_three;
	bool puzzle_one_flag_four;
	bool puzzle_one_master;
	bool ladder_flag;
	bool flag_fuse_done;
	bool fire_flag;
	bool flag_gramophone;
	bool flag_toolkit;
	bool button_push;
	bool puzzle_piano_flag_master;
	bool puzzle_oil_flag_master;

	int piano_count;
	int oil_count;

protected:	
	unsigned char H_STRAIGHT_LINE;
	unsigned char V_STRAIGHT_LINE;
	unsigned char TOP_T;
	unsigned char TOP_LEFT;
	unsigned char TOP_RIGHT;
	unsigned char LEFT_T;
	unsigned char CROSS;
	unsigned char RIGHT_T;
	unsigned char BOTTOM_T;
	unsigned char BOTTOM_LEFT;
	unsigned char BOTTOM_RIGHT;
	unsigned char mini_map[7][5][3];

	int X_pos;
	int Y_pos;
	int Z_pos;	

	bool visited[7][5][3];

public:
	explicit gameWorld();
	//explicit~gameWorld();
	// VER 0.7
	void load_new_game_text_files();
	void load_gui_gfx();

	void build_room_name(std::ostream&);
	void build_room_description(std::ostream&);
	void build_game_interface(std::ostream&);
	void build_mini_map(std::ostream&);
	//
	void set_room_new_game();
	void set_room_visited();
	void set_response_string(std::string);
	void set_puzzle_flags();
	//
	int set_clear();
	int get_x_pos();
	int get_y_pos();
	int get_z_pos();
	//
	std::string get_response_string();
	std::string validate_pickup_string(int, int, std::string);
	std::string move_player(char);
	//
	int do_solo_use(std::string);
	int process_total_use_command(std::string, std::string);	
	std::string process_inspection_comamnd(std::string);


	void create_save_dir();

	void save_write(std::string);
	
	void load_gw_saved_game_files(std::string);

}; // EOF GAME WORLD CLASS HEADER 
#endif