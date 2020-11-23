#include "built_in.h"

char	**new_double_array_unset(char *old, char **env, int oldlen)
{
	char	**env1;
	char	**new;
	char	**new1;
	int		len;

	len = find_doub_array_len(env);
	new = (char**)malloc(sizeof(char*) * len);
	env1 = env;
	new1 = new;
	while (*env1 != NULL)
	{
		if ((ft_strncmp(old, *env1, oldlen)) != 0)
		{
			*new1 = ft_strdup(*env1);
			new1++;
			env1++;
		}
		else
			env1++;
	}
	free_array(env);
	*new1 = NULL;
	return (new);	
}
		
char **find_and_remove(char *arg, char **env)
{
	int len;
	char **env1;
	int x;

	env1 = env;
	while (*env1 != NULL)
	{
		len = keylen(*env1);
		x = ft_strncmp(arg, *env1, len);
		if (!x)
		{
			env = new_double_array_unset(*env1, env, len);
			return (env);
		}
		env1++;
	}
	return (env);
}		
		
int check_args_unset(char *arg)
{
	char *c;

	c = arg;
	while (*c != '\0')
	{
		if (*c < 48 || (*c > 57 && *c < 65) ||
		(*c > 90  && *c < 95) || *c == 96 || *c > 122)
		{
			write(1, "bash: unset: '", 14);
			write(1, arg, ft_strlen(arg));
			write(1, "': not a valid identifier\n", 26);
			return (1);
		}
		c++;
	}
	return (0);
}

char **unset(char **args, char **env)
{
	args++;
	while (*args != NULL)
	{
		if (!(check_args_unset(*args)))
			env = find_and_remove(*args, env);
		args++;
	}
	return (env);
}	
