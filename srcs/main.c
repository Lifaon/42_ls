/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:02:07 by mlantonn          #+#    #+#             */
/*   Updated: 2019/07/23 22:13:43 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	is_illegal_option(char c)
{
	if (c == 'P' || c == 'R' || c == 'U' || c == 'a' || c == 'f' || c == 'g'
		|| c == 'l' || c == 'n' || c == 'o' || c == 'r' || c == 't' || c == '1')
		return (0);
	ft_dprintf(2, "ft_ls: illegal option -- '%c'\n", c);
	ft_dprintf(2, "usage: ft_ls [-PRUafglnort1] [file...]\n");
	return (1);
}

static void	set_options(_Bool (*opt)[128])
{
	if ((*opt)['f'])
	{
		(*opt)['a'] = 1;
		(*opt)['U'] = 1;
	}
	if ((*opt)['g'] || (*opt)['n'] || (*opt)['o'])
		(*opt)['l'] = 1;
}

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
		j = 0;
		if (av[i][0] != '-' || av[i][1] == '\0')
			++args;
		else
			while (av[i][++j])
			{
				if (is_illegal_option(av[i][j]))
					return (-1);
				(*opt)[av[i][j]] = 1;
			}
	}
	set_options(opt);
	return (args);
}

int			main(int ac, char **av)
{
	_Bool	opt[128];
	int		args;

	args = get_options(ac, av, &opt);
	if (args < 0)
		return (-1);
	if (!args)
		return (ft_readdir(".", opt));
	else
		ft_readargs(ac, av, args, opt);
	return (0);
}
