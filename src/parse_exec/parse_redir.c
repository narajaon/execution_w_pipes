#include "../../inc/header.h"

//output file descriptor
//input file descriptor / file name
//redirection type
//redirection right

char			*skip_cmd_name(t_dlist **arg, char *input)
{
	int			i;

	i = 0;
	while (*input != '\0' && ft_isspace(*input) == TRUE)
		input++;
	while (input[i] != '\0' && ft_isspace(input[i]) == FALSE)
		i++;
	ft_hlstadd_back_void(arg, ft_strsub(input, 0, i));;
	return (&input[i]);
}

int				is_file_redir(char *input)
{
	int			i;

	i = 0;
	if (*input == '&')
	{
		while (input[++i] && ft_isdigit(input[i]) == TRUE)
			;
		return (i);
	}
	while (input[i] != '\0' && ft_isspace(input[i]) == TRUE)
		i++;
	while (input[i] != '\0' && ft_isspace(input[i]) == FALSE)
		i++;
	return (i);
}

char			*is_redir(t_dlist **redir, char *input)
{
	int			i;
	int			type;
	char		*sub;

	i = 0;
	while (input[i] && ft_isdigit(input[i]) == TRUE)
		i++;
	while (input[i] && ft_isspace(input[i]) == TRUE)
		i++;
	if ((type = get_redir(&input[i])) >= 0)
	{
		i += (type == R_LEFT || type == R_RIGHT) ? 1 : 2;
		i += is_file_redir(&input[i]); //add condition if redirect to file
		sub = ft_strsub(input, 0, i);
		ft_hlstadd_back_void(redir, sub);
		return (&input[i]);
	}
	return (NULL);
}

char			*is_arg(t_dlist **arg, char *input)
{
	int			i;
	char		*sub;

	i = 0;
	if ((i += skip_quotes(&input[i], '\"')) != 0)
	{
		sub = ft_strsub(input, 0, i + 1);
		ft_hlstadd_back_void(arg, sub);
		return (&input[i + 1]);
	}
	if ((i += skip_quotes(&input[i], '\'')) != 0)
	{
		sub = ft_strsub(input, 0, i + 1);
		ft_hlstadd_back_void(arg, sub);
		return (&input[i + 1]);
	}
	while (input[i] && ft_isspace(input[i]) == FALSE)
		i++;
	if (i == 0)
		return (input);
	sub = ft_strsub(input, 0, i);
	ft_hlstadd_back_void(arg, sub);
	return (&input[i]);
}

char			*get_next_arg(t_dlist **arg, t_dlist **redirs, char *input)
{
	char		*skip;

	while (*input)
	{
		while (*input != '\0' && ft_isspace(*input) == TRUE)
			input++;
		if ((skip = is_redir(redirs, input)) != NULL)
			input = skip;
		else if ((skip = is_arg(arg, input)) != NULL)
			input = skip;
	}
	return (input);
}

t_dlist			*parse_arg_redirs(char *input)
{
	t_dlist		*arg;
	t_dlist		*redirs;

	arg = NULL;
	redirs = NULL;
	input = skip_cmd_name(&arg, input);
	while (*input != '\0')
		input = get_next_arg(&arg, &redirs, input);
	//do_redirs(redirs);
	return (arg);
}

char			**extract_redir(char *input)
{
	t_dlist		*av_lst;
	char		**av_str;
	int			stdio[3];

	stdio[STDIN_FILENO] = STDIN_FILENO;
	stdio[STDOUT_FILENO] = STDOUT_FILENO;
	stdio[STDERR_FILENO] = STDERR_FILENO;
	av_lst = parse_arg_redirs(input);
	av_str = ft_list_to_tab(av_lst);
	free_hlist_not_content(&av_lst);
	return (av_str);
}
