# Custom C Shell

## Chekkapalli Naveen | 2021101025

---

## Requirements

- GCC compiler
- Linux OS (preferably Ubuntu)
- Even works with mac (except pinfo)

## Running Shell

From the root directory of project, run `make` followed by `./shell`

## File & Functions

### Supporting Files

##### Files containing functions required for proper functioning of the shell.

- `shell.c`

  - Run Shell Loop

  - Checks for terminated child processes

  - Maps shared memory to the global variables

  - Bind functions from different files together

- `prompt.c`

  - Print prompt

  - Checks for current working directory

- `exec.c`

  - Takes input from user

  - Stores the input in history.txt file

  - Tokenize input to separate commands

  - Stores the child processes

  - Runs command in foreground or background

- `history.c`

  - Adds command to history

  - Stores maximum 20 commands

### Command Files

##### Files containing functions to run a particular command.

- `bg.c`

  - Stores the background processes' information

  - checks and prints the background processes which have completed execution

- `pwd.c`

  - Prints the working directory

- `echo.c`

  - Prints user input after removing excess spaces/tabs

- `cd.c`

  - Navigate to different directories

- `ls.c`

  - Prints all files/sub-directories in a location

  - Flags implemented: `a` and `l`

  - Multiple directories, files are supported

- `pinfo.c`

  - Prints info about process with given PID (current process if none is given)

- `history.c`

  - Prints last 10 commands

- `discover.c`

  - searches for the given file or folder and prints the paths to the respective files

  - Flags implemented: `d` and `f`

  - directory and file are supported

  - Multiple directories, files are not supported

### Other Implementations

##### Commands/functions which don't have a separate file.

- Exiting from the Shell

  - `exit` command.

## Assumptions

- Reasonable assumptions are made for things like length of current path, number of commands, command length, etc. The shell will work perfectly for all "day to day work". (all the lengths maximum is taken as 1024 `(MAXLEN)`)

- `user` and `hostname` will be constant throughout the life of current shell instance.

- `echo` will treat everything as normal character and will treat space separated strings as a single string even when they are not enclosed in quotes.

- File and directory names shouldn't contain spaces or special characters.

- `pinfo` may break on systems not running Ubuntu. This command uses `/proc` files which may not be same for other OS (for example macOS).

- Every user input will be stored as it is in history, given it is not same as the last input and contains at least one character other than space or tab.

- Prompt will check exist status of background processes only after user inputs a command (possibly empty). The same happens in actual Bash shell.

- In `discover` multiple directories or files are not supported and only a single directory and file are supported.

- `&` (used for running process in background) can come anywhere in command.

- A file (`history.txt`) is used to store history in a readable format. Any changes explicitly done in this file may result in unexpected output of `history` command.