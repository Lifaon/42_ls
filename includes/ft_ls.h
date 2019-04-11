/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:01:30 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/10 19:37:53 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <time.h>

# include "ft_printf.h"
# include "structs.h"

int		ft_readdir(char *path, _Bool opt[128]);
int		get_data(t_data *data, DIR *dir, char *path, _Bool opt[128]);
void	print_contents(t_env *env);

/*
**	Utils.
*/
void	*ft_malloc(unsigned long long size);
DIR		*ft_opendir(const char *path);
int		ft_closedir(DIR *dir);
int		ft_shortstrlen(char str[256]);
int		ft_uintsize(unsigned int nb);

#endif
