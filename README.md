# C-shell
## Bayan Berri & Brian Lim

### Features
* Forks and executes commands
* Parses multiple commands on one line
* cd implementation cd alone or followed by a tilde takes you home
* Simple redirection using <, > and |
* Complex redirection (redirecting more than once)

### Attempted
* Tried to have ~ replace the beginning of the working directory

### Bugs
* spiders, crickets, roaches

### Files & Function Headers
##### Shell.c

/**  
 \* @Function: split_line  
 \* @Params: char* line, char * character,char* split_input, char** retans  
 \* @Returns: char**  
 \* @Explanation: splits the line at the character. If multiple occurrences each will be a token in retans.  
 */

/**  
 \* @Function: replace_str  
 \* @Params: char* line, char* substring, char* replace_with  
 \* @Returns: Nothing  
 \* @Explanation: replaces the substring with replace_with. Used for if user surrounds semicolon with spaces.  
 */

/**  
 \* @Function: execute  
 \* @Params: char** parsed_line  
 \* @Returns: Nothing  
 \* @Explanation: forks, parent waits for child to execute parsed_line  
 */

/**  
 \* @Function: cd  
 \* @Params: char ** parsed_line  
 \* @Returns: nothing  
 \* @Explanation: change directory function, includes cd with no param and cd ~ as well  
 */

/**  
 \* @Function: run_the_shell  
 \* @Params: char* command_input, char* split_input, char** cmd  
 \* @Returns: char **  
 \* @Explanation: gets user input, replaces "\n" with 0 after fgets, and uses replace_Str and split_line to populate cmd.  
 */

/**  
 \* @Function: check_exit  
 \* @Params: char * token  
 \* @Returns: Nothing  
 \* @Explanation: if the token is "exit" exit the program  
 */

/**  
 \* @Function: print_dir  
 \* @Params: None  
 \* @Returns: None  
 \* @Explanation: Prints the prompt using current working directory  
 */

/**  
 \* @Function: locate_redirect  
 \* @Params: char ** parsed_line  
 \* @Returns: int red_index  
 \* @Explanation: It searches through the parsed line to find the index of <, > or |  
 */

/**  
 \* @Function: locate_symbol  
 \* @Params: char ** parsed_line, char * symbol  
 \* @Returns: int red_index  
 \* @Explanation: Similar to locate_redirect but it specifies the symbol.  
 */

/**  
 \* @Function: zero  
 \* @Params: char ** parsed_line, int redirection  
 \* @Returns: void  
 \* @Explanation:This function zeros out everything except for the command in parsed_line  
 */

/**  
 \* @Function: exec  
 \* @Params: int forked, char ** parsed_line  
 \* @Returns: None  
 \* @Explanation: This is super similar to execute except it's takes an int as a parameter so that we can implement modular design and make our functions shorter.  
 */

/**  
 \* @Function: redirect  
 \* @Params: char ** parsed line  
 \* @Returns: None  
 \* @Explanation: Uses modular design( locate_redirect, locate_symbol, zero, and exec) so that redirection and multiple redirection can work.  
 */
