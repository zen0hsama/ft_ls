/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:45:34 by jebrocho          #+#    #+#             */
/*   Updated: 2019/03/04 15:43:45 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	ft_display_attr(t_var *v)
{
	char *pathname;

	pathname = ft_strjoin(v->path, v->first);
	if (listxattr(pathname, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_printf("@");
	else
		ft_printf(" ");
	free(pathname);
}

void	initialize_stock_dir(t_var *v)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (v->path_long[i])
	{
		if (is_directory(v->path_long[i], v) == 1)
			j++;
		i++;
	}
	if (j > 1)
		v->file_path = 1;
	if (!(v->stock_d = (char**)malloc(sizeof(char*) * j + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i <= j)
		v->stock_d[i++] = NULL;
}

int		is_directory(char *str, t_var *v)
{
	if ((v->dir = opendir(str)) == NULL)
		return (0);
	closedir(v->dir);
	return (1);
}

char	**rev_order(char **tab)
{
	char	**tab_save;
	int		i;
	int		j;
	int		k;

	i = 1;
	j = 1;
	while (tab[i])
		i++;
	if (!(tab_save = (char**)malloc(sizeof(char*) * i + 1)))
		return (NULL);
	k = i;
	tab_save[0] = ft_strdup(tab[0]);
	while (j < k)
	{
		tab_save[j] = ft_strdup(tab[i - 1]);
		j++;
		i--;
	}
	tab_save[j] = NULL;
	return (tab_save);
}

void	padding_multi(t_var *v)
{
	int i;
	int j;

	i = 1;
	j = 1;
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		while (v->path_long[j])
		{
			if (ft_strcmp(v->path_long[j], diread->d_name) != 0)
				i++;
			j++;
		}
		if (i < j)
			padding_initialisation(v);
		i = 1;
		j = 1;
	}
	closedir(v->dir);
}
