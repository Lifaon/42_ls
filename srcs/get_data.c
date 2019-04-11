/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:21:44 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/11 19:26:59 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	get_type(unsigned char type)
{
	if (type == DT_REG)
		return ('-');
	if (type == DT_DIR)
		return ('d');
	if (type == DT_LNK)
		return ('l');
	if (type == DT_FIFO)
		return ('p');
	if (type == DT_BLK)
		return ('b');
	if (type == DT_CHR)
		return ('c');
	if (type == DT_SOCK)
		return ('s');
	return ('?');
}

static int	get_next_dirent(t_data *data, DIR *dir, char *path, _Bool opt[128])
{
	t_dirent *tmp;

	data->fullpath = NULL;
	if (opt['a'])
		tmp = readdir(dir);
	else
	{
		while (tmp = readdir(dir))
		{
			if (tmp->d_name[0] != '.')
				break ;
		}
	}
	if (tmp == NULL)
		return (-1);
	data->name_len = ft_snprintf(data->name, 256, tmp->d_name);
	data->type = get_type(tmp->d_type);
	if (ft_smprintf(&data->fullpath, "%s/%s", path, data->name) == -1)
		return (-1);
	return (0);
}

int			get_data(t_data *data, DIR *dir, char *path, _Bool opt[128])
{
	t_stat		st;
	t_passwd	*usr;
	t_group		*grp;

	if (get_next_dirent(data, dir, path, opt))
		return (-1);
	if (!opt['l'] && !opt['t'])
		return (0);
	if (stat(data->fullpath, &st))
		return (-1);
	data->time_s = st.st_mtim.tv_sec;
	if (!opt['l'])
		return (0);
	get_rights(&data->rights, st);
	data->links = st.st_nlink;
	usr = getpwuid(st.st_uid);
	grp = getgrgid(st.st_gid);
	if (!usr || !grp)
		return (-1);
	ft_snprintf(data->usr_name, 256, usr->pw_name);
	ft_snprintf(data->grp_name, 256, grp->gr_name);
	data->size = st.st_size;
	data->blocks = st.st_blocks;
	ft_snprintf(data->time, 13, ctime(&st.st_mtim.tv_sec) + 4);
	return (0);
}
