/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:41:35 by meriadec          #+#    #+#             */
/*   Updated: 2019/04/09 19:19:17 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

typedef struct dirent t_dir;
typedef struct stat t_stat;
typedef struct passwd t_usr;
typedef struct group t_grp;

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
	char		*fullpath;
}				t_data;

#endif
