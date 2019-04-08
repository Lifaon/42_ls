/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:02:07 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/08 13:13:42 by mlantonn         ###   ########.fr       */
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
