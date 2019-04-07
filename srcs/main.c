/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meriadec <meriadec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:02:07 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/08 00:48:28 by meriadec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av, char **env)
{
	char	*pwd;

	pwd = ft_env_var(env, "PWD");
	if (ft_readdir(pwd))
		return (1);
	return (0);
}
