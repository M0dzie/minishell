##########     minishell tests     ##########


#####  test fork and execve  #####

##  test 1  ##
minishell $> foo
expected: $shell: command not found: $command  |  then give prompt back

##  test 2  ##
minishell $> /bin/ls
expected: command executed correctly  |  then give prompt back

##  test 3  ##
minishell $> /bin/ls -laF
expected: command executed correctly with the flags  |  then give prompt back

##  test 4  ##
minishell $> /bin/ls -l -a -F
expected: command executed correctly with the flags like test 4  |  then give prompt back

##  test 5  ##       same as test 2 with only command name
minishell $> ls
expected: command executed correctly  |  then give prompt back

##  test 6  ##       same as test 3 with only command name
minishell $> ls -laF
expected: command executed correctly with the flags  |  then give prompt back

##  test 7  ##       same as test 4 with only command name
minishell $> ls -l -a -F
expected: command executed correctly with the flags like test 4  |  then give prompt back



#####  test builtins  #####


###  echo  ###

##  test 1  ##       echo with double quote
minishell $> echo "It works"
expected: the message must be displayed  |  then give prompt back

##  test 2  ##       echo without quote
minishell $> echo It works
expected: the message must be displayed  |  then give prompt back

##  test 3  ##       echo with -n flag
minishell $> echo -n "Echo with -n flag"
expected: the message must be displayed without newline  |  then give prompt back at the same line


###  cd & pwd  ###

##  test 4  ##       absolute path
minishell $> cd /bin
minishell $> /bin/pwd
expected: must show the path of bin  |  then give prompt back

##  test 5  ##       same as test 4 with only command name
minishell $> cd /bin
minishell $> pwd
expected: must show the path of bin  |  then give prompt back

##  test 6  ##       relative path
minishell $> cd ../
minishell $> /bin/pwd
expected: must show the path above minishell directory  |  then give prompt back

##  test 7  ##       same as test 6 with only command name
minishell $> cd ../
minishell $> pwd
expected: must show the path above minishell directory  |  then give prompt back

##  test 8  ##       user home folder
minishell $> cd
minishell $> /bin/pwd
expected: must show the path of user home directory  |  then give prompt back

##  test 9  ##       same as test 8 with only command name
minishell $> cd
minishell $> pwd
expected: must show the path of user home directory  |  then give prompt back


##########  not sur if needed, have to test chdir  ##########

##  test 10  ##       user home folder
minishell $> cd -
minishell $> /bin/pwd
expected: must show the path above minishell  |  then give prompt back

##  test 11  ##       same as test 10 with only command name
minishell $> cd -
minishell $> pwd
expected: must show the path above minishell  |  then give prompt back

##  test 12  ##       user home folder
minishell $> cd ~/Documents
minishell $> /bin/pwd
expected: must show the path of documents folder  |  then give prompt back

##  test 13  ##       same as test 12 with only command name
minishell $> cd ~/Documents
minishell $> pwd
expected: must show the path of documents folder  |  then give prompt back


###  exit  ###

##  test 1  ##
minishell $> exit  then run minishell again
expected: program must terminate  |  then give back the parent shell



#####  test environnement management  #####

###  env  ###

##  test 1  ##
minishell $> env
expected: program must display environnement variables  |  then give prompt back

##  test 2  ##       echo USER
minishell $> echo $USER
expected: program must display the environnement variable USER  |  then give prompt back

##  test 3  ##       echo HOME
minishell $> echo $HOME
expected: program must display the environnement variable HOME  |  then give prompt back

##  test 4  ##       echo SHELL
minishell $> echo $SHELL
expected: program must display the environnement variable SHELL  |  then give prompt back


###  export  ###

##  test 1  ##       define new env variable
minishell $> export NEW_VARIABLE=mini
minishell $> env
expected: program must display environnement variables with NEW_VARIABLE=mini  |  then give prompt back

##  test 2  ##
minishell $> echo $NEW_VARIABLE
expected: program must display NEW_VARIABLE value (mini)  |  then give prompt back

##  test 3  ##       redefine NEW_VARIABLE env variable
minishell $> export NEW_VARIABLE=minishell
minishell $> env
expected: program must display environnement variables with NEW_VARIABLE=minishell  |  then give prompt back

##  test 4  ##
minishell $> echo $NEW_VARIABLE
expected: program must display NEW_VARIABLE value (minishell)  |  then give prompt back

##  test 5  ##       env with is path
minishell $> /usr/bin/env
expected: program must display environnement variables with NEW_VARIABLE=minishell like in test 3  |  then give prompt back


###  unset  ###

##  test 1  ##       unset NEW_VARIABLE env variable
minishell $> unset NEW_VARIABLE
minishell $> env
expected: program must display environnement variables without NEW_VARIABLE  |  then give prompt back

##  test 2  ##       run unset NEW_VARIABLE again
minishell $> unset NEW_VARIABLE
minishell $> env
expected: program must display environnement variables unchanged  |  then give prompt back

##  test 3  ##       run env again with is path
minishell $> /usr/bin/env
expected: program must display environnement variables still without NEW_VARIABLE  |  then give prompt back



#####  test path management  #####

##  test 1  ##       unset PATH  then  use ls
minishell $> unset PATH
minishell $> ls
expected: program must not be able to use ls  |  then give prompt back

##  test 2  ##       use ls with is path
minishell $> /bin/ls
expected: program must use /bin/ls correctly  |  then give prompt back

##  test 3  ##       define PATH again
minishell $> export PATH=/bin:/usr/bin
minishell $> ls
expected: program must use ls again correctly  |  then give prompt back



#####  test history  #####

##  test 1  ##       use up arrow input/key 7 time  then  use the command (env)
expected: program must be able to go back and show all cmd used before  |  then give prompt back

##  test 2  ##       use up arrow input/key ONE time  then  use the command (env)
expected: program should show last used cmd (env)  |  then give prompt back



#####  test search  #####       open a new prompt

##  test 1  ##       use ctrl-R and search an already used cmd (pwd)  then  enter for using the cmd
expected: program must let you search a used cmd and used it  |  then give prompt back, the search line must only display the command used

##  test 2  ##       use ctrl-R  then  use ctrl-C
expected: program must exit search prompt letting (reverse-i-search)`': ^C displayed   |  then give prompt back

##  test 3  ##       use ctrl-R write anything  then  use ctrl-C
expected: program must exit search prompt letting (reverse-i-search)`whatever you wrote': ^C displayed |  then give prompt back



#####  test interactive mode  #####

##  test 1  ##       ctrl-C signal
minishell $> ctrl-C input
expected: program must display ^C  |  then give prompt back
minishell $> ^C

##  test 2  ##       ctrl-D signal
minishell $> ctrl-D input
expected: program must exit the shell correctly and print exit  |  then give back the parent shell
minishell $>
exit
parent_shell $>

##  test 3  ##       ctrl-\ signal
minishell $> ctrl-\ input
expected: program must do nothing



##########    interrogations    ##########

Is mode interactif different than prompt or it's just the way to call shortcut in shell?

$? working?