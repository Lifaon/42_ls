/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:04:19 by mlantonn          #+#    #+#             */
/*   Updated: 2019/07/18 18:11:40 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_width(t_env *env)
{
	int	i;
	int	max;
	int	tmp;

	i = -1;
	max = 1;
	while (++i < env->size)
	{
		tmp = 0;
		while (env->contents[i].name[tmp])
			++tmp;
		if (tmp > max)
			max = tmp;
	}
	return (((max / 8) * 8) + 8);
}

static void		print(t_env *env, int cols, int width)
{
	int lines;
	int i;
	int j;

	lines = env->size / cols + (env->size % cols != 0);
	i = -1;
	while (++i < lines)
	{
		j = -1;
		while (++j < cols)
		{
			if (((j * lines) + i >= env->size) || (env->opt['P']
					&& (env->contents[(j * lines) + i].type == 'd'
						|| env->contents[(j * lines) + i].type == 'l')))
				continue ;
			ft_printf_static("%-*s", width, env->contents[(j * lines) + i].name);
			env->printed++;
		}
		if (env->printed)
			ft_printf_static("\n");
	}
}

int			print_formatted(t_env *env)
{
	t_winsize	ws;
	int			width;
	int			cols;

	if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)))
		return (1);
	width = get_width(env);
	cols = (((ws.ws_col * 8) / 8) + 8) / width;
	if (cols == 1)
		return (1);
	print(env, cols, width);
	return (0);
}
