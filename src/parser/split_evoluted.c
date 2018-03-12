#include "ft_sh.h"


void	split_evoluted(t_parser *parser, char *original)
{

	t_vari var;
	init_var(&var);

//	printf("\noriginal = %s\n\n", original);
	while (original[var.i])
	{
		var.box = 1;
		while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
			var.i++;
		var.nbr_argv = count_argv(var.i, original);
//		printf("---------------Ici nb argument = %d\n", var.nbr_argv);
		var.nbr_redirection_input = count_redirection_input(var.i, original);
//		printf("++++++++++ var.nbr_redirection_input = %d\n", var.nbr_redirection_input);
		var.nbr_redirection_output = count_redirection_output(var.i, original);
//		printf("************ var.nbr_redirection_output = %d\n", var.nbr_redirection_output);
		while (original[var.i] && original[var.i] != ';' && original[var.i] != '|')
		{
			while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
				var.i++;
			if (original[var.i] == '\0')
				break ;
			while ((original[var.i] != ' ' && original[var.i] != '\t' &&
			original[var.i] != ';' && original[var.i] != '|') && original[var.i])
			{
				if ((checkquote(&var.i, &var.o, original)) == 'k')
					break ;
				if (original[var.i] == '\0')
					break ;
				var.boite = redirections2(original, &var);
				if (var.boite != 1)
				{
					if (var.boite == 2)
					{
						if (var.i_output == 0)
						{
//							printf("malloc nbr de ouput = %d\n", var.nbr_redirection_output);
							parser[var.b].output.meta = malloc(sizeof(t_meta_output) * var.nbr_redirection_output + 1);
							init_meta_output(parser, var.b, var.nbr_redirection_output);
						}
					}
					if (var.boite == 3 || var.boite == 4)
					{
						if (var.i_input == 0)
						{
//							printf("malloc nbr de input = %d\n", var.nbr_redirection_input);
							parser[var.b].input.meta = malloc(sizeof(t_meta_input) * var.nbr_redirection_input + 1);
							init_meta_input(parser, var.b, var.nbr_redirection_input);
						}
						if (var.boite == 4)
							var.i_input++;
					}
					checkquote(&var.i, &var.o, original);
					var.box = var.boite;
					break ;
				}
				var.i++;
				var.o++;
			}
			if (var.z == 0 && var.box == 1)
			{
//				printf("nombre de mot dans la commande = %d\n", var.nbr_argv);
				if (!(parser[var.b].cmd = malloc(sizeof(char *) * var.nbr_argv + 1)))
					exit(0);
			}
			if (var.box == 1)
			{
//				printf("malloc parser[%d].cmd[%d] = %d\n", var.b, var.z, var.o);
				if (!(parser[var.b].cmd[var.z] = malloc(sizeof(char) * var.o + 1)))
					exit(0);
			}
			if (var.box == 2)
			{
				while ((original[var.i] != ' ' && original[var.i] != '\t' &&
				original[var.i] != ';' && original[var.i] != '|') && original[var.i])
				{
					var.i++;
					var.o++;
				}
//				printf("malloc parser[%d].output.name_file[%d] = %d\n", var.b, var.i_output, var.o);
				if (!(parser[var.b].output.meta[var.i_output].name = malloc(sizeof(char) * var.o + 1)))
					exit(0);
				var.i_output++;
			}
			if (var.box == 3)
			{
				while ((original[var.i] != ' ' && original[var.i] != '\t' &&
				original[var.i] != ';' && original[var.i] != '|') && original[var.i])
				{
					var.i++;
					var.o++;
				}
//				printf("malloc parser[%d].input.name_file[%d] = %d\n", var.b , var.i_input , var.o);
				if (!(parser[var.b].input.meta[var.i_input].name = malloc(sizeof(char) * var.o + 1)))
					exit(0);
				var.i_input++;
			}
//			printf("commande [%d] mot[%d] = %d\n\n", var.b, var.z, var.o);
			var.o = 0;
			while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
				var.i++;
			if (original[var.i] == '\0' || original[var.i] == ';' || original[var.i] == '|')
				break ;
			if (var.box == 1)
				var.z++;
			var.box = 1;
		}
		var.z = 0;
		var.i_input = 0;
		var.i_output = 0;
		if (original[var.i] == '\0')
			break ;
		if (original[var.i] == '|')
		{
			parser[var.b].output.pipe = 1;
			var.i++;
			while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
				var.i++;
			parser[var.b + 1].input.pipe = 1;
		}
		if (original[var.i] == ';')
			var.i++;
		while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
			var.i++;
		var.b++;
	}
//	printf("End\n");
}
