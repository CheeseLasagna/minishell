#include "built_in.h"

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	write(1, str, ft_strlen(str));
}

void	echo(char **args)
{
	int flag;

	flag = 0;
	args++;
	if (ft_strncmp(*args, "-n", 3) == 0)
		args++;
	else
		flag = 1;
	while (*args != NULL)
	{
		ft_putstr(*args);
		args++;
		if (*args != NULL)
			write(1, " ", 1);
	}
	if (flag)
		write(1, "\n", 1);
}

int		main()
{
	char *args[] = {"echo", "-n", "ggg", "fff", NULL};
	//char *args[] = {"echo", "ggg", "fff", NULL};
	echo(args);
	return (0);
}
		
	
