#include "built_in.h"

char	**new_double_array_export(char *arg, char **env, int len)
{
	char **new;
	char **new1;
	char **env1;

	env1 = env;
	new = (char **)malloc(sizeof(char *) * (len + 2));
	new1 = new;
	while (*env1 != NULL)
	{
		*new1 = ft_strdup(*env1); 
		new1++;
		env1++;
	}
	free_array(env);
	*new1 = ft_strdup(arg);
	new1++;
	*new1 = NULL;
	return (new);
}

char	**add_to_env_list(char *arg, char **env)
{
	char **env1;
	int len_res;

	env1 = env;
	while (*env1 != NULL)
	{
		len_res = keylen(arg);
		len_res = ft_strncmp(arg, *env1, len_res + 1);
		if (!len_res)
		{
			free(*env1);
			*env1 = ft_strdup(arg);
			return (env);
		}
		env1++;
	}
	len_res = find_doub_array_len(env);
	env = new_double_array_export(arg, env, len_res);	
	return (env);
}	

void	print_element_export(char *elem)
{
	char *s;
	int len;

	s = ft_strchr(elem, '=');
	s++;
	len = keylen(elem);
	write(1, "declare -x ", 11);
	write(1, elem, len + 1);
	write(1, "\"", 1);
	write(1, s, ft_strlen(s));
	write(1, "\"", 1);
	write(1, "\n", 1);
}

char	**export2(char **args, char **env)
{
	char *s;

	while (*args != NULL)
	{
		if (!(check_args_export(*args)))
		{
			s = ft_strchr(*args, '=');
			if (s != NULL)
				env = add_to_env_list(*args, env);	
		}
		args++;
	}
	return (env);
}
	
char	**export(char **args, char **env)
{
	char **env1;
	char *s;

	env1 = env;
	args++;
	if (*args == NULL)
	{
		while (*env1 != NULL)
		{
			print_element_export(*env1);
			env1++;
		}
	}
	else
		env = export2(args, env);	
	return (env);
}