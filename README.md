# minishell

## Need change

```sh
echo bonjour 1> "$PATHH"
```
error `minishell: ': Permission denied` should be `No such file or directory`

## For leaks
Use this `command`
```sh
valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell
```
