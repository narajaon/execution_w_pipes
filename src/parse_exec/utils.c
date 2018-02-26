#include "../../inc/header.h"

char		*get_cmd_name(char *input)
{
	int		i;

	i = 0;
	while (*input != '\0' && ft_isspace(*input) == TRUE)
		input++;
	while (input[i] != '\0' && ft_isspace(input[i]) == FALSE)
		i++;
	return (ft_strndup(input, i));
}

bool		is_binary_file(char *bin_name)
{
	if (ft_strchr(bin_name, '/') != 0)
		return (TRUE);
	return (FALSE);
}

bool		is_valid_path(char *path_bin)
{
	if (access(path_bin, X_OK) == 0)
		return (TRUE);
	return (FALSE);
}

char		*check_bin(char **paths, char *input)
{
	char			*path;
	char			*slashed;
	char			*tmp;

	if (paths == NULL)
		return (NULL);
	path = input;
	while (*paths != NULL)
	{
		slashed = ft_strjoin(*paths, "/");
		if (is_valid_path((tmp = ft_strjoin(slashed, path))) == TRUE)
			return (tmp);
		free_str(&tmp);
		free_str(&slashed);
		paths++;
	}
	return (NULL);
}
