/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wcolor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 15:42:29 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 15:09:08 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	printgreen(t_dlist *list)
{
	t_chr	*schar;
	t_chr	*prev;
	t_chr	*prev2;

	schar = NULL;
	prev = NULL;
	prev2 = NULL;
	if (list != NULL)
	{
		if (list->prev != NULL)
		{
			prev = list->prev->content;
			if (list->prev->prev != NULL)
				prev2 = list->prev->prev->content;
		}
		schar = list->content;
		if (schar->c == '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else if (prev && prev->c == '\\' && prev2->c != '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KGRN, schar->c, KNRM);
	}
}

void	printred(t_dlist *list)
{
	t_chr	*schar;
	t_chr	*prev;
	t_chr	*prev2;

	schar = NULL;
	prev = NULL;
	prev2 = NULL;
	if (list != NULL)
	{
		if (list->prev != NULL)
		{
			prev = list->prev->content;
			if (list->prev->prev != NULL)
				prev2 = list->prev->prev->content;
		}
		schar = list->content;
		if (schar->c == '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else if (prev && prev->c == '\\' && prev2->c != '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KRED, schar->c, KNRM);
	}
}

void	printyellow(t_dlist *list)
{
	t_chr	*schar;
	t_chr	*prev;
	t_chr	*prev2;

	schar = NULL;
	prev = NULL;
	prev2 = NULL;
	if (list != NULL)
	{
		if (list->prev != NULL)
		{
			prev = list->prev->content;
			if (list->prev->prev != NULL)
				prev2 = list->prev->prev->content;
		}
		schar = list->content;
		if (schar->c == '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else if (prev && prev->c == '\\' && prev2->c != '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KYEL, schar->c, KNRM);
	}
}

void	printcyn(t_dlist *list)
{
	t_chr	*schar;
	t_chr	*prev;
	t_chr	*prev2;

	schar = NULL;
	prev = NULL;
	prev2 = NULL;
	if (list != NULL)
	{
		if (list->prev != NULL)
		{
			prev = list->prev->content;
			if (list->prev->prev != NULL)
				prev2 = list->prev->prev->content;
		}
		schar = list->content;
		if (schar->c == '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else if (prev && prev->c == '\\' && prev2->c != '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KCYN, schar->c, KNRM);
	}
}

void	printwhite(t_dlist *list)
{
	t_chr	*schar;
	t_chr	*prev;
	t_chr	*prev2;

	schar = NULL;
	prev = NULL;
	prev2 = NULL;
	if (list != NULL)
	{
		if (list->prev != NULL)
		{
			prev = list->prev->content;
			if (list->prev->prev != NULL)
				prev2 = list->prev->prev->content;
		}
		schar = list->content;
		if (schar->c == '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else if (prev && prev->c == '\\' && prev2->c != '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
	}
}
