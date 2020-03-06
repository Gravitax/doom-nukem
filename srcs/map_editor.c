/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:12:32 by maboye            #+#    #+#             */
/*   Updated: 2020/02/26 18:15:48 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void		transform_meshadd(t_obj *object, float x, float y, float z)
{
	int		i;
	t_mat	transmat;

	transmatrix(&transmat, x, y, z / 2);
	i = -1;
	while (++i < object->size)
	{
		for (int v = 0; v < 3; v++)
		{
			object->mesh[i].v[v].x += x;
			object->mesh[i].v[v].y += y;
			object->mesh[i].v[v].z += z;
		}
		//object->mesh[i] = mmvtriangle(transmat, object->mesh[i]);
	}
}	

static void		transform_meshmul(t_obj *object, float x, float y, float z)
{
	int	i;

	i = -1;
	while (++i < object->size)
		for (int v = 0; v < 3; v++)
		{
			object->mesh[i].v[v].x *= x;
			object->mesh[i].v[v].y *= y;
			object->mesh[i].v[v].z *= z;
		}
}

t_mat			new_rotzmatrix(float angle)
{
	t_mat	new_matrix;

	new_matrix.m[0][0] = cosf(angle);
	new_matrix.m[0][1] = sinf(angle);
	new_matrix.m[1][0] = -sinf(angle);
	new_matrix.m[1][1] = cosf(angle);
	new_matrix.m[2][2] = 1;
	new_matrix.m[3][3] = 1;
	return (new_matrix);
}

void			new_mat_mulmatrix(t_mat *m1, t_mat *m2)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			m1->m[j][i] = m1->m[j][0] * m2->m[0][i]
				+ m1->m[j][1] * m2->m[1][i]
				+ m1->m[j][2] * m2->m[2][i]
				+ m1->m[j][3] * m2->m[3][i];
		}
	}
}

static void		transform_meshrot(t_obj *object, float x, float y, float z)
{
	t_mat	rotmat;
	t_mat	tmp;

	//rotmat = new_rotzmatrix(z);
	rotzmatrix(&rotmat, z);
	rotymatrix(&tmp, y);
	rotmat = mat_mulmatrix(rotmat, tmp);
	rotxmatrix(&tmp, x);
	rotmat = mat_mulmatrix(rotmat, tmp);
	int i = -1;
	while (++i < object->size)
		object->mesh[i] = mmvtriangle(rotmat, object->mesh[i]);
}

static void		transform_mesh(t_obj *object, t_mat matrix)
{
	int i;

	i = -1;
	while (++i < object->size)
		object->mesh[i] = mmvtriangle(matrix, object->mesh[i]);
}

static void		x_event(t_doom *data, t_obj *object, float dist)
{
	t_mat	matrix;

	puts("X");
	if (data->editor.key[S] == 1)
		transform_meshmul(object, dist, 1, 1);
	else if (data->editor.key[R] == 1)
	{
		rotxmatrix(&matrix, dist - 1);
		transform_mesh(object, matrix);
	}
	else
		transform_meshadd(object, dist - 1, 0, 0);
}

static void		y_event(t_doom *data, t_obj *object, float dist)
{
	t_mat	matrix;

	puts("Y");
	if (data->editor.key[S] == 1)
		transform_meshmul(object, 1, dist, 1);
	else if (data->editor.key[R] == 1)
	{
		rotymatrix(&matrix, dist - 1);
		transform_mesh(object, matrix);
	}
	else
		transform_meshadd(object, 0, dist - 1, 0);
}

static void		z_event(t_doom *data, t_obj *object, float dist)
{
	t_mat	matrix;

	puts("Zzzz");
	if (data->editor.key[S] == 1)
		transform_meshmul(object, 1, 1, dist);
	else if (data->editor.key[R] == 1)
	{
		rotzmatrix(&matrix, dist - 1);
		//transform_mesh(object, matrix);
		transform_mesh(object, new_rotzmatrix(dist - 1));
	}
	else
		transform_meshadd(object, 0, 0, dist - 1);
}

static void		object_event(t_doom *data, t_obj *object)
{
	float		dist;

	if (data->editor.key[DOWN])
		dist = 0.9f;
	else if (data->editor.key[UP])
		dist = 1.1f;
	else
		dist = 0;
	if (dist)
	{
		if (data->editor.key[X])
			x_event(data, object, dist);
		else if (data->editor.key[Y])
			y_event(data, object, dist);
		else if (data->editor.key[Z])
			z_event(data, object, dist);
	}
}

static void		detect_key(t_doom *data)
{
	if (data->event.key.keysym.sym == SDLK_DOWN)
		data->editor.key[DOWN] = data->event.type == SDL_KEYUP ? 0 : 1;
	if (data->event.key.keysym.sym == SDLK_UP)
		data->editor.key[UP] = data->event.type == SDL_KEYUP ? 0 : 1;
	if (data->event.key.keysym.sym == SDLK_x)
		data->editor.key[X] = data->event.type == SDL_KEYUP ? 0 : 1;
	if (data->event.key.keysym.sym == SDLK_y)
		data->editor.key[Y] = data->event.type == SDL_KEYUP ? 0 : 1;
	if (data->event.key.keysym.sym == SDLK_z)
		data->editor.key[Z] = data->event.type == SDL_KEYUP ? 0 : 1;
	if (data->event.key.keysym.sym == SDLK_s)
		if (data->event.type == SDL_KEYDOWN)
		{
			if (data->editor.key[S] == 1)
				data->editor.key[S] = 0;
			else
				data->editor.key[S] = 1;
		}
	if (data->event.key.keysym.sym == SDLK_r)
		if (data->event.type == SDL_KEYDOWN)
		{
			if (data->editor.key[R] == 1)
				data->editor.key[R] = 0;
			else
				data->editor.key[R] = 1;
		}
}

static int      events_map_editor(t_doom *data)
{
	int	i = data->var.is;
	int	j = data->var.io;

	while (SDL_PollEvent(&data->event))
	{
    	if ((data->event.key.keysym.sym == SDLK_ESCAPE
		&& data->event.type == SDL_KEYDOWN)
		|| data->event.type == SDL_QUIT)
		    clean_exit(data, "map_editor: EXIT_SUCCES", 1);
		if (data->event.type == SDL_KEYDOWN
		&& data->event.key.keysym.sym == SDLK_p)
			return (0);
		detect_key(data);
		object_event(data, &data->scene[i].object[j]);
	}
    return (1);
}

void		    map_editor(t_doom *data)
{
	if (data->event.key.keysym.sym == SDLK_p)
	{
		ft_memset(data->editor.key, 0, sizeof(int) * KEY_MAX);
		while (1)
		{
            if (events_map_editor(data) == 0)
                return ;
			display(data);
		}
	}
}
