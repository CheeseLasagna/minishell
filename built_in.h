#ifndef BUILT_IN
# define BUILT_IN
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include "./libft/libft.h"

void    free_array(char **env);
char    **convert_array(char **args);
char    **unset(char **args, char **env);
int     keylen(char *key);
char    **export(char **args, char **env);
int     check_args_export(char *arg);
int		find_doub_array_len(char **env);
#endif