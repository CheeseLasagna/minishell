#include "built_in.h"

char **convert_array(char **args)
{
	char	**arg1;
	char	**dyno;
	char	**dyno1;
	int		number_of_args;

	number_of_args = 0;
	arg1 = args;
	while (*arg1 != NULL)
	{
		number_of_args++;
		arg1++;
	}
	arg1 = args;
	dyno = (char**)malloc(sizeof(char*) * (number_of_args + 1));
	dyno1 = dyno;
	while (*arg1 != NULL)
	{
		*dyno1 = ft_strdup(*arg1);
		arg1++;
		dyno1++;
	}
	*dyno1 = NULL;
	return (dyno);
}
