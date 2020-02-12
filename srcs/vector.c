/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/12 15:51:04 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"


t_vec3d			vecadd(t_vec3d v1, t_vec3d v2)
{
	return ((t_vec3d){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3d			vecsub(t_vec3d v1, t_vec3d v2)
{
	return ((t_vec3d){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z });
}

float			vecdotproduct(t_vec3d v1, t_vec3d v2)
{

	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float			veclen(t_vec3d v)
{
    return (1 / rsqrt(vecdotproduct(v, v)));
}

t_vec3d			vecnormalise(t_vec3d v)
{
    float		l;

    l = veclen(v);
	return ((t_vec3d){ v.x / l, v.y / l, v.z / l });
}

t_vec3d			veccrossproduct(t_vec3d v1, t_vec3d v2)
{
    t_vec3d    vec;

    vec.x = v1.y * v2.z - v1.z * v2.y;
    vec.y = v1.z * v2.x - v1.x * v2.z;
    vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

t_vec3d			vecmul(t_vec3d v, float k)
{
	return ((t_vec3d){ v.x * k, v.y * k, v.z * k });
}

t_vec3d			vecdiv(t_vec3d v, float k)
{
    return ((t_vec3d){ v.x / k, v.y / k, v.z / k });
}

t_vec3d			vecintersectplane(t_doom *data, t_vec3d startl, t_vec3d endl)
{
	float		ad;
	float		bd;
	float		dplane;
	t_vec3d		intersectline;

	data->cdata.nplane = vecnormalise(data->cdata.nplane);
	ad = vecdotproduct(startl, data->cdata.nplane);
	bd = vecdotproduct(endl, data->cdata.nplane);
	dplane = vecdotproduct(data->cdata.nplane, data->cdata.pplane);
	data->var.t = (dplane - ad) / (bd - ad);
	intersectline = vecmul(vecsub(endl, startl), data->var.t);
	return (vecadd(startl, intersectline));
}
