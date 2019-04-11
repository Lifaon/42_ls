/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:30:28 by meriadec          #+#    #+#             */
/*   Updated: 2019/04/11 09:26:03 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	cmp_contents(t_data content, t_data tmp, _Bool opt[128])
{
	int i;

	i = 0;
	while (content.name[i] && tmp.name[i] \
		&& content.name[i] == tmp.name[i])
		++i;
	if (content.name[i] <= tmp.name[i])
		return (1);
	return (0);
}

static void	sort_contents(t_env *env, DIR *dir)
{
	t_data	tmp;
	int		i;
	int		j;

	if (get_data(&env->contents[0], dir, env->path, env->opt))
		return ;
	i = 0;
	while (++i < env->size)
	{
		get_data(&tmp, dir, env->path, env->opt);
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
}

static void read_subcontents(t_env *env)
{
	int i;

	i = -1;
	// while (++i < size)
	// {
	// 	if (contents[i].type == 'd' && contents[i].name[0] != '.')
	// 		ft_readdir(contents[i].fullpath);
	// }
}

static void	free_contents(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->size)
	{
		if (env->contents[i].fullpath)
			free(env->contents[i].fullpath);
	}
	free(env->contents);
}

static int	init_env(t_env *env, char *path, _Bool opt[128])
{
	DIR			*dir;
	t_dirent	*dirent;
	int			i;

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

	if (init_env(&env, path, opt))
		return (0);
	if (!env.size)
		return (0);
	if (!(env.contents = (t_data *)ft_malloc(sizeof(t_data) * env.size)))
		return (1);
	if (!(dir = ft_opendir(env.path)))
	{
		free(env.contents);
		return (1);
	}
	sort_contents(&env, dir);
	print_contents(&env);
	read_subcontents(&env);
	free_contents(&env);
	if (ft_closedir(dir))
		return (1);
	return (0);
}
