/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:02:07 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/10 16:46:44 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_options(int ac, char **av, _Bool (*opt)[128])
{
	int args;
	int	i;
	int	j;

	args = 0;
	i = -1;
	while (++i < 128)
		(*opt)[i] = 0;
	i = 0;
	while (++i < ac)
	{
		j = -1;
		if (av[i][0] != '-' || av[i][1] == '\0')
			++args;
		else
			while (av[i][++j])
			{
				if (av[i][j] >= 0 && av[i][j] <= 128)
					(*opt)[av[i][j]] = 1;
				else
					return (-1);
			}
	}
	return (args);
}

int			main(int ac, char **av)
{
	_Bool	opt[128];
	int		args;
	int		i;

	i = 0;
	args = get_options(ac, av, &opt);
	if (args < 0)
	{
		ft_dprintf(2, "%s: invalid option.\n", av[0]);
		return (-1);
	}
	if (!args)
		return (ft_readdir(".", opt));
	else
		while (++i < ac)
			if (av[i][0] != '-' || av[i][1] == '\0')
			{
				if (!opt['R'] && args > 1)
					ft_printf("%s:\n", av[i]);
				if (ft_readdir(av[i], opt))
					return (1);
			}
	return (0);
}
