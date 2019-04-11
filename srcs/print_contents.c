/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_contents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:23:19 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/11 12:02:04 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void get_sizes(int (*sizes)[4], t_env *env)
{
	int	tmp;
	int	i;

	i = -1;
	while (++i < 4)
		(*sizes)[i] = 0;
	i = -1;
	while (++i < env->size)
	{
		tmp = ft_uintsize(env->contents[i].links);
		(*sizes)[0] = ((*sizes)[0] >= tmp) ? (*sizes)[0] : tmp;
		tmp = ft_shortstrlen(env->contents[i].usr_name);
		(*sizes)[1] = ((*sizes)[1] >= tmp) ? (*sizes)[1] : tmp;
		tmp = ft_shortstrlen(env->contents[i].grp_name);
		(*sizes)[2] = ((*sizes)[2] >= tmp) ? (*sizes)[2] : tmp;
		tmp = ft_uintsize(env->contents[i].size);
		(*sizes)[3] = ((*sizes)[3] >= tmp) ? (*sizes)[3] : tmp;
	}
}

static void	print_details(t_env *env)
{
	int	sizes[4];
	int	blocks;
	int	i;

	if (env->opt['R'])
		ft_printf("%s:\n", env->path);
	blocks = 0;
	i = -1;
	while (++i < env->size)
		blocks += env->contents[i].blocks;
	ft_printf("total %d\n", blocks);
	get_sizes(&sizes, env);
	i = -1;
	while (++i < env->size)
		ft_printf("%c%s %*ld %-*s %-*s %*ld %s %s\n", \
			env->contents[i].type, env->contents[i].rights, \
			sizes[0], env->contents[i].links, \
			sizes[1], env->contents[i].usr_name, \
			sizes[2], env->contents[i].grp_name, \
			sizes[3], env->contents[i].size, \
			env->contents[i].time, env->contents[i].name);
}

static int	print_formatted(t_env *env, int lines)
{
	int *sizes;
	int cols;
	int tmp;
	int i;
	int j;
	int k;

	cols = (env->size / lines) + 1;
	ft_printf("%d cols / %d lines\n", cols, lines);
	if (!(sizes = (int *)malloc(sizeof(int) * cols)))
		return (0);
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
	return (1);
}

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
		return (-1);
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
				if ((j * lines) + i < env->size && tmp < env->contents[(j * lines) + i].name_len)
					tmp = env->contents[(j * lines) + i].name_len;
			}
			len += tmp;
			
		}
		if (len < ws.ws_col)
			return (print_formatted(env, lines));
		++lines;
	}
	return (0);
}

void		print_contents(t_env *env)
{
	int	i;

	if (!env->opt['l'])
	{
		i = -1;
		can_be_formatted(env);
		// if (env->opt['1']);
		// 	while (++i < env->size)
		// 		ft_printf("%s\n", env->contents[i].name);
	}
	else
		print_details(env);
}