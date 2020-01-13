/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/01/10 18:40:12 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void     set_properplane(t_cube *data, int plane)
{
    if (plane == 0)
    {
        data->cdata.nplane = (t_vec3d){ 0, -1, 0 , 1 };
        data->cdata.pplane = (t_vec3d){ 0, (float)W_HEIGHT, 0 , 1 };
    }
    else if (plane == 1)
    {
        data->cdata.nplane = (t_vec3d){ 0, (float)W_HEIGHT, 0 , 1 };
        data->cdata.pplane = (t_vec3d){ 0, -1, 0 , 1 };
    }
    else if (plane == 2)
    {
        data->cdata.nplane = (t_vec3d){ -1, 0, 0 , 1 };
        data->cdata.pplane = (t_vec3d){ (float)W_WIDTH, 0, 0 , 1 };
    }
    else if (plane == 3)
    {
        data->cdata.nplane = (t_vec3d){ (float)W_WIDTH, 0, 0 , 1 };
        data->cdata.pplane = (t_vec3d){ -1, 0, 0 , 1 };
    }
}

static void     tabpopfront(t_cube *data, t_triangle *buffer)
{
    int zindex;
    int i;

    zindex = 1;
    i = -1;
    while (++i < data->index)
        buffer[i] = buffer[zindex++];
    --data->index;
}

static void     clip_byplane(t_cube *data, t_triangle *buffer, int *ntriangles)
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
			buffer[data->index++] = data->cdata.out[i];
	}
    *ntriangles += trianglestoadd;
}

static void     rasterisation(t_cube *data, t_triangle *buffer)
{
    while (data->index--)
	{
	    filltriangletext(data,
	    	buffer[data->index],
	    	buffer[data->index].color);
	    drawtriangle(data, buffer[data->index], 0xffffffff);
	}
}

void            clipping(t_cube *data, t_triangle *triangle)
{
    int         ntriangles;
    int         plane;
    t_triangle  buffer[10];

    data->index = 0;
    buffer[data->index++] = *triangle;
    ntriangles = 1;
    plane = -1;
	while (++plane < 4)
    {
        set_properplane(data, plane);
        clip_byplane(data, buffer, &ntriangles);
    }
    rasterisation(data, buffer);
}
