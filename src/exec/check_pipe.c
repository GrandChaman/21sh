#include "ft_sh.h"

void	check_pipe(t_parser *parser, int x, t_dup *r_dup)
{
	if (!(parser[x].input.pipe) && parser[x].output.pipe) // si debut de pipe
	{
		pipe(r_dup->p);
		dup2(r_dup->p[1], 1);
	}
	else if (!(parser[x].output.pipe) && parser[x].input.pipe) // si fin de pipe
	{
		close(r_dup->p[1]); //ferme le dup
		dup2(r_dup->stdin_copy, 1); // ecris dans l entree standart
		dup2(r_dup->p[0], 0); //recupere l ancienne cmd
	}
	else if (parser[x].input.pipe && parser[x].output.pipe) // si entre deux pipe
	{    
    	close(r_dup->p[1]);
    	dup2(r_dup->p[0], 0);
    	pipe(r_dup->p);
    	dup2(r_dup->p[1], 1);
	}
}