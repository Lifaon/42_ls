/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attr_and_acl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:38:28 by mlantonn          #+#    #+#             */
/*   Updated: 2019/07/23 19:14:00 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <sys/acl.h>
#include "ft_ls.h"

static int	get_attr(char (*rights)[11], char *path)
{
	int	ret;

	ret = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (ret <= 0)
		return (0);
	(*rights)[9] = '@';
	(*rights)[10] = '\0';
	return (1);
}

static int	get_acl(char (*rights)[11], char *path)
{
	acl_t	my_acl;

	my_acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (my_acl == NULL)
		return (0);
	acl_free(my_acl);
	(*rights)[9] = '+';
	(*rights)[10] = '\0';
	return (1);
}

void		get_attr_and_acl(char (*rights)[11], char *path)
{
	if (!get_attr(rights, path))
		get_acl(rights, path);
}
