# mks65p1 C-shell
## Bayan Berri & Brian Lim

### Features
* Forks and executes commands
* Parses multiple commands on one line
*
### Attempted

### Bugs

### Files & Function Headers
##### Shell.c

/**
 * @Function: split_line
 * @Params: char* line, char * character,char* split_input, char** retans
 * @Returns: char**
 * @Explanation: splits the line at the character. If multiple occurrences each will be a token in retans.
 */

/**
 * @Function: replace_str
 * @Params: char* line, char* substring, char* replace_with
 * @Returns: Nothing
 * @Explanation: replaces the substring with replace_with. Used for if user surrounds semicolon with spaces.
 */

/**
 * @Function: execute
 * @Params: char** parsed_line
 * @Returns: Nothing
 * @Explanation: forks, parent waits for child to execute parsed_line
 */

/**
 * @Function: cd
 * @Params: char ** parsed_line
 * @Returns: nothing
 * @Explanation: change directory function, includes cd with no param and cd ~ as well
 */

/**
 * @Function: run_the_shell
 * @Params: char* command_input, char* split_input, char** cmd
 * @Returns: char **
 * @Explanation: gets user input, replaces "\n" with 0 after fgets, and uses replace_Str and split_line to populate cmd.
 */

/**
 * @Function: check_exit
 * @Params: char * token
 * @Returns: Nothing
 * @Explanation: if the token is "exit" exit the program
 */

/**
 * @Function: print_dir
 * @Params: None
 * @Returns: None
 * @Explanation: Prints the prompt using current working directory
 */


/**
 * @Function: print_dir
 * @Params: None
 * @Returns: None
 * @Explanation: Prints the prompt using current working directory
 */
