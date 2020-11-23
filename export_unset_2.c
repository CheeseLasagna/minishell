#include "built_in.h"

void	free_array(char **env)
{
	char **env1;

	env1 = env;
	while (*env1 != NULL)
	{
		free(*env1);
		env1++;
	}
	free(env);
}

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
		if (*c < 48 || (*c > 57 && *c < 61) || (*c > 61 && *c < 65)
		|| (*c > 90  && *c < 95) || *c == 96 || *c > 122)
		{
			write(1, "bash: export: '", 15);
			write(1, arg, ft_strlen(arg));
			write(1, "': not a valid identifier\n", 26);
			return(1);
		}
		c++;
	}
	return (0);
}

int		find_doub_array_len(char **env)
{
	int len;

	len = 0;
	while(*env != NULL)
	{
		len++;
		env++;
	}
	return (len);
}