/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mtlassign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:54:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/25 19:06:15 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static char     *mtl_ressourcesname(t_doom *data, int *i)
{
    int     end;

    while (isblank(data->str[++(*i)]))
        ;
    end = *i;
    skip_line(data->str, &end);
    end = data->str[end - 1] == '\n' ? end - 1 : end;
    *i = end;
    return (ft_strsub(data->str, *i, end - *i));
}

static  void    mtl_assignressources(t_doom *data, t_scene *scene, char *name)
{
    int     index;
    int     error;

    index = -1;
    error = 1;
    while (++index < data->pdata.mtl_max)
    {
        if (ft_strcmp(name, data->pdata.mtl_ressources[index].name) == 0)
        {
            error = 0;
            break ;
        }
    }
    if (error == 1)
        parser_error(data);
    if (data->pdata.ti + 1 < scene->object[data->pdata.io].size)
        scene->object[data->pdata.io].mesh[data->pdata.ti + 1].ressources = data->pdata.mtl_ressources[index];
}

void            parser_mtlassign(t_doom *data, t_scene *scene, int *i)
{
    char    *ressource_name;

    if (ft_strncmp(data->str + *i, "usemtl", 5) == 0)
    {
        if (!(ressource_name = mtl_ressourcesname(data, i)))
            parser_error(data);
        mtl_assignressources(data, scene, ressource_name);
    }
    else
        parser_error(data);
}
