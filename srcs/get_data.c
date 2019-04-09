/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:21:44 by mlantonn          #+#    #+#             */
/*   Updated: 2019/04/09 18:12:52 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_fullpath(t_data *data, char *path)
{
	int size;
	int i;
	int j;

	j = 0;
	while (data->name[j])
		++j;
	i = 0;
	while (path[i])
		++i;
	size = sizeof(char) * (i + j + 2);
	if (!(data->fullpath = (char *)malloc(size)))
		return (1);
	ft_sprintf(data->fullpath, "%s/%s", path, data->name);
	return (0);
}

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

void		get_data(t_data *data, DIR *dir, char *path)
{
	t_dir	*tmp;
	t_stat	st;

	tmp = readdir(dir);
	ft_sprintf(data->name, tmp->d_name);
	if (get_fullpath(data, path))
		return ;
	if (stat(data->fullpath, &st))
		return ;
	data->type = get_type(tmp->d_type);
	get_rights(&data->rights, st);
}
