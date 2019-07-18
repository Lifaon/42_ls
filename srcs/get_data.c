/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:21:44 by mlantonn          #+#    #+#             */
/*   Updated: 2019/07/18 11:43:08 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <errno.h>
#include "ft_ls.h"

static void	get_attr(char (*rights)[11], char *path)
{
	char	ptr[4097];
	int		ret;
	int		i;

	ret = listxattr(path, ptr, 4096, XATTR_NOFOLLOW);
	if (!ret)
		return ;
	(*rights)[10] = '\0';
	i = -1;
	while (++i < ret) {
		// TODO: change strstr to ft_strstr
		if (!strstr(ptr + i, "posix_acl_access"))
		{
			(*rights)[9] = '@';
			return ;
		}
		while (ptr[i])
			++i;
	}
	(*rights)[9] = '+';
}

static void	get_rights(char (*rights)[11], t_stat st)
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

static void	get_owners(t_data *data, t_stat st, _Bool opt[128])
{
	t_passwd	*usr;
	t_group		*grp;

	if (!opt['g'])
	{
		usr = getpwuid(st.st_uid);
		if (usr)
			ft_snprintf(data->usr_name, 256, usr->pw_name);
		else
			ft_snprintf(data->usr_name, 256, "%u", st.st_uid);
	}
	else
		data->usr_name[0] = '\0';
	grp = getgrgid(st.st_gid);
	if (grp)
		ft_snprintf(data->grp_name, 256, grp->gr_name);
	else
		ft_snprintf(data->grp_name, 256, "%u", st.st_gid);
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
		ft_printf_static("ft_ls: cannot access '%s': %s\n",
			data->fullpath, strerror(errno));
		return (-1);
	}
	data->type = get_type(st.st_mode);
	data->time_s = st.st_mtime;
	if (!opt['l'])
		return (0);
	get_rights(&data->rights, st);
	get_attr(&data->rights, data->fullpath);
	data->links = st.st_nlink;
	data->usr_name[0] = '\0';
	data->grp_name[0] = '\0';
	get_owners(data, st, opt);
	data->size = st.st_size;
	data->blocks = st.st_blocks;
	get_time(data, st.st_mtime);
	return (0);
}
