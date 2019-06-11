/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_subcontents.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:43:00 by mlantonn          #+#    #+#             */
/*   Updated: 2019/06/11 19:37:29 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	read_subcontent(t_data content, t_env *env, _Bool p)
{
	static int	sub = 0;

	if (content.name[0] == '.' && (content.name[1] == '\0'
			|| (content.name[1] == '.' && content.name[2] == '\0')))
		return ;
	if (content.type == 'd' || (content.type == 'l' && p))
	{
		if (sub > 0 || env->printed > 0)
			ft_printf("\n");
		if (sub > 0 || env->size > 1)
			ft_printf("%s:\n", content.fullpath);
		ft_readdir(content.fullpath, env->opt);
		++sub;
	}
}

void		read_subcontents(t_env *env)
{
	int		i;
	_Bool	p;

	if (!env->opt['R'] && !env->opt['P'])
		return ;
	p = env->opt['P'];
	env->opt['P'] = 0;
	i = -1;
	while (++i < env->size)
		read_subcontent(env->contents[i], env, p);
}
