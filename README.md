# minishell

## Need change

Nothing for now

## For leaks
Use this `command`
```sh
valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell
```
