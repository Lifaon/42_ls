/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:30:28 by meriadec          #+#    #+#             */
/*   Updated: 2019/05/16 22:38:29 by mlantonn         ###   ########.fr       */
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

static int	sort_contents(t_env *env, DIR *dir)
{
	t_data	tmp;
	int		i;
	int		j;

	if (get_data(&env->contents[0], dir, env->path, env->opt))
		return (-1);
	i = 0;
	while (++i < env->size)
	{
		if (get_data(&tmp, dir, env->path, env->opt))
			return (-1);
		j = i;
		while (--j >= 0)
		{
			if (cmp_contents(env->contents[j], tmp, env->opt))
			{
				env->contents[j + 1] = tmp;
				break ;
			}
			else
				env->contents[j + 1] = env->contents[j];
		}
		if (j == -1)
			env->contents[0] = tmp;
	}
	return (0);
}

static void read_subcontents(t_env *env)
{
	t_data	*contents;
	int		i;

	contents = env->contents;
	i = -1;
	if (env->opt['R'])
		while (++i < env->size)
		{
			if (contents[i].name[0] == '.' && (contents[i].name[1] == '\0' \
				|| (contents[i].name[1] == '.' && contents[i].name[2] == '\0')))
				continue ;
			if (contents[i].type == 'd')
			{
				ft_printf("\n");
				ft_readdir(contents[i].fullpath, env->opt);
			}
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

	if (opt['R'])
		ft_printf("%s:\n", path);
	env->path = path;
	i = -1;
	while (++i < 128)
		env->opt[i] = opt[i];
	if (!(dir = ft_opendir(path)))
		return (1);
	env->size = 0;
	while ((dirent = readdir(dir)))
		if (opt['a'] || dirent->d_name[0] != '.')
			++env->size;
	if (ft_closedir(dir))
		return (1);
	return (0);
}

int			ft_readdir(char *path, _Bool opt[128])
{
	DIR		*dir;
	t_env	env;
	int		i;

	if (init_env(&env, path, opt))
		return (0);
	if (!env.size)
		return (0);
	if (!(env.contents = (t_data *)ft_malloc(sizeof(t_data) * env.size)))
		return (1);
	i = -1;
	while (++i < env.size)
		env.contents[i].fullpath = NULL;
	if (!(dir = ft_opendir(env.path)))
	{
		free(env.contents);
		return (1);
	}
	if (sort_contents(&env, dir))
		return (free_contents(&env, 1));
	if (ft_closedir(dir))
		return (free_contents(&env, 1));
	print_contents(&env);
	read_subcontents(&env);
	return (free_contents(&env, 0));
}
