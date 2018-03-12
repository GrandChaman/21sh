#include "ft_sh.h"

static int size_str(t_vari var, char *original)
{
	int nb;

	nb = 0;
	while (original[var.i] && (original[var.i] != ' ' && original[var.i] != '\t'))
	{
		var.i++;
		nb++;
	}
	return (nb);
}


void	call_heredoc(t_vari var, char *original)
{
	int size;
	char *str;
	int o;
	char *tmp = NULL;
	char *path_file;
	int fd;
	char *tmp2;

	o = 0;
	size = size_str(var, original);
	str = malloc(sizeof(char) * size + 1);
	while (original[var.i] && (original[var.i] != ' ' && original[var.i] != '\t'))
	{
		str[o] = original[var.i];
		var.i++;
		o++;
	}
	str[o] = '\0';
	tmp = read_command("heredoc>", NULL, 1);
	tmp2 = ft_itoa(var.heredoc);
	path_file = ft_strjoin("/tmp/heredoc", tmp2);
	free(tmp2);
	if ((fd = open(path_file,  O_RDWR | O_CREAT | O_EXCL | O_APPEND, 0777)) == -1)
	{
		if ((fd = open(path_file, O_WRONLY | O_TRUNC, 0777)) == -1)
		{
			exit(0);
		}
		close(fd);
		if ((fd = open(path_file,  O_RDWR | O_APPEND, 0777)) == -1)
			exit(0);
	}
	free(path_file);
	while (ft_strcmp(str, tmp) != 0)
	{
		ft_fprintf(fd, tmp);
		free(tmp);		
		tmp = read_command("heredoc>", NULL, 1);		
	}
	free(tmp);
	free(str);
	close(fd);
}