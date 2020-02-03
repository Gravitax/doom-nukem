/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/04 22:15:02 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void		ft_tswap(t_triangle *buffer, int p1, int p2)
{
    t_triangle	tmp;

    tmp = buffer[p1];
    buffer[p1] = buffer[p2];
    buffer[p2] = tmp;
}

static float	get_zvalue(t_triangle *buffer, int pos)
{
    return (buffer[pos].v[0].z
        + buffer[pos].v[1].z
        + buffer[pos].v[2].z);
}

static int		ft_partition(t_triangle *buffer, int start, int size)
{
	int			i;
	int			j;
	int			pivot;

	i = start - 1;
	j = start - 1;
	pivot = size - 1;
	if (size - start == 2)
	{
		if (get_zvalue(buffer, start) < get_zvalue(buffer, size - 1))
            ft_tswap(buffer, start, size - 1);
		return (0);
	}
	while (i < size - 1 && ++j < size - 1)
	{
		if (get_zvalue(buffer, i) > get_zvalue(buffer, j))
            ft_tswap(buffer, i++, j);
	}
    ft_tswap(buffer, i + 1, pivot);
	return (i + 1);
}

void			ft_quicksort(t_triangle *buffer, int start, int size)
{
	int	i;

	if (start < size - 1)
	{
		i = ft_partition(buffer, start, size);
		ft_quicksort((&buffer[start]), 0, i);
		ft_quicksort((&buffer[i + 1]), 0, (size - i - 1));
	}
}
