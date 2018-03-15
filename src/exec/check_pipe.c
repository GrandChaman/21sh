#include "ft_sh.h"

void	check_pipe(t_parser *parser, int x, t_dup *r_dup)
{
	int pipefd[2];

	if (parser[x].output.pipe)
	{
		printf("Icici\n");
		pipe(pipefd);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
	}
	if (parser[x].input.pipe)
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
	}
}