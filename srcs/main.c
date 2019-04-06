/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:02:07 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/05 20:06:36 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"

#include <string.h>
#include <errno.h>
#include <dirent.h>

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

void	free_exit(int val, void *to_free)
{
	if (to_free)
		free(to_free);
	exit (val);
}

DIR	*ft_opendir(const char *path)
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

int		ft_readdir(int size, DIR *dir)
{
	t_dirent	**contents;
	t_dirent	*tmp;
	int			errno;
	int			i;
	int			j;

	if (!(contents = (t_dirent **)malloc(sizeof(t_dirent*) * size)))
	{
		ft_dprintf(2, "Malloc error: %s\n", strerror(errno));
		return (1);
	}
	i = -1;
	while (++i < size)
	{
		tmp = readdir(dir);
		j = -1;
		// while (++j < i)
	}
	free(contents);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	DIR			*dir;
	char		*pwd;
	int			size;
	int			i;

	pwd = ft_env_var(env, "PWD");
	if (!(dir = ft_opendir(pwd)))
		return (1);
	size = 0;
	while (readdir(dir))
		++size;
	if (ft_closedir(dir))
		return (1);
	if (!(dir = ft_opendir(pwd)))
		return (1);
	if (ft_readdir(size, dir))
		return (1);
	if (ft_closedir(dir))
		return (1);
	i = 0;
	return (0);
}
