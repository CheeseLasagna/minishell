#include "built_in.h"

void	pwd()
{
	char	*s;
	int		size;

	size = 100;
	s = (char*)malloc(sizeof(char) * size);
	while (getcwd(s, size) == NULL)
	{
		free(s);
		size = size + 50;
		s = (char*)malloc(sizeof(char) * size);
	}
	write(1, s, size);
	write(1, "\n", 1);
	free(s);
}

int		main()
{
	pwd();
	return (0);
}
