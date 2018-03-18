#include "ft_sh.h"

int	check_dup_input(t_parser *parser, int x)
{
	int i;
	int fd;
	int stock;
	char *str;
	char *str2;

	i = 0;	
	if (parser[x].input.meta)
	{
		while (parser[x].input.meta)
		{
			if (parser[x].input.meta[i].name && parser[x].input.meta[i].name[0] == '&')
			{
				if (!(parser[x].input.meta[i].name[1] && parser[x].input.meta[i].name[1] == '-'))
				{
					ft_easy_input(&stock, x, i, parser);
					if (parser[x].input.meta[i].name[1])
						dup2(stock, parser[x].input.meta[i].name[1] - 48);
					else
						dup2(stock, 0);
				}
			}
			else
			{
				if (parser[x].input.meta[i].heredoc_number)
				{
					str = "/tmp/21sh_heredoc";
					str2 = ft_itoa(parser[x].input.meta[i].heredoc_number);
					str = ft_strjoin(str, str2);
					if ((fd = open(str,  O_RDWR, 0777)) == -1)
						exit(0);
					free(str);
					free(str2);
					dup2(fd, 0);
				}
				else
				{
					if ((fd = open(parser[x].input.meta[i].name,  O_RDWR, 0777)) == -1)
					{
						ft_printf("21sh :no such file or directory\n");
						return(0);
					}
					ft_easy_input(&stock, x, i, parser);
					dup2(fd, stock);
				}
			}
			if (parser[x].input.meta[i].next_exist == 0)
				break ;
			i++;
		}
	}
	return (1);
}

void	ft_easy_input(int *stock, int x, int i, t_parser *parser)
{
	if (parser[x].input.meta[i].stdin)
		*stock = 0;
	else if (parser[x].input.meta[i].stdout)
		*stock = 1;
	else if (parser[x].input.meta[i].stderr)
		*stock = 2;
}