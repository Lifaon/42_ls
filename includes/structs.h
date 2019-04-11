/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:41:35 by meriadec          #+#    #+#             */
/*   Updated: 2019/04/10 18:12:12 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/ioctl.h>

typedef struct dirent t_dirent;
typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct group t_group;
typedef struct winsize t_winsize;

typedef struct	s_data
{
	char		type;
	char		rights[10];
	long int	links;
	char		usr_name[256];
	char		grp_name[256];
	long int	size;
	char		time[13];
	char		name[256];
	char		name_len;
	char		*fullpath;
	int			blocks;
}				t_data;

typedef struct	s_env
{
	t_data		*contents;
	char		*path;
	int			size;
	_Bool		opt[128];
}				t_env;

#endif
