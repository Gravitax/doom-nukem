/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mtl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:29:57 by maboye            #+#    #+#             */
/*   Updated: 2020/02/25 20:08:18 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static int      parser_mtlgoodvalue(t_doom *data)
{
    // name i ka kd ks d tr ns illum map_ka kd ks map_name
    // else parser_error(data);
    // de newmtl into newmtl
    return (0);
}

void            parser_mtl(t_doom *data)
{
    (void)data;
    // lire tout les fichers object/*.mlt et les stocks dans un tableau mlt_ressources[nbmlt]
    // open dir => pdirent
    // pdirent => readdir
    // readdir => stock path
    // parse all path into data->pdata.mtl_ressources + stock mtlindex
}
