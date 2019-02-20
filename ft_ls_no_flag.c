/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_no_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:58:42 by jebrocho          #+#    #+#             */
/*   Updated: 2019/02/20 17:06:18 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void		ft_print(t_var *v, t_flags *f)
{
	if (strcmp(v->first, v->last) == 0)
	{
		ft_printf("%s", v->first);
		if (v->file_path == 1 && v->c_dir == 1)
			ft_putstr("\n\n");
		return ;
	}
	else
		ft_printf("%-*s ", v->len, v->first);
	if (v->is_link == 1)
		return ;
	if (f->l == 1)
		printf("\n");
}

void		padding_initialisation(t_var *v, t_flags *f)
{
	if (stat(ft_strjoin(v->path, diread->d_name), &st) < 0)
		return ;
	if (v->len_file < count_lenf(st.st_size))
		v->len_file = count_lenf(st.st_size);
	if (v->len_link < count_lenf(st.st_nlink))
		v->len_link = count_lenf(st.st_nlink);
}

void	init_len_n_last(t_var *v, t_flags *f)
{
	v->len = 0;
	v->dir = opendir(v->path);
	while ((diread = readdir(v->dir)) != NULL)
	{
		if (f->a == 0 && diread->d_name[0] == '.')
			continue ;
		if (v->len == 0)
		{
			v->first = ft_strdup(diread->d_name);
			v->last = ft_strdup(diread->d_name);
		}
		if (v->len < ft_strlen(diread->d_name))
			v->len = ft_strlen(diread->d_name);
		if (ft_strcmp(v->last, diread->d_name) < 0)
			v->last = ft_strdup(diread->d_name);
		if ((ft_strcmp(v->first, diread->d_name) > 0) && f->a == 0)
			v->first = ft_strdup(diread->d_name);
		padding_initialisation(v, f);
	}
	init_rev(v, f);
	v->mid = v->first;
	closedir(v->dir);
}

void		ascii_order(t_var *v, t_flags *f)
{
	if (f->l == 1)
		v->len = 0;
	ft_print(v, f);
	v->save = opendir(v->path);
	while ((diread = readdir(v->save)) != NULL)
	{
		if (diread->d_name[0] == '.' && f->a == 0)
			continue ;
		if (f->r == 1)
		{
			ascii_rev(v, f);
			continue ;
		}
		if ((ft_strcmp(v->first, diread->d_name) < 0) && v->mid == NULL)
			v->mid = ft_strdup(diread->d_name);
		if (ft_strcmp(v->first, v->mid) == 0
				&& (ft_strcmp(v->first, diread->d_name) < 0))
			v->mid = ft_strdup(diread->d_name);
		if ((ft_strcmp(v->first, diread->d_name) < 0)
				&& (ft_strcmp(v->mid, diread->d_name) > 0))
			v->mid = ft_strdup(diread->d_name);
	}
	closedir(v->save);
	v->first = v->mid;
}

int		ft_ls_no_flag(t_var *v, t_flags *f)
{
	v->path = ft_strdup(".");
	init_len_n_last(v, f);
	v->dir = opendir(".");
	if (ft_strcmp(v->first, v->last) != 0)
		while ((diread = readdir(v->dir)) != NULL
				&& ft_strcmp(v->first, v->last) != 0)
			ascii_order(v, f);
	closedir(v->dir);
	ft_print(v, f);
	return (1);
}
