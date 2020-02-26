/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mtl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:29:57 by maboye            #+#    #+#             */
/*   Updated: 2020/02/26 18:21:52 by maboye           ###   ########.fr       */
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
    struct dirent   *pdirent;
    DIR             *p_dir;

	p_dir = opendir("/Users/maboye/sgoinfre/doom-nukem/object");
	if (p_dir)
	{
		while ((pdirent = readdir(p_dir)) != NULL)
        {
            //stock les path du current dir finissant par .mtl
            //parse tout les fichiers mtl trouvés
        }
		closedir(p_dir);
	}
}
