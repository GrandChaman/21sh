#include "ft_sh.h"

int main(int argc, char **argv)
{
	//t_parser *parser;
	char ptr_need_quote;
	
	if (argc == 3)
	{
		printf("tu te fout de ma geule\n");
		return (0);
	}
	if (argc == 1)
	{
		printf("ta oublier un truc\n");
		return (0);
	}
	split_evoluted(argv[1], &ptr_need_quote);
}

/*

	1 verifier que tt est bon avec les cotes...
	2 tout remplacer
	3 remplir structure

*/

/*
orginal = cat -e file | grep "ligne" > other

parser[0].name_cmd = cat
parser[0].argument[0].name = -e
					  special = 0;
		  argument[1].name = file
		  			  special = 0;
parser[0].entree_cmd.
					exist = 0;
					pipe = 0;
					name_file = NULL;
parser[0].sortie_cmd.
					standart = 0;
					erreur = 0;
					to_next_cmd = 1;
					name_file = NULL;
					double_chevron = 0;
					continue_if_fail = 1;

parser[1].name_cmd = grep
parser[1].argument[0].name = ligne
		  			  special = 0;
parser[1].entree_cmd.
					exist = 1;
					pipe = 1;
					name_file = NULL;
parser[1].sortie_cmd.
					standart = 0;
					erreur = 0;
					to_next_cmd = 0;
					name_file = other;
					double_chevron = 0;
					continue_if_fail = 1;

*/

/*
	original = ls > file && echo "lol"

parser[0].name_cmd = ls
parser[0].argument[0].name = file
		  			  special = 0;
parser[0].entree_cmd.
					exist = 1;
					pipe = 0;
					name_file = file;
parser[0].sortie_cmd.
					standart = 1;
					erreur = 0;
					to_next_cmd = 0;
					name_file = NULL;
					double_chevron = 0;
					continue_if_fail = 0;

parser[1].name_cmd = echo
parser[1].argument[0].name = lol
		  			  special = 0;
parser[1].entree_cmd.
					exist = 0;
					pipe = 0;
					name_file = NULL;
parser[1].sortie_cmd.
					standart = 1;
					erreur = 0;
					to_next_cmd = 0;
					name_file = NULL;
					double_chevron = 0;
					continue_if_fail = 1;
*/

/*

original = echo  "  file" >> file

parser[0].name_cmd = cat
parser[0].argument[0].name =   file
		  			  special = 0;
parser[0].entree_cmd.
					exist = 0;
parser[0].sortie_cmd.
					standart = 0;
					erreur = 0;
					to_next_cmd = 1;
					name_file = file;
					double_chevron = 1;
					continue_if_fail = 1;
*/

/*

original = cat *.c
parser[0].name_cmd = cat
parser[0].argument[0].name = *.c
		  			  special = 1;
parser[0].entree_cmd.
					exist = 0;
parser[0].sortie_cmd.
					standart = 1;
					erreur = 0;
					to_next_cmd = 1;
					name_file = NULL;
					double_chevron = 0;
					continue_if_fail = 1;

*/