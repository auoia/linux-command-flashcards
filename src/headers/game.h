#ifndef MENU_H 
#define MENU_H

#include <iostream>
#include <cstring>
#include <ctime>
#include <sstream>
#include <algorithm>
#include "list.h"

#include <string>
#include <fstream>


#define NULL_STR "\0"

/* The actual maximum number of profiles is 
 * MAX_PROFILES/2 because the profile array holds two data
 * but it is a 1-dimensional array.
 */
#define MAX_PROFILES 100
/* files macro */
#define COMMANDS_CSV_FILE "../commands.csv"
#define PROFILES_CSV_FILE "../profiles.csv"

/* menu macro */
#define RULES 1
#define PLAY 2
#define LOAD_PREV 3
#define ADD_CMD 4
#define RM_CMD 5
#define EXIT 6


class Game {
private:

public:
    List<std::string, std::string> cmdlist;
    std::string profiles[MAX_PROFILES];

    void run(void);

    bool shift_right(std::string instr[], int arr_s);
    bool exists_in_array(int arr[], int n, int size_a);
    void g_unique_int(int arr[], int modulus, int size_a);
    void pause(void);
    int random(void);

    void load_commands_csv(void);
    void load_profiles_csv(void);
    int find_profile(std::string username);
    void load_profile(void);

    void add_command(void);
    void rm_command(void);
    void rules_menu(void);
    void main_menu(void);
    void play_helper(bool loaded, int index);
    void play(std::string username, int num_games, int profile_index);

    void save_profiles(void);
    void save_commands(void);
};

#endif