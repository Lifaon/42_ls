/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:30:28 by meriadec          #+#    #+#             */
/*   Updated: 2019/06/12 14:33:44 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	cmp_contents(t_data content, t_data tmp, _Bool opt[128])
{
	int i;

	if (opt['t'] && content.time_s != tmp.time_s)
	{
		if (!opt['r'])
			return (content.time_s > tmp.time_s);
		return (content.time_s < tmp.time_s);
	}
	i = 0;
	while (content.name[i] && tmp.name[i]
		&& content.name[i] == tmp.name[i])
		++i;
	if (!opt['r'])
		return (content.name[i] < tmp.name[i]);
	return (content.name[i] > tmp.name[i]);
}

void		sort_contents(t_env *env, t_data tmp, int i)
{
	while (--i >= 0)
	{
		if (cmp_contents(env->contents[i], tmp, env->opt))
		{
			env->contents[i + 1] = tmp;
			break ;
		}
		env->contents[i + 1] = env->contents[i];
	}
	if (i == -1)
		env->contents[0] = tmp;
}

static void	set_contents(t_env *env, DIR *dir)
{
	t_data	tmp;
	int		i;

	i = 0;
	while (i < env->size)
	{
		if (get_next_dirent(&tmp, dir, env->path, env->opt))
			env->size--;
		else
			sort_contents(env, tmp, i++);
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
	env->args = 0;
	env->printed = 0;
	i = -1;
	while (++i < 128)
		env->opt[i] = opt[i];
	if (opt['R'] && opt['P'])
		env->opt['P'] = 0;
	if (!(dir = ft_opendir(path)))
		return (1);
	while ((dirent = readdir(dir)))
		if (opt['a'] || dirent->d_name[0] != '.')
			++env->size;
	env->args = env->size;
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
		return (1);
	if (!(env.contents = (t_data *)ft_malloc(sizeof(t_data) * env.size)))
		return (1);
	i = -1;
	while (++i < env.size)
		env.contents[i].fullpath = NULL;
	if (!(dir = ft_opendir(env.path)))
		return (free_contents(&env, 1));
	set_contents(&env, dir);
	if (ft_closedir(dir))
		return (free_contents(&env, 1));
	print_contents(&env);
	read_subcontents(&env);
	return (free_contents(&env, 0));
}
