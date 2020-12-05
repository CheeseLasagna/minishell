#include <stdio.h>
#include "../../includes/minishell.h"

void cd(char **args)
{
	char *s;

	args++;
	if(*args == NULL)
		chdir("/home/");
	else
	{
		if (*(args + 1) != NULL)
		{
			write(1, "bash: cd: too many arguments\n", 29);
			exit_status = 1;
		}
		else
			if (chdir(*args) == -1)
			{
				s = strerror(errno);
				write(1, "bash: cd: ", 10);
				write(1, *args, ft_strlen(*args));
				write(1, ": ", 2);
				write(1, s, ft_strlen(s));
				write(1, "\n", 1);
				exit_status = 1;
			}
	}
}

/*int main()
{
	char s[100];

//	char *args[] = {"cd", "/home/lasagna", NULL};
//	char *args[] = {"cd", "/home/lasagna", "/home", NULL};
	char *args[] = {"cd", "asdfasdfas", NULL};
//	char *args[] = {"cd", "..", NULL};
//	char *args[] = {"cd", NULL};
	printf("%s\n", getcwd(s, 100));	
	cd(args);
	printf("%s\n", getcwd(s, 100));	
	return (0);
}*/
