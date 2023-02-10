# Minishell Readme

###  _EXECUTION_

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

### _cd_
_cd work if zero or one argument max, the argument must be a valid directory 
of error will be displayed. \
If used with other commands (inside pipes) doesn't do anything but still 
display error if more than one arg_ 

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
_Doesn't change the directory but if some arguments are wrong or if more 
than one argument while print an error._
- too many arguments error as the priority over No such file or directory,  
minishell isn't a directory but it's the second argument that trigger the error

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

