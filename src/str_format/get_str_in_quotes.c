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

	av_tmp = av;
	while (*av_tmp != NULL)
	{
		if (**av_tmp == '\"')
		{
			fmt_input_spec_chr(av_tmp);
			*av_tmp = get_str_in_dquotes(*av_tmp);
		}
		else if (**av_tmp == '\'')
			*av_tmp = get_str_in_quotes(*av_tmp);
		av_tmp++;
	}
	av_tmp = ft_tab_dup(av);
	free_tab_str(&av);
	return (av_tmp);
}
