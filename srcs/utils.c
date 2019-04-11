/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:18:39 by meriadec          #+#    #+#             */
/*   Updated: 2019/04/10 13:44:18 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_malloc(unsigned long long size)
{
	int errno;
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_dprintf(2, "Malloc error: %s\n", strerror(errno));
		return (NULL);
	}
	return (ptr);
}

DIR		*ft_opendir(const char *path)
{
	DIR	*ret;
	int	errno;

	ret = opendir(path);
	if (ret == NULL)
	{
		ft_dprintf(2, "Error opening '%s': %s\n", path, strerror(errno));
		return (NULL);
	}
	return (ret);
}

int		ft_closedir(DIR *dir)
{
	int ret;
	int	errno;

	ret = closedir(dir);
	if (ret)
		ft_dprintf(2, "Error closing DIR *stream: %s\n", strerror(errno));
	return (ret);
}

int		ft_shortstrlen(char str[256])
{
	int i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int		ft_uintsize(unsigned int nb)
{
	int size;

	size = 1;
	while (nb >= 10)
	{
		nb /= 10;
		++size;
	}
	return (size);
}
