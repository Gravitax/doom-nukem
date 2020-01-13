/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/04 21:14:56 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void		draw_horizontal(t_cube *data, t_vec3d p1, t_vec3d p2, int c)
{
	int			x;
	int			y;

	if (p1.x > p2.x)
		ft_swap((void *)&p1, (void *)&p2);
	while (p1.x + data->i <= p2.x)
	{
		x = p1.x + data->i;
		y = (int)(p1.y + data->i * data->coef);
		putpixel(data, x, y, c);
		++data->i;
	}
}

static void		draw_vertical(t_cube *data, t_vec3d p1, t_vec3d p2, int c)
{
	int			x;
	int			y;

	data->coef = 1 / data->coef;
	if (p1.y > p2.y)
		ft_swap((void *)&p1, (void *)&p2);
	while (p1.y + data->i <= p2.y)
	{
		x = (int)(p1.x + data->i * data->coef);
		y = p1.y + data->i;
		putpixel(data, x, y, c);
		++data->i;
	}
}

void			drawline(t_cube *data, t_vec3d p1, t_vec3d p2, int color)
{
	data->i = 0;
	if (p2.x == p1.x)
		data->coef = 1000000;
	else
		data->coef = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	if (data->coef > -1 && data->coef < 1)
		draw_horizontal(data, p1, p2, color);
	else
		draw_vertical(data, p1, p2, color);
}
