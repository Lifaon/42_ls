/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:30:28 by meriadec          #+#    #+#             */
/*   Updated: 2019/04/09 19:18:23 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	cmp_contents(t_data content, t_data tmp)
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

static void	sort_contents(t_data **contents, DIR *dir, char *path, int size)
{
	t_data	tmp;
	int		i;
	int		j;

	get_data(contents[0], dir, path);
	i = 0;
	while (++i < size)
	{
		get_data(&tmp, dir, path);
		j = i;
		while (--j >= 0)
		{
			if (cmp_contents((*contents)[j], tmp))
			{
				(*contents)[j + 1] = tmp;
				break ;
			}
			else
					(*contents)[j + 1] = (*contents)[j];
		}
		if (j == -1)
			(*contents)[0] = tmp;
	}
}

static void	print_contents(t_data *arr, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		ft_printf("%c%s %d %s %s %d %s %s\n", arr[i].type, arr[i].rights, \
			arr[i].links, arr[i].usr_name, arr[i].grp_name, arr[i].size, \
			arr[i].time, arr[i].name);
	}
}

static void	free_contents(t_data *contents, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		free(contents[i].fullpath);
	}
	free(contents);
}

int			ft_readdir(char *path)
{
	DIR		*dir;
	t_data	*contents;
	int		size;

	if (!(dir = ft_opendir(path)))
		return (1);
	size = 0;
	while (readdir(dir))
		++size;
	if (ft_closedir(dir))
		return (1);
	if (!(contents = (t_data *)ft_malloc(sizeof(t_data) * size)))
		return (1);
	if (!(dir = ft_opendir(path)))
	{
		free(contents);
		return (1);
	}
	sort_contents(&contents, dir, path, size);
	print_contents(contents, size);
	free_contents(contents, size);
	if (ft_closedir(dir))
		return (1);
	return (0);
}
