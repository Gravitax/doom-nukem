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
	int	i;

	i = -1;
	while (++i < object->size)
		for (int v = 0; v < 3; v++)
		{
			object->mesh[i].v[v].x += x;
			object->mesh[i].v[v].y += y;
			object->mesh[i].v[v].z += z;
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

static void		transform_meshrot(t_obj *object, float x, float y, float z)
{
	t_mat	rotmat;

	rotxmatrix(&rotmat, );	
}

static void		object_event(t_doom *data, t_obj *object)
{
	float		x;
	float		y;
	float		z;
	float		dist;

	dist = 0;
	x = 1;
	y = 1;
	z = 1;
	if (data->editor.key[DOWN])
		dist = -0.1f;
	else if (data->editor.key[UP])
		dist = 0.1f;
	if (data->editor.key[X])
		x += dist;
	else if (data->editor.key[Y])
		y += dist;
	else if (data->editor.key[Z])
		z += dist;
	if (data->editor.key[S] == 1)
		transform_meshmul(object, x, y, z);
	else if (data->editor.key[R] == 1)
		transform_meshrot(object, x, y, z);
	else
		transform_meshadd(object, x - 1, y - 1, z - 1);
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
		while (1)
		{
            if (events_map_editor(data) == 0)
			{
				ft_memset(data->editor.key, 0, sizeof(int) * KNB);
                return ;
			}
			display_mesh(data);
			display_renderer(data);
		}
	}
}
