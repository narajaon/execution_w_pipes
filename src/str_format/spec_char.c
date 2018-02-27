#include "../../inc/header.h"

t_schar		g_spec_char[SCHAR_NB] =
{
	{"\\a", '\a'},
	{"\\f", '\f'},
	{"\\n", '\n'},
	{"\\b", '\b'},
	{"\\r", '\r'},
	{"\\t", '\t'},
	{"\\v", '\v'},
	{"", 0},
};

bool		converted_spe_char(char c)
{
	return (c == 'a' || c == 'f' || c == 'n' || c == 'b' || c == 'r' ||
			c == 't' || c == 'v');
}

int			is_esc_char(char *str)
{
	int			i;

	i = 0;
	while (i < SCHAR_NB)
	{
		if (ft_strncmp(g_spec_char[i].sequ, str, 2) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char		*replace_spec_char(char *user_in, int size)
{
	char		*formated;
	int			esc_index;
	int			i;

	i = 0;
	if ((formated = ft_memalloc(size)) == NULL)
		return (NULL);
	while (*user_in != '\0')
	{
		if (*user_in == '\\' && converted_spe_char(user_in[1]) == 0)
			formated[i] = *(++user_in);
		else if ((esc_index = is_esc_char(user_in)) >= 0)
		{
			formated[i] = g_spec_char[esc_index].asc;
			user_in++;
			if (*user_in == '\0')
				break ;
		}
		else
			formated[i] = *user_in;
		user_in++;
		i++;
	}
	formated[i] = '\0';
	return (formated);
}

void		fmt_input_spec_chr(char **str)
{
	int		in_size;
	char	*formated;

	in_size = ft_strlen(*str) + 1;
	formated = replace_spec_char(*str, in_size);
	free_str(str);
	*str = formated;
}
