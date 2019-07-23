/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meriadec <meriadec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:41:35 by meriadec          #+#    #+#             */
/*   Updated: 2019/07/23 20:59:48 by mlantonn         ###   ########.fr       */
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
	char		rights[11];
	long int	links;
	char		usr_name[256];
	char		grp_name[256];
	long int	size;
	int			major;
	int			minor;
	long int	time_s;
	char		time[13];
	char		name[256];
	short		name_len;
	short		name_width;
	char		*fullpath;
	int			blocks;
}				t_data;

typedef struct	s_env
{
	t_data		*contents;
	char		*path;
	int			size;
	int			args;
	size_t		printed;
	_Bool		opt[128];
}				t_env;

#endif
