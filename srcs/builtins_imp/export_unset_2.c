#include "../../includes/minishell.h"

/*void	free_arrah(char **env)
{
	char **env1;

	env1 = env;
	while (*env1 != NULL)
	{
		free(*env1);
		env1++;
	}
	free(env);
}*/

int		keylen(char *key)
{
	int len;

	len = 0;
	while (*key != '=')
	{
		len++;
		key++;
	}
	return (len);
}

int		check_args_export(char *arg)
{
	char *c;

	c = arg;
	while (*c != '\0')
	{
		if (*c < 47 || (*c > 57 && *c < 61) || (*c > 61 && *c < 65)
		|| (*c > 90  && *c < 95) || *c == 96 || *c > 122)
		{
			write(1, "bash: export: '", 15);
			write(1, arg, ft_strlen(arg));
			write(1, "': not a valid identifier\n", 26);
			exit_status = 1;
			return(1);
		}
		c++;
	}
	return (0);
}

/*int		find_doub_array_len(char **env)
{
	int len;

	len = 0;
	while(*env != NULL)
	{
		len++;
		env++;
	}
	return (len);
}*/

int     ft_strarrlen(char **strarr)
{
	int i;

	i = 0;
	while (strarr && strarr[i])
		i++;
	return(i);
}

int     ft_strarrclear(char ***strarrp)
{
	int i;
 
	i = 0;
	while (*strarrp && (*strarrp)[i])
	{
		free((*strarrp)[i]);
		(*strarrp)[i] = NULL;
 		i++;
 	}
	free(*strarrp);
	*strarrp = NULL;
	return (0);
}

