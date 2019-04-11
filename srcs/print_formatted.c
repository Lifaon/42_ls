/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:04:19 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/11 17:47:11 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_lines_len(t_env *env, int lines)
{
	int	cols;
	int	tmp;
	int	len;
	int	i;
	int	j;

	i = -1;
	len = 0;
	cols = (env->size / lines) + 1;
	while (++i < lines)
	{
		j = -1;
		tmp = 0;
		while (++j < cols)
		{
			if ((j * lines) + i < env->size)
				tmp += env->contents[(j * lines) + i].name_len + 2;
		}
		len = len >= tmp ? len : tmp;
	}
	return (len);
}

static void	set_name_width(t_env *env, int lines)
{
	int cols;
	int tmp;
	int i;
	int j;
	int k;

	cols = (env->size / lines) + 1;
	i = -1;
	while (++i < cols)
		env->contents[i].name_width = 0;
	i = -1;
	while (++i < lines)
	{
		j = -1;
		while (++j < cols)
		{
			k = (j * lines) + i;
			tmp = k < env->size ? env->contents[k].name_len + 2 : 0;
			env->contents[j].name_width = env->contents[j].name_width >= tmp \
				? env->contents[j].name_width : tmp;
		}
	}
}

static int	get_lines(t_env *env)
{
	t_winsize	ws;
	int			lines;

	if (ioctl(1, TIOCGWINSZ, &ws))
		return (0);
	lines = 1;
	while (lines < ((env->size) / 2) + 1)
	{
		if (get_lines_len(env, lines) < ws.ws_col)
		{
			set_name_width(env, lines);
			return (lines);
		}
		++lines;
	}
	return (0);
}

int			print_formatted(t_env *env)
{
	int lines;
	int cols;
	int i;
	int j;

	if (!(lines = get_lines(env)))
		return (1);
	cols = (env->size / lines) + 1;
	i = -1;
	while (++i < lines)
	{
		j = -1;
		while (++j < cols)
			if ((j * lines) + i < env->size)
				ft_printf("%-*s", env->contents[j].name_width, \
					env->contents[(j * lines) + i].name);
		ft_printf("\n");
	}
	return (0);
}