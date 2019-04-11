/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:04:19 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/11 14:24:07 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_lines_length(t_env *env, int lines)
{
	int cols;
	int tmp;
	int len;
	int i;
	int j;

	i = -1;
	len = 0;
	cols = (env->size / lines) + 1;
	while (++i < cols)
	{
		j = -1;
		tmp = 0;
		while (++j < lines)
		{
			if ((j * lines) + i < env->size \
				&& tmp < env->contents[(j * lines) + i].name_len + 2)
				tmp = env->contents[(j * lines) + i].name_len + 2;
		}
		len += tmp;
	}
	return (len);
}

static void	set_name_len(t_env *env, int lines)
{
	int cols;
	int tmp;
	int i;
	int j;
	int k;

	i = -1;
	cols = (env->size / lines) + 1;
	while (++i < cols)
	{
		j = -1;
		tmp = 0;
		while (++j < lines)
		{
			k = (j * lines) + i;
			if (k < env->size && tmp < env->contents[k].name_len + 2)
				tmp = env->contents[k].name_len + 2;
		}
		j = -1;
		ft_printf("tmp = %d\n", tmp);
		while (++j < lines)
		{
			k = (j * lines) + i;
			if (k < env->size)
				env->contents[k].name_width = tmp;
		}
	}
}

static int	get_lines(t_env *env)
{
	t_winsize	ws;
	int			lines;

	if (ioctl(1, TIOCGWINSZ, &ws))
		return (-1);
	lines = 1;
	while (lines < env->size / 2)
	{
		if (get_lines_length(env, lines) < ws.ws_col)
		{
			set_name_len(env, lines);
			return (lines);
		}
		++lines;
	}
	return (0);
}

int		print_formatted(t_env *env)
{
	int *sizes;
	int lines;
	int cols;
	int tmp;
	int i;
	int j;
	int k;

	if (!(lines = get_lines(env)))
		return (-1);
	cols = (env->size / lines) + 1;
	if (!(sizes = (int *)malloc(sizeof(int) * cols)))
		return (0);
	i = -1;
	while (++i < cols)
		sizes[i] = 0;
	i = -1;
	while (++i < cols)
	{
		j = -1;
		while (++j < lines)
		{
			tmp = env->contents[(j * cols) + i].name_len + 2;
			sizes[i] = sizes[i] >= tmp ? sizes[i] : tmp;
		}
	}

	i = -1;
	while (++i < cols)
		ft_printf("sizes[%d] = %d\n", i, sizes[i]);

	i = -1;
	while (++i < lines)
	{
		j = -1;
		while (++j < cols)
			ft_printf("%-*s", sizes[j], env->contents[(i * cols) + j].name);
		ft_printf("\n");
	}
	free(sizes);
	return (1);
}
