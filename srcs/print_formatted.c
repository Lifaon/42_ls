/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:04:19 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/11 14:47:11 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	can_be_formatted(t_env *env)
{
	t_winsize	ws;
	int			lines;
	int			cols;
	int			tmp;
	int			len;
	int			i;
	int			j;

	if (ioctl(1, TIOCGWINSZ, &ws))
		return (0);
	lines = 1;
	while (lines < env->size / 2)
	{
		i = -1;
		len = 0;
		cols = (env->size / lines) + 1;
		while (++i < cols)
		{
			j = -1;
			tmp = 0;
			while (++j < lines)
			{
				if ((j * lines) + i < env->size && tmp < env->contents[(j * lines) + i].name_len + 2)
					tmp = env->contents[(j * lines) + i].name_len + 2;
			}
			len += tmp;
			
		}
		if (len < ws.ws_col)
			return (lines);
		++lines;
	}
	return (0);
}

int			print_formatted(t_env *env)
{
	int *sizes;
	int lines;
	int cols;
	int tmp;
	int i;
	int j;
	int k;

	if (!(lines = can_be_formatted(env)))
		return (1);
	cols = (env->size / lines) + 1;
	ft_printf("%d cols / %d lines\n", cols, lines);
	if (!(sizes = (int *)malloc(sizeof(int) * cols)))
		return (1);
	i = -1;
	while (++i < cols)
		sizes[i] = 0;
	i = -1;
	while (++i < lines)
	{
		j = -1;
		while (++j < cols)
		{
			k = (j * lines) + i;
			tmp = k < env->size ? env->contents[k].name_len + 2 : 0;
			sizes[j] = sizes[j] >= tmp ? sizes[j] : tmp;
			// ft_printf("line n°%d / col n°%d / name = %s\n", i, j, env->contents[k].name);
		}
	}
	i = -1;
	while (++i < lines)
	{
		j = -1;
		while (++j < cols)
			if ((j * lines) + i < env->size)
				ft_printf("%-*s", sizes[j], env->contents[(j * lines) + i].name);
		ft_printf("\n");
	}
	free(sizes);
	return (0);
}
