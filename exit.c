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

void	my_exit(char **env)
{
	free_array(env);
	exit(33);
}

int		main(int argc, char **argv, char **env)
{
	char **dyn_env;
	dyn_env = convert_array(env);
	my_exit(dyn_env);
	return (0);
}
