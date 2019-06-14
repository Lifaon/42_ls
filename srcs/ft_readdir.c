/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:30:28 by meriadec          #+#    #+#             */
/*   Updated: 2019/06/14 11:38:26 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_next_dirent(t_data *data, DIR *dir, char *path, _Bool opt[128])
{
	t_dirent	*tmp;
	int			i;

	i = -1;
	while (path[++i] != '\0')
		if (path[i] == '/' && path[i+1] == '\0')
			path[i] = '\0';
	data->fullpath = NULL;
	if (opt['a'])
		tmp = readdir(dir);
	else
		while (tmp = readdir(dir))
			if (tmp->d_name[0] != '.')
				break ;
	if (tmp == NULL)
		return (-1);
	data->name_len = ft_snprintf(data->name, 256, tmp->d_name);
	if (ft_smprintf(&data->fullpath, "%s/%s", path, data->name) == -1)
		return (-1);
	if (get_data(data, opt))
	{
		free(data->fullpath);
		return (-1);
	}
	return (0);
}

static void	set_contents(t_env *env, DIR *dir)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (get_next_dirent(&env->contents[i], dir, env->path, env->opt))
			env->size--;
		else
			++i;
	}
	sort_contents(env);
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
