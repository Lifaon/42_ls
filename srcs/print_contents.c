/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_contents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:23:19 by mlantonn          #+#    #+#             */
/*   Updated: 2019/06/12 13:55:39 by mlantonn         ###   ########.fr       */
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

static void print_one_line(t_data content, int sizes[4])
{
	char link[261];

	link[0] = '\0';
	if (content.type == 'l')
	{
		ft_sprintf(link, " -> ");
		link[4 + readlink(content.fullpath, link + 4, 256)] = '\0';
	}
	ft_printf("%c%s %*ld %-*s %-*s %*ld %s %s%s\n", \
			content.type, content.rights, \
			sizes[0], content.links, \
			sizes[1], content.usr_name, \
			sizes[2], content.grp_name, \
			sizes[3], content.size, \
			content.time, content.name, link);
}

static void	print_details(t_env *env)
{
	int	sizes[4];
	int	blocks;
	int	i;

	if (env->path)
	{
		blocks = 0;
		i = -1;
		while (++i < env->size)
			blocks += env->contents[i].blocks;
		ft_printf("total %d\n", blocks);
	}
	get_sizes(&sizes, env);
	i = -1;
	while (++i < env->size)
	{
		if (env->opt['P'] && (env->contents[i].type == 'd'
			|| env->contents[i].type == 'l'))
			continue ;
		print_one_line(env->contents[i], sizes);
		env->printed++;
	}
}

void		print_contents(t_env *env)
{
	static int	sub = 0;
	int			i;

	if (env->opt['R'])
	{
		if (sub++ > 0 || env->printed > 0)
			ft_printf("\n");
		ft_printf("%s:\n", env->path);
	}
	if (!env->opt['l'])
	{
		i = -1;
		if (env->opt['1'] || print_formatted(env))
			while (++i < env->size)
			{
				if (!env->opt['P'] || (env->contents[i].type != 'd'
						&& env->contents[i].type != 'l'))
				{
					env->printed++;
					ft_printf("%s\n", env->contents[i].name);
				}
			}
	}
	else
		print_details(env);
}
