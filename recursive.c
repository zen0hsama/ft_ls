/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:25:55 by ezonda            #+#    #+#             */
/*   Updated: 2019/03/22 16:43:26 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int		ft_count_names(char *strpath, t_flags *flag)
{
	DIR				*dir;
	struct dirent	*diread;
	int				count;

	count = 0;
	dir = opendir(strpath);
	if (dir == NULL)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(ft_strrchr(strpath, '/'), 2);
		perror(" ");
		return (-1);
	}
	while ((diread = readdir(dir)) != NULL)
	{
		if (flag->a == 0 && diread->d_name[0] == '.')
			continue ;
		count++;
	}
	closedir(dir);
	return (count);
}

static void		ft_stock_names(char *strpath, char **stock, t_flags *flag)
{
	DIR				*dir;
	struct dirent	*diread;
	int				i;

	i = 0;
	dir = opendir(strpath);
	while ((diread = readdir(dir)) != NULL)
	{
		if (flag->a == 0 && diread->d_name[0] == '.')
			continue ;
		else if (flag->a == 1)
		{
			if (diread->d_name[0] == '.'
					&& (diread->d_name[1] == '.' || diread->d_name[1] == '\0'))
				continue ;
		}
		stock[i] = ft_strdup(diread->d_name);
		i++;
	}
	closedir(dir);
	stock[i] = NULL;
}

static char		*ft_init_new_path(char *str, char *stock, int mod)
{
	char	*new;
	char	*tmp;

	if (mod == 1)
	{
		if (!(new = ft_strjoin(str, stock)))
			return (NULL);
	}
	else
	{
		if (!(tmp = ft_strjoin(stock, "/")))
			return (NULL);
		if (!(new = ft_strjoin(str, tmp)))
			return (NULL);
		free(tmp);
	}
	return (new);
}

static void		ft_recursive_p2(char *str, char **stock, t_flags *f, t_var *v)
{
	int		i;
	char	*recursive_path;

	i = 0;
	while (stock[i])
	{
		v->path = ft_init_new_path(str, stock[i], 1);
		if (stat(v->path, &st) < 0)
		{
			free(v->path);
			while (stock[i])
				free(stock[i++]);
			free(stock);
			return ;
		}
		free(v->path);
		if (S_ISDIR(st.st_mode))
		{
			recursive_path = ft_init_new_path(str, stock[i], 2);
			ft_recursive_flag(recursive_path, f, v);
			free(recursive_path);
		}
		free(stock[i++]);
	}
	free(stock);
}

void			ft_recursive_flag(char *str, t_flags *flag, t_var *v)
{
	char	**stock;
	int		name_count;

	v->path = str;
	name_count = ft_count_names(v->path, flag);
	if (name_count == -1)
		return ;
	if (!(stock = (char**)malloc(sizeof(char*) * name_count + 1)))
		return ;
	ft_stock_names(v->path, stock, flag);
	ft_printf("%s:\n", v->path);
	print_ls(v, flag);
	ft_putchar('\n');
	if (flag->l == 0)
		ft_putchar('\n');
	ft_recursive_p2(str, stock, flag, v);
}
