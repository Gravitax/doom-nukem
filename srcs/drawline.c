/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/12 15:51:04 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void		draw_horizontal(t_doom *data, t_vec3d p1, t_vec3d p2, int c)
{
	int			x;
	int			y;

	if (p1.x > p2.x)
		ft_swap((void *)&p1, (void *)&p2);
	while (p1.x + data->var.i <= p2.x)
	{
		x = p1.x + data->var.i;
		y = (int)(p1.y + data->var.i * data->var.coef);
		putpixel(data, x, y, c);
		++data->var.i;
	}
}

static void		draw_vertical(t_doom *data, t_vec3d p1, t_vec3d p2, int c)
{
	int			x;
	int			y;

	data->var.coef = 1 / data->var.coef;
	if (p1.y > p2.y)
		ft_swap((void *)&p1, (void *)&p2);
	while (p1.y + data->var.i <= p2.y)
	{
		x = (int)(p1.x + data->var.i * data->var.coef);
		y = p1.y + data->var.i;
		putpixel(data, x, y, c);
		++data->var.i;
	}
}

void			drawline(t_doom *data, t_vec3d p1, t_vec3d p2, int color)
{
	data->var.i = 0;
	if (p2.x == p1.x)
		data->var.coef = 1000000;
	else
		data->var.coef = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	if (data->var.coef > -1 && data->var.coef < 1)
		draw_horizontal(data, p1, p2, color);
	else
		draw_vertical(data, p1, p2, color);
}
