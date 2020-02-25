/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/25 17:32:42 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int             parser_goodchar(t_doom *data, char c)
{
    int i;

    i = -1;
    while (++i < PNB_CHAR)
    {
        if (data->pdata.c[i] == c)
            return (1);
    }
    return (0);
}

void            skip_line(char *str, int *start)
{
    while (str[*start] && str[*start] != '\n')
        ++(*start);
    if (str[*start] == '\n')
        ++(*start);
}

void            parser_error(t_doom *data)
{
    ft_strdel(&data->str);
    ft_memdel((void **)&data->pdata.texture);
	ft_memdel((void **)&data->pdata.vertex);
    clean_exit(data, "doom-nukem: parse error", 0);
}
