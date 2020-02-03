/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/03 18:07:48 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void		world_rotation(t_cube *data)
{
	if (data->event.key.keysym.sym == SDLK_t
	|| data->event.key.keysym.sym == SDLK_y)
	{
		data->xtheta += (data->event.key.keysym.sym == SDLK_t ? 0.1f : -0.1f);
		rotxmatrix(&data->matrix.rotx, data->xtheta);
	}
	else if (data->event.key.keysym.sym == SDLK_g
	|| data->event.key.keysym.sym == SDLK_h)
	{
		data->ytheta += (data->event.key.keysym.sym == SDLK_g ? 0.1f : -0.1f);
		rotymatrix(&data->matrix.roty, data->ytheta);
	}
	else if (data->event.key.keysym.sym == SDLK_b
	|| data->event.key.keysym.sym == SDLK_n)
	{
		data->ztheta += (data->event.key.keysym.sym == SDLK_b ? 0.1f : -0.1f);
		rotzmatrix(&data->matrix.rotz, data->ztheta * 0.5f);
	}
}

static void		camera_rotation(t_cube *data)
{
	if (data->event.key.keysym.sym == SDLK_q
	|| data->event.key.keysym.sym == SDLK_e)
	{
		data->yaw += (data->event.key.keysym.sym == SDLK_q ? 0.02f : -0.02f);
		rotymatrix(&data->matrix.camroty, data->yaw);
	}
	else if (data->event.key.keysym.sym == SDLK_r
	|| data->event.key.keysym.sym == SDLK_f)
	{
		data->xaw += (data->event.key.keysym.sym == SDLK_f ? 0.02f : -0.02f);
		rotxmatrix(&data->matrix.camrotx, data->xaw);
	}
}

static void		camera(t_cube *data)
{

	data->vector.forward = vecmul(data->vector.lookdir, 0.1f);
	if (data->event.key.keysym.sym == SDLK_UP)
		data->vector.camera = vecsub(data->vector.camera, vecmul(data->vector.up, 0.1f));
	else if (data->event.key.keysym.sym == SDLK_DOWN)
		data->vector.camera = vecadd(data->vector.camera, vecmul(data->vector.up, 0.1f));
	else if (data->event.key.keysym.sym == SDLK_a)
		data->vector.camera = vecsub(data->vector.camera, vecmul(data->vector.right, 0.1f));
	else if (data->event.key.keysym.sym == SDLK_d)
		data->vector.camera = vecadd(data->vector.camera, vecmul(data->vector.right, 0.1f));
	else if (data->event.key.keysym.sym == SDLK_w)
		data->vector.camera = vecadd(data->vector.camera, data->vector.forward);
	else if (data->event.key.keysym.sym == SDLK_s)
		data->vector.camera = vecsub(data->vector.camera, data->vector.forward);
}

void			events(t_cube *data)
{
	while (SDL_PollEvent(&data->event))
	{
		if ((data->event.key.keysym.sym == SDLK_ESCAPE
			&& data->event.type == SDL_KEYDOWN)
		|| data->event.type == SDL_QUIT)
			clean_exit(data, "cube3d: EXIT_SUCCES", 1);
		if (data->event.type == SDL_KEYDOWN)
		{
			if (data->event.key.keysym.sym == SDLK_u)
				data->zoom += 0.1f;
			else if (data->event.key.keysym.sym == SDLK_i)
				data->zoom -= data->zoom < 0.1f ? 0 : 0.1f;
			world_rotation(data);
			camera(data);
			camera_rotation(data);
		}
	}
}
