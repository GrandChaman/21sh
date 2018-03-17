#include "ft_sh.h"

static int	size_str(t_vari var, char *original)
{
	int nb;

	nb = 0;
	while (original[var.i] && (original[var.i] != ' ' &&
		original[var.i] != '\t'))
	{
		var.i++;
		nb++;
	}
	return (nb);
}

static char	*search_str(t_vari var, char *original)
{
	int		o;
	char	*str;

	o = 0;
	if (!(str = malloc(sizeof(char) * size_str(var, original) + 1)))
		exit(0);
	while (original[var.i] && (original[var.i] != ' ' &&
		original[var.i] != '\t'))
	{
		str[o] = original[var.i];
		var.i++;
		o++;
	}
	str[o] = '\0';
	return (str);
}

static void	final_heredoc(char *tmp, char *str, char *tmp2, int fd)
{
	while (ft_strcmp(str, tmp) != 0)
	{
		tmp2 = ft_strjoin(tmp, "\n");
		ft_fprintf(fd, tmp2);
		free(tmp2);
		free(tmp);
		tmp = read_command(NULL, 0, 1, 0);
	}
}

void		call_heredoc(t_vari var, char *original)
{
	char	*str;
	char	*tmp;
	char	*path_file;
	int		fd;
	char	*tmp2;

	str = search_str(var, original);
	tmp = read_command(NULL, 0, 1, 0);
	tmp2 = ft_itoa(var.heredoc);
	path_file = ft_strjoin("/tmp/21sh_heredoc", tmp2);
	free(tmp2);
	if ((fd = open(path_file, O_RDWR | O_CREAT | O_EXCL |
		O_APPEND, 0777)) == -1)
	{
		if ((fd = open(path_file, O_WRONLY | O_TRUNC, 0777)) == -1)
			exit(0);
		close(fd);
		if ((fd = open(path_file, O_RDWR | O_APPEND, 0777)) == -1)
			exit(0);
	}
	free(path_file);
	final_heredoc(tmp, str, tmp2, fd);
	free(str);	
	free(tmp);
	close(fd);
}
