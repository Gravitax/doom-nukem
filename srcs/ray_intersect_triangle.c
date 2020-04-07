/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_triangle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/25 18:37:35 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int         ray_intersect_triangle(t_vec3d ray_origin, t_vec3d ray_vector,
                t_triangle triangle, t_vec3d *intersection_point)
{
    const float     epsilon = 0.0000001f;
    t_vec3d         edge1, edge2, h, s, q;
    float           a, f, u, v;

    edge1 = vecsub(triangle.v[1], triangle.v[0]);
    edge2 = vecsub(triangle.v[2], triangle.v[0]);
    h = veccrossproduct(ray_vector, edge2);
    a = vecdotproduct(edge1, h);
    if (a > -epsilon && a < epsilon)
        return (0);
    f = 1 / a;
    s = vecsub(ray_origin, triangle.v[0]);
    u = f * vecdotproduct(s, h);
    if (u < 0 || u > 1)
        return (0);
    q = veccrossproduct(s, edge1);
    v = f * vecdotproduct(ray_vector, q);
    if (v < 0 || u + v > 1)
        return (0);
    float   t = f * vecdotproduct(edge2, q);
    if (t > epsilon)
    {
        //outIntersectionPoint = rayOrigin + rayVector * t;
        *intersection_point = vecmul(ray_vector, t);
        *intersection_point = vecadd(*intersection_point, ray_origin);
        return (1);
    }
    else
        return (0);
}
