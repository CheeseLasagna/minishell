#include "built_in.h"

void	envp(char **env)
{
	while (*env != NULL)
	{
		write(1, *env, ft_strlen(*env));	
		write(1, "\n", 1);
		env++;
	}
}

int		main(int argc, char **argv, char **env)
{
	envp(env);
	return (0);
}
