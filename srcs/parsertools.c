/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/21 17:40:32 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void            skip_line(char *str, int *start)
{
    while (str[*start] && str[*start] != '\n')
        ++(*start);
    if (str[*start] == '\n')
        ++(*start);
}

void            parse_error(t_doom *data)
{
    if (data->str)
		ft_strdel(&data->str);
    if (data->var.texture == 1)
        if (data->pdata.texture)
            ft_memdel((void **)&data->pdata.texture);
	if (data->pdata.vertex)
		ft_memdel((void **)&data->pdata.vertex);
    clean_exit(data, "doom-nukem: parse error", 0);
}
