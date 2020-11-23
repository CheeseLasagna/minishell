#include "built_in.h"

int main (int argc, char **argv, char **env)
{
	char **dyn_env;
	dyn_env = convert_array(env);
	char *args[] = {"export", "PWD=jejeje", "j*ka=", "SHELL=testtesttest", NULL};
	dyn_env = export(args, dyn_env);
	char *args2[] = {"export", NULL};
	dyn_env = export(args2, dyn_env);
	write(1, "\n\n", 2);
	char *args3[] = {"unset", "SHELL", "PWD=", "testtest", NULL};
	dyn_env = unset(args3, dyn_env);
	char *args4[] = {"export", NULL};
	dyn_env = export(args4, dyn_env);
	return (0);
}