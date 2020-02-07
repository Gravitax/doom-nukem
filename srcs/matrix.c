/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/07 00:56:11 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void			pmatrix(t_cube *data)
{
	float	ratio;
	float	fovrad;

	ratio = (float)W_HEIGHT / (float)W_WIDTH;
	fovrad = 1 / tanf(((data->var.fov * 0.5f) / 180) * 3.14159f);
	data->matrix.proj.m[0][0] = ratio * fovrad;
	data->matrix.proj.m[1][1] = fovrad;
	data->matrix.proj.m[2][2] = data->var.far
		/ (data->var.far - data->var.near);
	data->matrix.proj.m[3][2] = (-data->var.far * data->var.near)
		/ (data->var.far - data->var.near);
	data->matrix.proj.m[2][3] = 1;
}

void			rotxmatrix(t_mat *matrix, float angle)
{
	matrix->m[0][0] = 1;
	matrix->m[1][1] = cosf(angle);
	matrix->m[1][2] = sinf(angle);
	matrix->m[2][1] = -sinf(angle);
	matrix->m[2][2] = cosf(angle);
	matrix->m[3][3] = 1;
}

void			rotymatrix(t_mat *matrix, float angle)
{
	matrix->m[0][0] = cosf(angle);
	matrix->m[0][2] = sinf(angle);
	matrix->m[1][1] = 1;
	matrix->m[2][0] = -sinf(angle);
	matrix->m[2][2] = cosf(angle);
	matrix->m[3][3] = 1;
}

void			rotzmatrix(t_mat *matrix, float angle)
{
	matrix->m[0][0] = cosf(angle);
	matrix->m[0][1] = sinf(angle);
	matrix->m[1][0] = -sinf(angle);
	matrix->m[1][1] = cosf(angle);
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;
}

void			transmatrix(t_mat *matrix, float x, float y, float z)
{
	matrix->m[0][0] = 1;
	matrix->m[1][1] = 1;
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;	
	matrix->m[3][0] = x;
	matrix->m[3][1] = y;
	matrix->m[3][2] = z;
	matrix->m[3][3] = 1;
}

void			identitymatrix(t_mat *matrix)
{
	matrix->m[0][0] = 1;
	matrix->m[1][1] = 1;
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;
}

void			pointatmatrix(t_mat *matrix,
					t_vec3d pos, t_vec3d target, t_vec3d up)
{
	t_vec3d	a;
	t_vec3d	forward;
	t_vec3d	right;

	forward = vecsub(target, pos);
	forward = vecnormalise(forward);
	a = vecmul(forward, vecdotproduct(up, forward));
	up = vecsub(up, a);
	right = veccrossproduct(up, forward);
	matrix->m[0][0] = right.x;
	matrix->m[0][1] = right.y;
	matrix->m[0][2] = right.z;
	matrix->m[1][0] = up.x;
	matrix->m[1][1] = up.y;
	matrix->m[1][2] = up.z;
	matrix->m[2][0] = forward.x;
	matrix->m[2][1] = forward.y;
	matrix->m[2][2] = forward.z;
	matrix->m[3][0] = pos.x;
	matrix->m[3][1] = pos.y;
	matrix->m[3][2] = pos.z;
	matrix->m[3][3] = 1;
}

void			quickinversematrix(t_mat *matrix, t_mat mpointat)
{
	matrix->m[0][0] = mpointat.m[0][0];
	matrix->m[0][1] = mpointat.m[1][0];
	matrix->m[0][2] = mpointat.m[2][0];
	matrix->m[1][0] = mpointat.m[0][1];
	matrix->m[1][1] = mpointat.m[1][1];
	matrix->m[1][2] = mpointat.m[2][1];
	matrix->m[2][0] = mpointat.m[0][2];
	matrix->m[2][1] = mpointat.m[1][2];
	matrix->m[2][2] = mpointat.m[2][2];
	matrix->m[3][0] = -(mpointat.m[3][0] * matrix->m[0][0]
		+ mpointat.m[3][1] * matrix->m[1][0]
		+ mpointat.m[3][2] * matrix->m[2][0]);
	matrix->m[3][1] = -(mpointat.m[3][0] * matrix->m[0][1]
		+ mpointat.m[3][1] * matrix->m[1][1]
		+ mpointat.m[3][2] * matrix->m[2][1]);
	matrix->m[3][2] = -(mpointat.m[3][0] * matrix->m[0][2]
		+ mpointat.m[3][1] * matrix->m[1][2]
		+ mpointat.m[3][2] * matrix->m[2][2]);
	matrix->m[3][3] = 1;
}

t_mat			mat_mulmatrix(t_mat m1, t_mat m2)
{
	int		i;
	int		j;
	t_mat	matrix;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			matrix.m[j][i] = m1.m[j][0] * m2.m[0][i]
				+ m1.m[j][1] * m2.m[1][i]
				+ m1.m[j][2] * m2.m[2][i]
				+ m1.m[j][3] * m2.m[3][i];
		}
	}
	return (matrix);
}

t_vec3d		mat_mulvector(t_mat m, t_vec3d i)
{
	t_vec3d	v;

	v.x = i.x * m.m[0][0]
		+ i.y * m.m[1][0]
		+ i.z * m.m[2][0]
		+ i.w * m.m[3][0];
	v.y = i.x * m.m[0][1]
		+ i.y * m.m[1][1]
		+ i.z * m.m[2][1]
		+ i.w * m.m[3][1];
	v.z = i.x * m.m[0][2]
		+ i.y * m.m[1][2]
		+ i.z * m.m[2][2]
		+ i.w * m.m[3][2];
	v.w = i.x * m.m[0][3]
		+ i.y * m.m[1][3]
		+ i.z * m.m[2][3]
		+ i.w * m.m[3][3];
	return (v);
}
