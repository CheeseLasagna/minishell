#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigint_handler(int signum)
{
	printf("\n> ");
	exit(0);
}

void quit_handler(int signum)
{
	printf("Quit (core dumped)");
	printf("\n> ");
	exit(0);
}

int main()
{
	int id;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	id = fork();
	if (id == 0) 
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, quit_handler);
		while (1)
		{
			printf("Sleeping...\n");
			sleep(1);
		}
		printf("beb\n");
		printf("beb\n");
		printf("beb\n");
		printf("beb\n");
		exit (0);
	}
	else
	{
		waitpid(id, NULL, 0);
		printf("SUCCESS\n");
	}
	
	return (0);
}
