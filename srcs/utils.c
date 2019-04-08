/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:18:39 by meriadec          #+#    #+#             */
/*   Updated: 2019/04/08 13:26:11 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_exit(int val, void *to_free)
{
	if (to_free)
		free(to_free);
	exit (val);
}

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

char	*ft_env_var(char **env, char *var)
{
	int i;
	int j;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] && var[j])
		{
			if (env[i][j] != var[j])
				break ;
			++j;
		}
		if (var[j] == '\0')
			return (env[i] + j + 1);
		++i;
	}
	return (NULL);
}
