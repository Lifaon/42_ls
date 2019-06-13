/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:21:44 by mlantonn          #+#    #+#             */
/*   Updated: 2019/06/13 09:34:43 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "ft_ls.h"

static void	get_rights(char (*rights)[10], t_stat st)
{
	(*rights)[0] = (st.st_mode & S_IRUSR) ? 'r' : '-';
	(*rights)[1] = (st.st_mode & S_IWUSR) ? 'w' : '-';
	(*rights)[2] = (st.st_mode & S_IXUSR) ? 'x' : '-';
	(*rights)[3] = (st.st_mode & S_IRGRP) ? 'r' : '-';
	(*rights)[4] = (st.st_mode & S_IWGRP) ? 'w' : '-';
	(*rights)[5] = (st.st_mode & S_IXGRP) ? 'x' : '-';
	(*rights)[6] = (st.st_mode & S_IROTH) ? 'r' : '-';
	(*rights)[7] = (st.st_mode & S_IWOTH) ? 'w' : '-';
	(*rights)[8] = (st.st_mode & S_IXOTH) ? 'x' : '-';
	if (st.st_mode & S_ISUID && (*rights)[2] == 'x')
		(*rights)[2] = 's';
	else if (st.st_mode & S_ISUID && (*rights)[2] == '-')
		(*rights)[2] = 'S';
	if (st.st_mode & S_ISGID && (*rights)[5] == 'x')
		(*rights)[5] = 's';
	else if (st.st_mode & S_ISGID && (*rights)[5] == '-')
		(*rights)[5] = 'S';
	if (st.st_mode & S_ISVTX && (*rights)[8] == 'x')
		(*rights)[8] = 't';
	if (st.st_mode & S_ISVTX && (*rights)[8] == '-')
		(*rights)[8] = 'T';
	(*rights)[9] = '\0';
}

static char	get_type(mode_t md)
{
	if (S_ISREG(md))
		return ('-');
	if (S_ISDIR(md))
		return ('d');
	if (S_ISLNK(md))
		return ('l');
	if (S_ISFIFO(md))
		return ('p');
	if (S_ISBLK(md))
		return ('b');
	if (S_ISCHR(md))
		return ('c');
	if (S_ISSOCK(md))
		return ('s');
	return ('?');
}

static int	get_owners(t_data *data, t_stat st, _Bool opt[128])
{
	t_passwd	*usr;
	t_group		*grp;

	if (!opt['g'])
	{
		usr = getpwuid(st.st_uid);
		if (!usr)
		{
			ft_dprintf(2, "ft_ls: cannot get owner from '%s': %s",
				data->fullpath, strerror(errno));
			return (-1);
		}
		ft_snprintf(data->usr_name, 256, usr->pw_name);
	}
	else
		data->usr_name[0] = '\0';
	grp = getgrgid(st.st_gid);
	if (!grp)
	{
		ft_dprintf(2, "ft_ls: cannot get group from '%s': %s",
			data->fullpath, strerror(errno));
		return (-1);
	}
	ft_snprintf(data->grp_name, 256, grp->gr_name);
	return (0);
}

static void	get_time(t_data *data, time_t s_file)
{
	time_t	s_now;
	char	buff[25];

	ft_snprintf(buff, 25, ctime(&s_file));
	s_now = time(NULL);
	if (s_now - s_file < SIX_MONTHS)
		ft_snprintf(data->time, 13, buff + 4);
	else
	{
		ft_snprintf(data->time, 8, buff + 4);
		ft_snprintf(data->time + 7, 6, buff + 19);
	}
}

int			get_data(t_data *data, _Bool opt[128])
{
	t_stat	st;

	if (lstat(data->fullpath, &st))
	{
		ft_dprintf(2, "ft_ls: cannot access '%s': %s\n",
			data->fullpath, strerror(errno));
		return (-1);
	}
	data->type = get_type(st.st_mode);
	data->time_s = st.st_mtim.tv_sec;
	if (!opt['l'])
		return (0);
	get_rights(&data->rights, st);
	data->links = st.st_nlink;
	data->usr_name[0] = '\0';
	data->grp_name[0] = '\0';
	if (get_owners(data, st, opt))
		return (-1);
	data->size = st.st_size;
	data->blocks = st.st_blocks;
	get_time(data, st.st_mtim.tv_sec);
	return (0);
}

int			get_next_dirent(t_data *data, DIR *dir, char *path, _Bool opt[128])
{
	t_dirent	*tmp;
	int			i;

	i = -1;
	while (path[++i] != '\0')
		if (path[i] == '/' && path[i+1] == '\0')
			path[i] = '\0';
	data->fullpath = NULL;
	if (opt['a'])
		tmp = readdir(dir);
	else
		while (tmp = readdir(dir))
			if (tmp->d_name[0] != '.')
				break ;
	if (tmp == NULL)
		return (-1);
	data->name_len = ft_snprintf(data->name, 256, tmp->d_name);
	if (ft_smprintf(&data->fullpath, "%s/%s", path, data->name) == -1)
		return (-1);
	if (get_data(data, opt))
	{
		free(data->fullpath);
		return (-1);
	}
	return (0);
}
