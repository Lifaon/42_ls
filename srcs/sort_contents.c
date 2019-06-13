/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_contents.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 10:19:11 by mlantonn          #+#    #+#             */
/*   Updated: 2019/06/13 10:19:20 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	cmp_contents(t_data content, t_data tmp, _Bool opt[128])
{
	int i;

	if (opt['t'] && content.time_s != tmp.time_s)
	{
		if (!opt['r'])
			return (content.time_s > tmp.time_s);
		return (content.time_s < tmp.time_s);
	}
	i = 0;
	while (content.name[i] && tmp.name[i]
		&& content.name[i] == tmp.name[i])
		++i;
	if (!opt['r'])
		return (content.name[i] < tmp.name[i]);
	return (content.name[i] > tmp.name[i]);
}

void		sort_contents(t_env *env, t_data tmp, int i)
{
	if (env->opt['U'])
	{
		env->contents[i] = tmp;
		return ;
	}
	while (--i >= 0)
	{
		if (cmp_contents(env->contents[i], tmp, env->opt))
		{
			env->contents[i + 1] = tmp;
			break ;
		}
		env->contents[i + 1] = env->contents[i];
	}
	if (i < 0)
		env->contents[0] = tmp;
}
