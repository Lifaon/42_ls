/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:30:28 by meriadec          #+#    #+#             */
/*   Updated: 2019/06/11 17:17:40 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	cmp_contents(t_data content, t_data tmp, _Bool opt[128])
{
	int i;

	i = 0;
	if (!opt['t'])
	{
		while (content.name[i] && tmp.name[i] \
			&& content.name[i] == tmp.name[i])
			++i;
		if (!opt['r'])
			return (content.name[i] < tmp.name[i]);
		return (content.name[i] > tmp.name[i]);
	}
	else {
		if (!opt['r'])
			return (content.time_s > tmp.time_s);
		return (content.time_s <= tmp.time_s);
	}
	return (1);
}

static void	sort_contents(t_env *env, DIR *dir)
{
	t_data	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < env->size)
	{
		if (get_next_dirent(&tmp, dir, env->path, env->opt))
		{
			env->size--;
			continue ;
		}
		j = i++;
		while (--j >= 0)
		{
			if (cmp_contents(env->contents[j], tmp, env->opt))
			{
				env->contents[j + 1] = tmp;
				break ;
			}
			env->contents[j + 1] = env->contents[j];
		}
		if (j == -1)
			env->contents[0] = tmp;
	}
}

static int	free_contents(t_env *env, int ret)
{
	int i;

	i = -1;
	while (++i < env->size)
	{
		if (env->contents[i].fullpath)
		{
			free(env->contents[i].fullpath);
			env->contents[i].fullpath = NULL;
		}
	}
	free(env->contents);
	return (ret);
}

static int	init_env(t_env *env, char *path, _Bool opt[128])
{
	DIR			*dir;
	t_dirent	*dirent;
	int			i;

	env->path = path;
	env->size = 0;
	env->printed = 0;
	i = -1;
	while (++i < 128)
		env->opt[i] = opt[i];
	if (!(dir = ft_opendir(path)))
		return (1);
	while ((dirent = readdir(dir)))
		if (opt['a'] || dirent->d_name[0] != '.')
			++env->size;
	if (ft_closedir(dir))
		return (1);
	return (!env->size);
}

int			ft_readdir(char *path, _Bool opt[128])
{
	DIR		*dir;
	t_env	env;
	int		i;

	if (init_env(&env, path, opt))
		return (0);
	if (!(env.contents = (t_data *)ft_malloc(sizeof(t_data) * env.size)))
		return (1);
	i = -1;
	while (++i < env.size)
		env.contents[i].fullpath = NULL;
	if (!(dir = ft_opendir(env.path)))
		return (free_contents(&env, 1));
	sort_contents(&env, dir);
	if (ft_closedir(dir))
		return (free_contents(&env, 1));
	print_contents(&env);
	read_subcontents(&env);
	return (free_contents(&env, 0));
}
