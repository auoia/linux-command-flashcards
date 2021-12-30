#include "game.h"


void Game::run(void) {
    // seed time for pseudorandom number generator
    std::srand(std::time(nullptr));

    load_commands_csv();
    load_profiles_csv();
    
    main_menu();
}

/*
 * shift_right() is a helper function for load_profiles() to implement
 * the "insert at front of array" requirement of Assignment 1
 */
bool Game::shift_right(std::string instr[], int arr_s) {
	bool success = 0;
	// if the first element is null, do not shift
	if (instr[0] == NULL_STR) {
		success = 0;
	} else {
		int size_str = 0;
		while(instr[size_str] != NULL_STR) {
			size_str++;
		}
		// if array is full, do not shift
		if (size_str >= arr_s) {
			success = 0;
		} else {
			std::string tmp[size_str];
			for (int i=0; i < size_str; i++) {
				tmp[i] = instr[i];
			}
			
			instr[0] = NULL_STR;

			for (int i=0; i<size_str; i++) {
				instr[i+1] = tmp[i];
			}
			success = 1;
		}
	}

	return success;
}

/* Determine if integer n is in an array
 */
bool Game::exists_in_array(int arr[], int n, int size_a) {
    int i = 0;
    bool exist = 0;
    while ((i < size_a) && !exist) {
        if (n == arr[i]) {
            exist = 1;
        }
        i++;
    }

    return exist;
}

/* Generate unique size_a unique integers and store it in arr[]
 *
 */
void Game::g_unique_int(int arr[], int modulus, int size_a) {

    for (int i =0; i<size_a; i++) {
        arr[i] = -1;
    }

    int random = 0;

    random = rand() % modulus;
    int i = 0;
    while (i < size_a) {
        while (exists_in_array(arr, random, size_a)) {
            random = rand() % modulus;
        }
        arr[i] = random;
        i++;
    }
}

void Game::pause(void) {
    std::cout << "(press ENTER to continue)";
    std::cin.ignore();
}

// Generate random numbers up to the size of the linked list
// to cover all linux commands
int Game::random(void) {
    return rand() % cmdlist.size();
}

void Game::load_commands_csv(void) {
    std::ifstream infile;

    infile.open(COMMANDS_CSV_FILE);

    /*
     * This is modified from https://stackoverflow.com/a/19936571, which
     * (1) Read lines from a csv file, then
     * (2) "tokenize" it using the delimiter ','
     * But because the second loop gives two tokens, we use an array of 
     * std::string to capture those tokens.
     */
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream strstream(line);
        std::string token;

        std::string fields[2] = {"\0"};
        int i = 0;
        while(getline(strstream, token, ',')) {
            fields[i] = token;
            i++;
        }
        cmdlist.insert(fields[0], fields[1]);
    }

    infile.close();
}

/*
 * From Assignment 1 requirements, profiles in profiles.csv are loaded to an array
 * at the front of the array. So we employ shift_right() to first shift elements
 * in the array to the right, then we insert fields[i] to array[0].
 * Profile elements (name,points) are stored in a one-dimensional std::string array,
 * the points will be converted to integer using std::stoi()
 */
void Game::load_profiles_csv(void) {
    std::ifstream infile;

    infile.open(PROFILES_CSV_FILE);

    /*
     * This is modified from https://stackoverflow.com/a/19936571
     */
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream strstream(line);
        std::string token;

        std::string fields[2] = {"\0"};
        int i = 0;
        while(getline(strstream, token, ',')) {
            fields[i] = token;
            i++;
        }
        
        shift_right(profiles, MAX_PROFILES);
        profiles[0] = fields[0];
        shift_right(profiles, MAX_PROFILES);
        profiles[0] = fields[1];
    }
    infile.close();
}

/* find_profile() returns the index of the profile in the profiles array
 * if the profile does not exist, it returns 0
 */
int Game::find_profile(std::string username) {
    int index=0;

    while (profiles[index] != username && profiles[index] != NULL_STR) {
        //index++;
        index++;
    }

    if (profiles[index] == username) {
        return index;
    } else {
        return 0;
    }
}

void Game::load_profile(void) {
    std::cout   << "***********************************************************\n"
                << "*                   Load Previous Game                    *\n"
                << "*                   ==================                    *\n"
                << "*  Enter the username of the profile to load              *\n"
                << "***********************************************************\n"
                << std::endl;
    
    std::string u_input = NULL_STR;

    while (u_input.compare(NULL_STR) == 0) {
        std::cout << "(load previous game) >> ";
        std::getline(std::cin, u_input);
        if (u_input.compare(NULL_STR) == 0) {
            std::cout << "Error: username cannot be empty" << std::endl;
        }
    }

    int index = 0;
    index = find_profile(u_input);

    if (index != 0) {
        play_helper(true, index);
    } else {
        std::cout << "Failed to find profile" << std::endl;
    }
}

void Game::add_command(void) {
    
    std::string cmd = NULL_STR;
    std::string description = NULL_STR;
    
    while (cmd.compare("q") != 0) {
        std::cout   << "***********************************************************\n"
                    << "*                     Add Commands                        *\n"
                    << "*                     ============                        *\n"
                    << "*  Add only the base *nix commands, no switches or args.  *\n"
                    << "*  Any commas in the description will be removed to san-  *\n"
                    << "*  itize the cmdlist.csv file.                            *\n"
                    << "*  To quit, type 'q'.                                     *\n"
                    << "***********************************************************\n"
                    << std::endl;

        std::cout << "(add command) >> ";
        std::getline(std::cin, cmd);

        if (cmd.compare("q") != 0) {
            std::cout << "(enter a brief description)>> ";
            std::getline(std::cin, description);

            // CSV files are sensitive to commas, so we
            // sanitize cmd and description for commas
            // This elegant solution in STL was found on https://stackoverflow.com/a/20326454
            cmd.erase(std::remove(cmd.begin(), cmd.end(), ','), cmd.end());
            description.erase(std::remove(description.begin(), description.end(), ','), description.end());

            // put quotes around description
            std::string tmp = "\"";
            tmp = tmp.append(description);
            description = tmp.append("\"");

            bool success = 0;
            success = cmdlist.insert(cmd, description);

            if (success) {
                std::cout << "Successfully added `" << cmd << "` as a new command" << std::endl;
                pause();
            } else {
                std::cout << "Fail: command already exists, try again..." << std::endl;
                pause();
            }
        }
    }

    pause();
}

void Game::rm_command(void) {
    std::cout   << "***********************************************************\n"
                << "*                    Remove Commands                      *\n"
                << "*                    ===============                      *\n"
                << "*  Remove command by command name only.                   *\n"
                << "*  Enter only the command name, e.g `ls` or `awk`         *\n"
                << "***********************************************************\n"
                << std::endl;

    std::string cmd;
    std::cout << "(remove command) >> ";
    std::getline(std::cin, cmd);

    bool success = 0;

    success = cmdlist.remove(cmd);
    if(success) {
        std::cout << "Success: `" << cmd << "` was removed from the list." << std::endl;
    } else {
        std::cout << "Fail: Did not find `" << cmd << "` in the commands list." << std::endl;
    }
    pause();
}

void Game::rules_menu(void) {
    std::cout   << "************************************************************\n"
                << "*                       Game Rules                         *\n"
                << "*                       ==========                         *\n"
                << "*  You will be matching linux commands to the right desc-  *\n"
                << "*  ription. If you match the command to the right descri-  *\n"
                << "*  ption, you score +1 point. However, a wrong match will  *\n"
                << "*  score you -1 point.                                     *\n"
                << "*                                                          *\n"
                << "*  Hint: this says nothing about not answering the ques-   *\n"
                << "*        tion. Sometimes, the right move is making no mo-  *\n"
                << "*        ve at all.                                        *\n"
                << "*                                                          *\n"
                << "*  Selecting `Play New Game` will create a new profile or  *\n"
                << "*  overwrite a previously saved profile.                   *\n"
                << "*  To prevent your progress from being overwritten, use    *\n"
                << "*  `Load Previous Game` instead.                           *\n"
                << "*                                                          *\n"
                << "*  You may add new commands that already does not exist    *\n"
                << "*  or remove a command that does exist. If you try adding  *\n"
                << "*  a command that already exists, you will be prompted f-  *\n"
                << "*  or a new command.                                       *\n"
                << "*                                                          *\n"
                << "*  Good luck!                                              *\n"
                << "************************************************************\n"
                << std::endl;
    pause();
}

void Game::main_menu(void) {        
    // std::string u_input;
    // unsigned int choice;
    // std::getline(std::cin, u_input);
    // choice = std::stoi(u_input);
    unsigned int choice = 0;

    while (choice != EXIT) {

        std::cout   << "***********************************************************\n"
                    << "*                       Main Menu                         *\n"
                    << "*                       =========                         *\n"
                    << "*  Make a selection from the following:                   *\n"
                    << "*     1. Display Rules                                    *\n"
                    << "*     2. Play New Game                                    *\n"
                    << "*     3. Load Previous Game                               *\n"
                    << "*     4. Add New Command                                  *\n"
                    << "*     5. Remove a Command                                 *\n"
                    << "*     6. Save and Exit                                    *\n"
                    << "***********************************************************\n"
                    << std::endl;

        std::cout << "(menu selection) >> ";

        std::string u_input;
        std::getline(std::cin, u_input);
        
        // No sanitation is done on user input, but we
        // reject all unless it is within the bounds of 1-6
        try {
            choice = std::stoi(u_input);

            if(choice < RULES || choice > EXIT) 
                throw choice;

            switch (choice) {
                case RULES: 
                    rules_menu();
                    break;
                case PLAY:
                    play_helper(false, 0);
                    break;
                case LOAD_PREV:
                    load_profile();
                    break;
                case ADD_CMD:
                    add_command();
                    break;
                case RM_CMD:
                    rm_command();
                    break;
                case EXIT:
                    std::cout << "Saving and quiting" << std::endl;
                    save_profiles();
                    save_commands();
                    break;
                default:
                    main_menu();
            }
        } catch (std::invalid_argument const&){
            std::cout << "Invalid choice: must be [1-6]" << std::endl;
        } catch (unsigned int num) {
            std::cout << num << " is out of bounds [1-6]" << std::endl;
        } catch (std::out_of_range const&) {
            std::cout << "Input is out of bounds [1-6]" << std::endl;
        }
    }
}

/* play_helper() is a helper function for play that sets up a user's username,
 * and determines the number of games to play
 */
void Game::play_helper(bool loaded, int index) {
    std::string username = NULL_STR;
    int profile_index = 0;
    bool success = 0;

    if (!loaded) {
        std::cout       << "***********************************************************\n"
                        << "*                       Play New Game                     *\n"
                        << "*                       =============                     *\n"
                        << "*  Follow the instructions below.                         *\n"
                        << "***********************************************************\n"
                        << std::endl;

        while (username.compare(NULL_STR) == 0) {
            std::cout << "(enter a username) >> ";
            std::getline(std::cin, username);
            
            if (username.compare(NULL_STR) == 0) {
                std::cout << "Error: username cannot be empty" << std::endl;
            }
        }

        profile_index = find_profile(username);
        if(profile_index == 0) {
            std::cout << "Using new profile `" << username << "`" << std::endl;
            profile_index = 1;
        } else {
            std::cout << "Will be overwriting existing profile `" << username << "`" << std::endl;
            profiles[profile_index-1] = NULL_STR;
            profiles[profile_index] = NULL_STR;
        }
        std::string init_score = "0";
        // Create new profiles in the array
        shift_right(profiles, MAX_PROFILES);
        profiles[0] = username;
        shift_right(profiles, MAX_PROFILES);
        profiles[0] = init_score;
        success = 1;
    } else {
        profile_index = index;
        username = profiles[index];
        success = 1;
    }
    
    if (success) {
        int num_games;
        std::string input_games;
        std::cout << "(enter number of rounds [5-30]) >> ";
        std::getline(std::cin, input_games);

        try {
            num_games = std::stoi(input_games);

            if(num_games > 30 || num_games < 5)
                throw num_games;
            // Start game
            play(username, num_games, profile_index);
        } catch (std::invalid_argument const&){
                std::cout << "Invalid input" << std::endl;
        } catch (int num) {
            std::cout << "Please make a selection between 5-30 rounds" << std::endl;
        } catch (std::out_of_range const&) {
            std::cout << "Please make a selection between 5-30 rounds" << std::endl;
        }
    }
}


void  Game::play(std::string username, int num_games, int profile_index) {
    // start game
    std::string u_input;
    int question = -1;
    int asked[num_games]; // asked[] keeps track of questions that have already been asked
    int distractor[2];
    std::string str_score = profiles[profile_index - 1];
    int i_score = std::stoi(str_score);
    int round_score = 0;

    // initialize the asked array to -1
    for (int i=0; i<num_games; i++) {
        asked[i] = -1;
    }


    int i=0;
    while (i < num_games) {
        question = random();
        bool repeated = exists_in_array(asked, question, num_games);
        while (repeated) {
            question = random();
            repeated = exists_in_array(asked, question, num_games);
            //std::cout << question << "\n";
        }
        asked[i] = question;
        distractor[0] = random();
        distractor[1] = random();

        /* Distractor descriptions should not be duplicates, and should not
        * be a duplicate of the question's real description
        */
        while (distractor[0] == distractor[1] 
                || distractor[1] == question
                || distractor[0] == question) {
            distractor[0] = random();
            distractor[1] = random();
        }
        
        // We use a three element integer array to 
        // shuffle the order that possible answers are displayed
        int answers[3];
        answers[0] = distractor[0];
        answers[1] = distractor[1];
        answers[2] = question;

        std::cout   << "`"
                    << cmdlist.data1_by_index(question)
                    << "`";

        int unique[3];
        g_unique_int(unique, 3, 3);

        int key = 0;
        for(int k=1; k<=3; k++) {
            std::cout   << "\t" 
                        << k << ". "  
                        << cmdlist.data2_by_index(answers[unique[k-1]])
                        << std::endl;
            if (answers[unique[k-1]] == question)
                key = k;
        }

        std::cout   << "(" << i+1 << "/" << num_games << ")" << "(answer) >> ";

        int player_answer = 0;
        std::getline(std::cin, u_input);

        i++;

        try {
            player_answer = std::stoi(u_input);
            if(player_answer == key) {
                std::cout << "[+] Correct! +1 point" << std::endl;
                round_score++;
            } else {
                std::cout << "[-] Wrong! -1 point" << std::endl;
                round_score--;
            }

        } catch (std::invalid_argument const&){
            std::cout << "Please make a selection between 1-3" << std::endl;
        } catch (int num) {
            std::cout << "Please make a selection between 1-3" << std::endl;
        } catch (std::out_of_range const&) {
            std::cout << "Please make a selection between 1-3" << std::endl;
        }
    }
    std::cout << "Congrats, your total points this round is: " << round_score << std::endl;
    std::cout << "Total points: " << round_score + i_score << std::endl;

    str_score = std::to_string(round_score + i_score);
    profiles[profile_index - 1] = str_score;

    pause();
}

/* Funny thing, load_profile_csv loads the file at the front of the list,
 * but save_profiles() also saves to file starting from the front of the list.
 * So the end result is that the profiles are saved in reverse
 * every time the program is ran then quit. lol
 */ 
void Game::save_profiles(void) {
    std::ofstream outfile;
    outfile.open(PROFILES_CSV_FILE);

    int i = 0;
    while (i < MAX_PROFILES-1 && profiles[i] != NULL_STR) {
        outfile << profiles[i+1] 
                << "," 
                << profiles[i] 
                << std::endl;

        i = i + 2;
    }
    outfile.close();
}

/* Save to file
 */
void Game::save_commands(void) {
    std::ofstream outfile;
    outfile.open(COMMANDS_CSV_FILE);

    int list_size = cmdlist.size() - 1;

    while (list_size >= 0) {
        outfile << cmdlist.data1_by_index(list_size) 
                << "," 
                << cmdlist.data2_by_index(list_size) 
                << std::endl;
        list_size--;
    }

    outfile.close();
}