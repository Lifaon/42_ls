/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meriadec <meriadec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:30:28 by meriadec          #+#    #+#             */
/*   Updated: 2019/04/08 00:49:48 by meriadec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	cmp_contents(t_dir *content, t_dir *tmp)
{
	int i;

	i = 0;
	while (content->d_name[i] && tmp->d_name[i] \
		&& content->d_name[i] == tmp->d_name[i])
		++i;
	if (content->d_name[i] <= tmp->d_name[i])
		return (1);
	return (0);
}

static void	sort_contents(t_dir ***contents, DIR *dir, int size)
{
	t_dir	*tmp;
	int		i;
	int		j;

	(*contents)[0] = readdir(dir);
	i = 0;
	while (++i < size)
	{
		tmp = readdir(dir);
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

static void	print_contents(t_dir **contents, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		ft_printf("%s\n", contents[i]->d_name);
	}
}

int			ft_readdir(char *path)
{
	DIR		*dir;
	t_dir	**contents;
	int		size;

	if (!(dir = ft_opendir(path)))
		return (1);
	size = 0;
	while (readdir(dir))
		++size;
	if (ft_closedir(dir))
		return (1);
	if (!(contents = (t_dir **)ft_malloc(sizeof(t_dir*) * size)))
		return (1);
	if (!(dir = ft_opendir(path)))
	{
		free(contents);
		return (1);
	}
	sort_contents(&contents, dir, size);
	print_contents(contents, size);
	free(contents);
	if (ft_closedir(dir))
		return (1);
	return (0);
}
