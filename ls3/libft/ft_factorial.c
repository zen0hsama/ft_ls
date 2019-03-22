/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:27:20 by jebrocho          #+#    #+#             */
/*   Updated: 2018/11/13 13:38:26 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_factorial(int n)
{
	if (n == 1 || n == 0)
		return (1);
	else if (n > 12 || n < 0)
		return (0);
	else
		return (n * ft_factorial(n - 1));
}
