/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_contents.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 10:19:11 by mlantonn          #+#    #+#             */
/*   Updated: 2019/07/23 17:19:41 by mlantonn         ###   ########.fr       */
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

static void	swap(t_data *a, t_data *b)
{
	t_data	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(t_data *contents, int low, int high, _Bool opt[128])
{
	t_data	pivot;
	int		i;
	int		j;

	pivot = contents[high];
	i = low - 1;
	j = i;
	while (++j <= high - 1)
		if (cmp_contents(contents[j], pivot, opt))
			swap(&contents[++i], &contents[j]);
	swap(&contents[++i], &contents[high]);
	return (i);
}

static void	quick_sort(t_data *contents, int low, int high, _Bool opt[128])
{
	int p;

	if (low < high)
	{
		p = partition(contents, low, high, opt);
		quick_sort(contents, low, p - 1, opt);
		quick_sort(contents, p + 1, high, opt);
	}
}

void		sort_contents(t_env *env)
{
	if (env->opt['f'])
		return ;
	quick_sort(env->contents, 0, env->size - 1, env->opt);
}
