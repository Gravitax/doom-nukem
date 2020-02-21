/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/21 21:32:10 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     set_properplane(t_doom *data, int plane)
{
    if (plane == 0)
    {
        data->cdata.nplane = (t_vec3d){ 0, -1, 0, 1 };
        data->cdata.pplane = (t_vec3d){ 0, (float)W_HEIGHT - 1, 0, 1 };
    }
    else if (plane == 1)
    {
        data->cdata.nplane = (t_vec3d){ 0, 1, 0, 1 };
        data->cdata.pplane = (t_vec3d){ 0, 0, 0, 1 };
    }
    else if (plane == 2)
    {
        data->cdata.nplane = (t_vec3d){ -1, 0, 0, 1 };
        data->cdata.pplane = (t_vec3d){ (float)W_WIDTH - 1, 0, 0, 1 };
    }
    else if (plane == 3)
    {
        data->cdata.nplane = (t_vec3d){ 1, 0, 0, 1 };
        data->cdata.pplane = (t_vec3d){ 0, 0, 0, 1 };
    }
}

static void     tabpopfront(t_doom *data, t_triangle *buffer)
{
    int zindex;
    int i;

    zindex = 1;
    i = -1;
    while (++i < data->var.index)
        buffer[i] = buffer[zindex++];
    --data->var.index;
}

static void     clip_byplane(t_doom *data, t_triangle *buffer, int *ntriangles)
{
    int         i;
    int         trianglestoadd;

    trianglestoadd = 0;
	while (*ntriangles > 0)
	{
	    data->cdata.in = buffer[0];
        tabpopfront(data, buffer);
        *ntriangles -= 1;
        trianglestoadd = cliptriangle(data);
		i = -1;
        while (++i < trianglestoadd)
			buffer[data->var.index++] = data->cdata.out[i];
	}
    *ntriangles += trianglestoadd;
}

static void		triangletransform(t_doom *data, t_triangle *triangle)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
        if (data->var.texture)
        {
		    triangle->t[i].u /= triangle->v[i].w;
    		triangle->t[i].v /= triangle->v[i].w;
	    	triangle->t[i].w = 1 / triangle->v[i].w;
        }
        triangle->v[i] = vecdiv(triangle->v[i], triangle->v[i].w / 2);
        triangle->v[i].x *= -1;
        triangle->v[i].y *= -1;
        triangle->v[i] = vecadd(triangle->v[i], data->vector.offset);
		triangle->v[i].x *= data->var.xfactor;
		triangle->v[i].y *= data->var.yfactor;
	}
}

static void     projection(t_doom *data, t_triangle *buffer)
{
    while (data->var.index--)
	{
	    filltriangletext(data, buffer[data->var.index]);
	    drawtriangle(data, buffer[data->var.index], 0xffffffff);
	}
}

void            rasterisation(t_doom *data, t_triangle triangle)
{
    int         ntriangles;
    int         plane;
    t_triangle  buffer[13];

    data->var.index = 0;
    triangletransform(data, &triangle);
    buffer[data->var.index++] = triangle;
    ntriangles = 1;
    plane = -1;
	while (++plane < 4)
    {
        set_properplane(data, plane);
        clip_byplane(data, buffer, &ntriangles);
    }
    projection(data, buffer);
}
