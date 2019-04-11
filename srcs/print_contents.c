/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_contents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:23:19 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/11 19:45:05 by mlantonn         ###   ########.fr       */
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

	blocks = 0;
	i = -1;
	while (++i < env->size)
		blocks += env->contents[i].blocks;
	get_sizes(&sizes, env);
	i = -1;
	while (++i < env->size)
	{
		ft_printf("%c%s %*ld %-*s %-*s %*ld %s %s\n", \
			env->contents[i].type, env->contents[i].rights, \
			sizes[0], env->contents[i].links, \
			sizes[1], env->contents[i].usr_name, \
			sizes[2], env->contents[i].grp_name, \
			sizes[3], env->contents[i].size, \
			env->contents[i].time, env->contents[i].name);
	}
}

void		print_contents(t_env *env)
{
	int	i;

	if (!env->opt['l'])
	{
		i = -1;
		if (env->opt['1'] || print_formatted(env))
			while (++i < env->size)
				ft_printf("%s\n", env->contents[i].name);
	}
	else
		print_details(env);
}
