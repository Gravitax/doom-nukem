/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/04 22:12:22 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void			flatbot(t_cube *data, t_triangle triangle, int color)
{
    t_vec3d v0;
    t_vec3d v1;
    t_vec3d v2;
    int     x;
    int     y;

    v0 = triangle.v[0];
    v1 = triangle.v[1];
    v2 = triangle.v[2];
	data->fdata.m0 = (v1.x - v0.x) / (v1.y - v0.y);
    data->fdata.m1 = (v2.x - v0.x) / (v2.y - v0.y);
    data->fdata.ystart = (int)ceil(v0.y - 0.5f);
    data->fdata.yend = (int)ceil(v2.y - 0.5f);
	y = data->fdata.ystart - 1;
    while (++y < data->fdata.yend)
    {
        data->fdata.x0 = data->fdata.m0 * (y + 0.5f - v0.y) + v0.x;
        data->fdata.x1 = data->fdata.m1 * (y + 0.5f - v0.y) + v0.x;
        data->fdata.xstart = (int)(data->fdata.x0 - 0.5f);
        data->fdata.xend = (int)(data->fdata.x1 - 0.5f);
        x = data->fdata.xstart - 1;
        while (++x < data->fdata.xend)
            putpixel(data, x, y, color);
    }
}

static void			flattop(t_cube *data, t_triangle triangle, int color)
{
    t_vec3d v0;
    t_vec3d v1;
    t_vec3d v2;
    int	    x;
    int	    y;

    v0 = triangle.v[0];
    v1 = triangle.v[1];
    v2 = triangle.v[2];
    data->fdata.m0 = (v2.x - v0.x) / (v2.y - v0.y);
    data->fdata.m1 = (v2.x - v1.x) / (v2.y - v1.y);
    data->fdata.ystart = (int)ceil(v0.y - 0.5f);
    data->fdata.yend = (int)ceil(v2.y - 0.5f);
    y = data->fdata.ystart - 1;
    while (++y < data->fdata.yend)
    {
        data->fdata.x0 = data->fdata.m0 * (y + 0.5f - v0.y) + v0.x;
        data->fdata.x1 = data->fdata.m1 * (y + 0.5f - v1.y) + v1.x;
        data->fdata.xstart = (int)(data->fdata.x0 - 0.5f);
        data->fdata.xend = (int)(data->fdata.x1 - 0.5f);
		x = data->fdata.xstart - 1;
        while (++x < data->fdata.xend)
            putpixel(data, x, y, color);
    }
}

static void			general(t_cube *data, t_triangle triangle, int color)
{
    float	alpha;
    t_vec3d	v0;
    t_vec3d	v1;
    t_vec3d	v2;
    t_vec3d	vi;

    v0 = triangle.v[0];
    v1 = triangle.v[1];
    v2 = triangle.v[2];
    alpha = (v1.y - v0.y) / (v2.y - v0.y);
    vi.x = v0.x + (v2.x - v0.x) * alpha;
    vi.y = v0.y + (v2.y - v0.y) * alpha;
    vi.z = v0.z + (v2.z - v0.z) * alpha;
    if (v1.x < vi.x)
    {
        flatbot(data, (t_triangle){ v0, v1, vi }, color);
        flattop(data, (t_triangle){ v1, vi, v2 }, color);
    }
    else
    {
        flatbot(data, (t_triangle){ v0, vi, v1 }, color);
        flattop(data, (t_triangle){ vi, v1, v2 }, color);
    }
}

void				filltriangle(t_cube *data, t_triangle triangle, int color)
{
    t_vec3d	v0;
    t_vec3d	v1;
    t_vec3d	v2;

    v0 = triangle.v[0];
    v1 = triangle.v[1];
    v2 = triangle.v[2];
    v1.y < v0.y ? ft_swap((void *)&v0, (void *)&v1) : 0;
    v2.y < v1.y ? ft_swap((void *)&v1, (void *)&v2) : 0;
    v1.y < v0.y ? ft_swap((void *)&v0, (void *)&v1) : 0;
    if (v0.y == v1.y)
    {
        v1.x < v0.x ? ft_swap((void *)&v0, (void *)&v1) : 0;
        flattop(data, (t_triangle){ v0, v1, v2 }, color);
    }
    else if (v1.y == v2.y)
    {
        v2.x < v1.x ? ft_swap((void *)&v1, (void *)&v2) : 0;
        flatbot(data, (t_triangle){ v0, v1, v2 }, color);
    }
    else
    	general(data, (t_triangle){ v0, v1, v2 }, color);
}
