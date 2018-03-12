#include "parser.h"

void		fill_parser(t_parser *parser, char *original)
{
	t_vari var;

	init_var(&var);
//	printf("\noriginal = %s\n", original);
	while (original[var.i])
	{
		while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
			var.i++;
		while (original[var.i] && original[var.i] != ';' && original[var.i] != '|')
		{
			while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
				var.i++;
			if (original[var.i] == '\0')
				break;
			while ((original[var.i] != ' ' && original[var.i] != '\t' &&
			original[var.i] != ';' && original[var.i] != '|') && original[var.i])
			{
				while (checkquote_fill_cmd(&var, original, parser) != 'n')
				{
					while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
						var.i++;
				}
				while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
					var.i++;
				if (original[var.i] == '\0'|| original[var.i] == ';' || original[var.i] == '|')
					break ;
				var.boite = redirections4(original, parser, &var);
				if (var.boite == 4)
				{
					var.i_input++;					
					if (original[var.i] == '\0' || original[var.i] == ' ' || original[var.i] == '\t')
						break ;
					//var.box = 4;
				}
				if (var.boite == 2)
				{
					var.box = var.boite;
					var.stock = checkquote_fill_output(&var, original, parser);
					if (var.stock == 'n' || var.stock == 'k')
						break ;
				}
				if (var.boite == 3)
				{
					var.box = var.boite;
					var.stock = checkquote_fill_input(&var, original, parser);
					if (var.stock == 'n' || var.stock == 'k')
						break ;
				}
				if (var.boite == 1 && var.box == 1)
				{
	//				printf("fill_cmd parser[%d].cmd[%d][%d] = %c\n", var.b, var.j,var.o,  original[var.i]);
					parser[var.b].cmd[var.j][var.o] = original[var.i];
				}
				if (var.box == 3)
				{
	//				printf("fill_input = %c\n", original[var.i]);
					parser[var.b].input.meta[var.i_input].name[var.o] = original[var.i];
				}
				if (var.box == 2)
				{
//					printf("fill_output = %c\n", original[var.i]);
					parser[var.b].output.meta[var.i_output].name[var.o] = original[var.i];
				}
				var.i++;
				var.o++;
			}
			if (var.z >= 0 && var.o != 0 && var.box == 1)
			{
//				printf("rajoute cmd backslash\n");
				parser[var.b].cmd[var.j][var.o] = '\0';
				var.j++;
			}
			if (var.box == 2 && var.o != 0)
			{
				parser[var.b].output.meta[var.i_output].name[var.o] = '\0';
				var.i_output++;
				var.box = 1;
			}
			if (var.box == 3 && var.o != 0)
			{
				parser[var.b].input.meta[var.i_input].name[var.o] = '\0';
				var.i_input++;
				var.box = 1;
			}
			if (original[var.i] == '\0') //suprimer conditon ; ???
				break ;
			var.o = 0;
			var.z++;
		}
		var.box = 1;
		if ((var.z > 0 || (var.z == 0 && original[var.i] == '\0')) && var.j)
			parser[var.b].cmd[var.j] = NULL;
		var.i_input = 0;
		var.i_output = 0;
		var.j = 0;
		var.z = 0;
		if (original[var.i] == '\0')
			break ;
		if (original[var.i] == '|')
		{
			var.i++;
			while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
				var.i++;
		}
		else
			var.i++;
		while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
			var.i++;
		var.b++;
	}
//	printf("End\n");
}