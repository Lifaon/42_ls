/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:04:19 by mlantonn          #+#    #+#             */
/*   Updated: 2019/07/23 23:10:51 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_width(t_env *env, int *width, int *size)
{
	int	i;
	int	max;
	int	tmp;

	i = -1;
	max = 1;
	*size = 0;
	while (++i < env->size)
	{
		if (env->opt['P'] && (env->contents[i].type == 'd'
			|| env->contents[i].type == 'l'))
			continue ;
		++*size;
		tmp = 0;
		while (env->contents[i].name[tmp])
			++tmp;
		if (tmp > max)
			max = tmp;
	}
	*width = ((max / 8) * 8) + 8;
}

static void	print(t_env *env, int cols, int width, int size)
{
	int lines;
	int i;
	int j;

	lines = size / cols + (size % cols != 0);
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
			ft_printf_static("%-*s", width,
				env->contents[(j * lines) + i].name);
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
	int			size;

	if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)))
		return (1);
	get_width(env, &width, &size);
	cols = ((ws.ws_col / 8) * 8) / width;
	if (cols == 1)
		return (1);
	print(env, cols, width, size);
	return (0);
}
