/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/25 17:38:05 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     get_size(t_doom *data, int *start)
{
    while (data->str && data->str[*start])
    {   
        if (data->str[*start] == '#' || data->str[*start] == 'o'
        || data->str[*start] == 's' || data->str[*start] == 'f'
        || data->str[*start] == 'm' || data->str[*start] == 'u')
            skip_line(data->str, start);
        else if (data->str[*start] == 'v')
        {
            if (data->str[*start + 1] == 't')
                ++data->pdata.vtcount;
            else
                ++data->pdata.vcount;
            skip_line(data->str, start);
        }
        else if (isspace(data->str[*start]))
            ++(*start);
        else if (parser_goodchar(data, data->str[*start]) == 0)
            parser_error(data);
    }
}

static void     init_ptrmallocsize(t_doom *data, int start, t_scene *scene)
{
    get_size(data, &start);
    if (data->pdata.vcount == 0)
        parser_error(data);
    if (!(data->pdata.vertex = (t_vec3d *)ft_memalloc(sizeof(t_vec3d)
            * data->pdata.vcount)))
        parser_error(data);
    if (data->pdata.vtcount == 0)
        return ;
    else
        data->var.texture = 1;
    if (!(data->pdata.texture = (t_vec2d *)ft_memalloc(sizeof(t_vec2d)
            * data->pdata.vtcount)))
        parser_error(data);
}

static void     assign_vertex(t_doom *data, float *v, int vnb)
{
    if (vnb == 2 && data->var.texture)
    {
        data->pdata.texture[data->pdata.vti++] = (t_vec2d){ v[0], v[1], 1 };
    }
    else if (vnb == 3)
        data->pdata.vertex[data->pdata.vi++] = (t_vec3d){ v[0], v[1], v[2], 1 };
}

static void     get_vertex(t_doom *data, int *start, int vnb)
{
    int     nb;
    float   v[3];

    nb = 0;
    ++(*start);
    while (data->str[*start] && data->str[*start] != '\n')
    {
        while (isblank(data->str[*start]))
            ++(*start);
        if (data->str[*start] == '-')
            ++(*start);
        if (ft_isdigit(data->str[*start]))
        {
           v[nb++] = atof(data->str + *start - 1);
           while (ft_isdigit(data->str[*start]) || data->str[*start] == '.')
                ++(*start);
        }
        else
            parser_error(data);
    }
    (nb == vnb) ? assign_vertex(data, v, vnb) : parser_error(data);
}

void            parser_handlevertex(t_doom *data, t_scene *scene, int *start)
{
    if (data->pdata.s == 1 || scene->object[data->pdata.io].name == NULL)
        parser_error(data);
    if (data->pdata.vcount == 0)
        init_ptrmallocsize(data, *start, scene);
    if (data->str[*start + 1] == 't')
    {
        scene->object[data->pdata.io].texture = 1;
        ++(*start);
        get_vertex(data, start, 2);
    }
    else
        get_vertex(data, start, 3);
    while (isblank(data->str[*start]))
        ++(*start);
}
