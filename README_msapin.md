# **Minishell - Readme**


#  _EXECUTION_
_I will divide each command line into "block" of tokens.
a block can be compose of multiples token :_
- one command (optional)
- arguments (optional)
- one or multiple inputs (optional)
- one or multiple outputs (optional)

_A block is all characters between pipe_

```
minishell $> ls -la | wc < README -l | sleep 3 | env > fileout
            cmd arg  cmd   input  arg   cmd arg  cmd    redir
```

_If one element in the block is invalid nothing is execute, but
an error message is displayed corresponding of the first error
encounter_

#  _BUILTINS_


## _echo_
_echo accept an infinity of arguments, that can be with or 
without quotes._
```
bash $> echo hello world!
hello world!
```

```
bash $> echo "hello world!"
hello world!
```

_That can also be a mix of arguments with and without quotes._
```
bash $> echo hello "world!"
hello world!
```
```
bash $> echo "hel"lo "world"!
hello world!
```
_Quotes are ignored/removed from the sentence if correctly closed._


### Difference SIMPLE and DOUBLE quotes (strong vs weak)?
_- We can put environment variables inside double quotes_
```
bash $> echo "$PATH"
/home/username/.local/bin:home/username/...
```

_- But simple quotes will just display the word inside even write as a ENV variable_
```
bash $> echo '$PATH'
$PATH
```

_It's look like simple quotes block special character to be used as special character
instead it will be print as a normal character._
```
bash $> echo '$PATH'
$PATH
```

__For minishell double quotes will also block special characters 
except $__

#

### SPECIAL CHARACTERS:
- ~
- `
- \#
- $
- &
- \*
- (
- )
- \
- |
- [
- ]
- {
- }
- ;
- '
- "
- <
- \>
- /
- ?
- !

#

__IMPORTANT in bash double quotes let some special character have an
effect to the shell, example : echo " ` " will open prompt__  
_In MINISHELL we don't have to handle these special character expect $_

### _Double quotes :_

_Inside double quotes we can write every characters or specials character
they will be displayed as a normal char._  

_There are two exception:_
- "  a double quotes inside two double quotes will open prompt, it
will not be valid in minishell
- $ the dollar sign will be display if alone but before a word
it will be remplace by the ENV variable with the same name

```
minishell $> echo "~ ` # $ & * ( ) \ | [ ] { } ; ' < > / ? !"
~ ` # $ & * ( ) \ | [ ] { } ; ' < > / ? !
```

```
minishell $> echo "$PATH"
home/username/.local/bin:/home/username/.local/bin:...
```

_If environmental var doesn't exist will not print anything_
```
minishell $> echo "$NON_EXISTING_VAR"
minishell $>
```

### _Simple quotes :_

_Inside simple quote we can write every characters or specials character
they will be displayed as a normal char._  

_There are one exception:_
- '  a simple quotes inside two simple quote will open prompt, it
will not be valid in minishell

```
minishell $> echo '~ ` # $ & * ( ) \ | [ ] { } ; " < > / ? !'
~ ` # $ & * ( ) \ | [ ] { } ; " < > / ? !
```

```
minishell $> echo '$PATH'
$PATH
```

### _STRATEGY for PARSING_

_For double quotes, if special character found in it we should split
it from the sentence and put it as argument between simple quote_

```
bash $> echo "Hello World!"
bash $> echo "Hello World"'!'

c
char    **arg_cmd = {"Hello World", "'!'"}
```




## _echo -n flag_

_The -n flag print without newline at the end._
```
bash $> echo -n Hello World!
Hello World!bash $>
```
_Give prompt back at the same line as the echo._



## _cd_

__It will not change directory if use in a pipe with 
other command, need to be executed alone to do something.__


_cd work if zero or one argument max, the argument must be 
a valid directory or error will be displayed. \
If used with other commands (inside pipes) doesn't change 
the directory but still display error if more than one arg 
or if invalid path._ 

`bash $> cd`  
_Go to root or user home directory._

#

`bash $> cd ~/Documents`  
_Go to the directory "Documents"._

#

```
bash $> cd ~/Documents second_arg
bash: cd: too many arguments
```
_Display error message._

#

```
bash $> cd | cd ~/Documents/ | cd ~/Documents/cursus | cd ~/Documents/cursus/minishell
```
_Doesn't change the directory._

#

```
bash $> cd | cd ~/Documents/ | cd cursus | cd minishell second_arg
bash: cd: cursus/: No such file or directory
bash: cd: too many arguments
```
_Doesn't change the directory but if some arguments are invalid 
(folder that doesnt exist) or if more than one argument while 
print an error._
- too many arguments error as the priority over No such file 
or directory, minishell isn't a valid directory but it's the 
second argument that trigger the error.

#

```
bash $> cd | pwd
/home/user/current/directory
```
_Execute all command but display the last one._

#

```
bash $> cd | pwd | cd
```
_Doesn't print anything and doesn't change directory._


## _pwd_
_pwd ignore all arguments:_
```
bash $> pwd arg1 agr2 agr3 ...
/home/mehdisapin/Documents/cursus/minishell
```

_display the directory same as pwd alone:_
```
bash $> pwd
/home/mehdisapin/Documents/cursus/minishell
```


## _export_

__Like cd it will not export anything if use in a pipe with 
other command, need to be executed alone to do something.__

_Can be used without arguments, it will print all already 
declared variables._
```
bash $> export
declare -x SHELL="/bin/bash"
declare -x PATH="/home/username/.local/bin:home/username/..."
...
```

_If we try to export variable without assigning value it will 
not export anything._
```
bash $> export TEST
bash $> env | grep TEST
bash $>
```

_We can export anything as long as we use "="_
```
bash $> export TEST=value
bash $> env | grep TEST
TEST=value
```

_Possibility to export multiples variables._
```
bash $> export TEST1=value1 TEST2=value2 test3=VALUE3
bash $> env
...
TEST1=value1
TEST2=value2
test3=VALUE3
```
_Uppercases doesn't matter but in practice variables are 
named in uppercase._

#

_It's possible to reassign an other value to an already declared 
variable._
```
bash $> export TEST1=reassign_1 TEST1=reassign_2 TEST1=reassign_3
bash $> env
...
TEST1=reassign_3
```


## _unset_

__Like cd or export it will not unset anything if use in a pipe 
with other command, need to be executed alone to do something.__

_If use without arguments or if the variable doesn't exist 
doesn't do anything._
```
bash $> unset
bash $> unset UNSET_VAR
bash $>
```

_Will unset the variable if existing and give the prompt back._
```
bash $> unset PATH
bash $>
```


## _env_

_Print environmental variables if use without argument, can be 
use in pipe with other commands._
```
bash $> env
...
SHELL=/bin/bash
PATH=/home/username/.local/bin:home/username/...
```

_If use with argument, env will try to access the argument as
a file or directory and display an error even if the file exist, 
for directory it will display an error about permission_
```
bash $> env non_existing_file
env: 'non_existing_file': No such file or directory
bash $> env existing_file
env: 'existing_file': No such file or directory
bash $> env non_existing_folder/
env: 'non_existing_folder': No such file or directory
bash $> env existing_folder/
env: 'existing_folder': Permission denied
```

_If multiples arguments, it will only try to access the first one._
```
bash $> env existing_file existing_folder/
env: 'existing_file': No such file or directory
```


## _exit_

__Like cd, export or unset it will not exit if use in a pipe 
with other command, need to be executed alone to do something 
(exit minishell).__

```
bash $> pwd | exit
bash $>
bash $> exit | wc
    0   0   0
bash $> exit
exit
parent_shell $>
```


# _REDIRECTIONS_

## _<_

_When "<" used will take the file specified at its right as the 
standard input for the command specified after or before it._
```
bash $> < readme wc
    4   20  165
bash $> wc < readme
    4   20  165
```

_It's seems like < file is open and put as standard input but 
doesn't impact the command add to the input._
```
bash $> wc < readme -l
    4
```
same as
```
bash $> cat readme | wc -l
    4
```

_"< readme" is extract from the line, so the remaining: wc -l
is execute with as standard input the content of the file._

#

_If the file doesn't exist will display an error and will not 
execute the command._
```
bash $> wc < invalid_file -l
bash: invalid_file: No such file or directory
```


## _>_

_When ">" used will take the file specified at its right as the 
standard output. If the file doesn't exist, it will be created.
Otherwise will truncated all content._
```
bash $> > new_file
```

_If the name of the file contain an invalid folder. An error 
message will be displayed._
```
bash $> > invalid_folder/new_file
bash: invalid_folder/new_file: No such file or directory
```

#

__Same as "<", "> new_file" seems to be ignored and remove from the input so 
it doesn't interfere with the command.__
```
bash $> ls > new_file -la
```
_Will write the result of ls -la into the file "new_file"._

#

_It need at least one command to be able to write something in the 
file._
```
bash $> > new_file
// will just create or erase the content of the file
bash $> ls > new_file
// will write the return of ls into the file
bash $> ls | wc > new_file
// will write the return of "wc" from "ls" into the file
bash $> ls | > new_file
// will write nothing into the file, just created it or erased the 
content

```


__Bug found with "wc" and "> new_file"__
```
bash $> wc > new_file

```
_It just open the prompt like with cat and wait for something._


## _<<_

_Open a new prompt and read the input until it match the delimiter
specified at is right._
```
bash $> << DELIMITER
> new
> input
> DELIMITER
bash $>
```

__Same as "<" and ">", "<<" seems to be ignored and remove from 
the input so it doesn't interfere with the command.__
```
bash $> wc << DELIMITER -l
> new
> input
> DELIMITER
2
bash $>
```

_Can be use with other command with the use of pipes._
```
bash $> grep input << DELIMITER | wc
> new
> input
> DELIMITER
    1   1   6
bash $>
```


## _>>_

_Like "> new_file" but will not truncated the file just add 
standard output (append) into it or doesn't do anything if no
standard output._


## _MIX of < / > / << / >>_
```
bash $> ls >> new_file | ls >> new_file | < new_file wc
    12   12   94
```
_ls is append into new_file, two time. And finally new_file is 
used as standard input for wc. The total of line, word and 
characters is than display and new_file will contain two time 
the result of ls_

#

```
bash $> ls >> new_file | ls > new_file | < new_file wc
    6   6   47
```
_In this example ls is first append but the second time new_file 
is used as standard input and truncated. So new_file will contain
only one ls. Displayed the total of line, word and characters 
and new_file will contain the result of ls_



### 46 shell Commands

`ls`  
_list content of the directory_

`alias`  
_set temporary alias in shell session_

`unalias`  
_unset temporary alias in shell session_

`pwd`  
_print absolute path of working directory_

`cd`  
_change directory_

`cp`  
_copy files or directories with -r flag (recursive)_

`rm`  
_remove files or directories, if file inside use -rf flags_

`mv`  
_move files or directories_

`mkdir`  
_create directory, use -p flag to create subdirectories_

`man`  
_displays manual_

`touch`  
_update the access and modification times of a file, use -m to change modification date to current time_

`chmod`  
_change the mode of a file (permission)_

`exit`  
_end a shell session_

`sudo`  
_let you act as a superuser or root user_

`shutdown`  
_power off your computer, use now to do that immediately otherwise default time is one minute_

`htop`  
_is an interactive process viewer_

`zip`
_zip files into an archive_

`unzip`
_extract the content of a .zip file_

`apt, yum, pacman`  
_let you install, update and remove software/packages_

`echo`  
_display text in the terminal_

`cat`  
_let you create, view and concatenate files_

`ps`  
show processes running in your current shell session_

`kill`  
_force close a program, use the name or the pid of the program as argument_

`ping`  
_use to test network connectivity_

`vim`  
_let you use Vim_

`history`  
_displays an enumerated list of commands used in the past_

`passwd`  
_allows you to change the password of user accounts_

`which`  
_outputs full path of the shell commands_

`shred`  
_overrides the contents of a file repeatdly to make it extremely difficult to recover_

`less`  
_let you inspect files backward and forward_

`tail`  
_similar to cat, tail prints last line (10 last lines by default) use -n flags to define an other number_

`head`  
_inverse of tail prints first lines (10 first lines by default) use -n flags to define an other number_

`grep`  
_search for line that match a regular expression and print them_

`whoami`  
_display the username same as echo $USER_

`whatis`  
_prints a single-line description of any other command_

`wc`  
_return the number of words in a text file_

`uname`  
_prints the operative system, use -a flag for more information_

`find`  
_search for files in a directory, find [flags] [path] -name [expression]_

`wget`  
_utility that let you retrieve content from the internet, wget [url]_

`clear`  
_clear the terminal display_

`diff`  
_find the difference between two files_

`cmp`  
_check if two files are identical_

`comm`  
_diff and cmp in one command_

`export`  
_export environment variables_

`whereis`  
_locate the binary, source and manual pages for a command_

`df`  
_display disk filesystem information_

