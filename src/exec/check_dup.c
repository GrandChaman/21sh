#include "ft_sh.h"

int	check_dup(t_parser *parser, int x)
{
	int fd;
	int i;
	int stock;

	i = 0;
	ft_easy2(x, parser);
	if (parser[x].output.meta)
	{
		while (parser[x].output.meta)
		{
			if (parser[x].output.meta[i].name[0] == '&')
			{
				if (!(parser[x].output.meta[i].name[1] && parser[x].output.meta[i].name[1] == '-'))
				{
					ft_easy_output(&stock, x, i, parser);
					if (parser[x].output.meta[i].name[1])
						dup2(stock, parser[x].output.meta[i].name[1] - 48);
					else
						dup2(stock, 1);
				}
			}
			else
			{
				if (parser[x].output.meta[i].double_chevron)
				{
					if ((fd = open(parser[x].output.meta[i].name,  O_RDWR | O_CREAT
							| O_EXCL | O_APPEND , 0777)) == -1)
					{
					if ((fd = open(parser[x].output.meta[i].name,  O_RDWR | O_APPEND, 0777)) == -1)
						exit(0);
					}
				}
				else if ((fd = open(parser[x].output.meta[i].name,  O_RDWR | O_CREAT
							| O_EXCL, 0777)) == -1)
				{
					if ((fd = open(parser[x].output.meta[i].name, O_WRONLY |
						O_TRUNC, 0777)) == -1)
						exit(0);
					close(fd);
					if ((fd = open(parser[x].output.meta[i].name,  O_RDWR, 0777)) == -1)
						exit(0);
				}
				ft_easy_output(&stock, x, i, parser);
				dup2(fd, stock);
			}
			if (parser[x].output.meta[i].next_exist == 0)
				break;
			i++;
		}
	}
	return (check_dup_input(parser, x));
}

void	ft_easy2(int x, t_parser *parser)
{
	if (parser[x].close_stdin)
		close(0);
	if (parser[x].close_stdout)
		close(1);
	if (parser[x].close_stderr)
		close(2);
}

void	ft_easy_output(int *stock, int x, int i, t_parser *parser)
{
	if (parser[x].output.meta[i].stdin)
		*stock = 0;
	else if (parser[x].output.meta[i].stdout)
		*stock = 1;
	else if (parser[x].output.meta[i].stderr)
		*stock = 2;
}

void	init_r_dup(t_dup *r_dup)
{
	r_dup->stdin_copy = dup(0);
	r_dup->stdout_copy = dup(1);
	r_dup->stderr_copy = dup(2);
}

void	init_dup(t_dup *r_dup)
{
	dup2(r_dup->stdin_copy, 0);
	dup2(r_dup->stdout_copy, 1);
	dup2(r_dup->stderr_copy, 2);
}