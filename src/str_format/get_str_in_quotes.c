#include "../../inc/header.h"

bool		is_esc_cmp(char *str, char *esc)
{
	if (ft_strncmp(str, esc, 2) == 0)
		return (TRUE);
	return (FALSE);
}

char		*get_str_in_dquotes(char *str)
{
	char	*content;
	int		i;

	i = 0;
	if (*str != '\"')
		return (str);
	str++;
	while (str[i])
	{
		if (is_esc_cmp(&str[i], "\\\"") == TRUE)
			i++;
		else if (str[i] == '"')
			break ;
		i++;
	}
	content = ft_strsub(str, 0, i);
	return (content);
}

char		*get_str_in_quotes(char *str)
{
	char	*content;
	int		i;

	i = 0;
	if (*str != '\'')
		return (str);
	str++;
	while (str[i] && str[i] != '\'')
		i++;
	content = ft_strsub(str, 0, i);
	return (content);
}

char		**fmt_input_quote(char **av)
{
	char	**av_tmp;
	char	**stock_av;
	char	*formated;

	av_tmp = (char **)malloc(sizeof(char *) * (ft_tablen(av) + 1));
	stock_av = av_tmp;
	while (*av != NULL)
	{
		if (**av == '\"')
		{
			formated = ft_strdup(*av);
			*av_tmp = get_str_in_dquotes(formated);
			fmt_input_spec_chr(av_tmp);
			free_str(&formated);
		}
		else if (**av == '\'')
			*av_tmp = get_str_in_quotes(*av);
		else
		{
			formated = ft_strdup(*av);
			fmt_input_spec_chr(&formated);
			*av_tmp = formated;
		}
		av++;
		av_tmp++;
	}
	*av_tmp = NULL;
	return (stock_av);
}
