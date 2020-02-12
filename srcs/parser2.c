/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/12 16:40:42 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     get_size(t_doom *data, int *start)
{
    while (data->str && data->str[*start])
    {
        printf("c: [%c]\n", data->str[*start]);    
        if (data->str[*start] == '#' || data->str[*start] == 'o'
        || data->str[*start] == 's' || data->str[*start] == 'f')
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
        else
            parse_error(data);
    }
}

static void     init_ptrmallocsize(t_doom *data, int start)
{
    get_size(data, &start);
    if (!(data->pdata.vertex = (t_vec3d *)ft_memalloc(sizeof(t_vec3d)
    * data->pdata.vcount + 1)))
        parse_error(data);
    if (data->pdata.vtcount == 0)
        return ;
    else
        data->var.texture = 1;
    if (!(data->pdata.texture = (t_vec2d *)ft_memalloc(sizeof(t_vec2d)
    * data->pdata.vtcount + 1)))
        parse_error(data);
}

static void     stock_vertex(t_doom *data, float *v, int vnb)
{
    if (vnb == 2)
        data->pdata.texture[data->pdata.vti++] = (t_vec2d){ v[0], v[1], 1 };
    else if (vnb == 3)
        data->pdata.vertex[data->pdata.vi++] = (t_vec3d){ v[0], v[1], v[2], 1 };
}

static void     get_vertex(t_doom *data, int *start, int vnb)
{
    int     nb;
    float   v[3];

    nb = 0;
    while (nb < vnb && data->str[*start] && data->str[*start] != '\n')
    {
        while (isblank(data->str[++(*start)]))
            ;
        if (data->str[*start] == '-')
            ++(*start);
        if (ft_isdigit(data->str[*start]))
        {
           v[nb++] = atof(data->str + *start - 1); 
           while (ft_isdigit(data->str[*start]) || data->str[*start] == '.')
                ++(*start);
        }
        else
            parse_error(data);
    }
    (nb == vnb - 1) ? stock_vertex(data, v, vnb) : parse_error(data);
}

void            handle_vertex(t_doom *data, t_scene *scene, int *start)
{
    if (data->pdata.s == 1)
        parse_error(data);
    puts("1");
    if (data->pdata.vcount == 0)
        init_ptrmallocsize(data, *start);
    puts("2");
    if (data->str[*start + 1] == 't')
    {
        ++(*start);
        get_vertex(data, start, 2);
    }
    else
        get_vertex(data, start, 3);
    while (isblank(data->str[++(*start)]))
        ;
}
