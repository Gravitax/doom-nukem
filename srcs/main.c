/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/19 16:39:33 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void		init_sdl(t_cube *data)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		clean_exit(data, "cube3d: SDL_Init fail", 0);
	data->pwindow = SDL_CreateWindow("maboye cube3d",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W_WIDTH, W_HEIGHT, 0);
}

static int		get_fps(t_cube *data)
{
	int	pframe;

	pframe = 1000 / FPS;
	data->fps = 1000 / (data->frame_start - data->etime);
	if (data->frame_start - data->etime >= pframe)
	{
		data->etime = data->frame_start;
		return (1);
	}
	SDL_Delay(pframe - (data->frame_start - data->etime));
	return (0);
}

static void		init_matrix(t_cube *data)
{
	data->xfactor = 0.5f * (float)W_WIDTH;
	data->yfactor = 0.5f * (float)W_HEIGHT;
	data->xtheta = 1;
	data->ytheta = 1;
	data->ztheta = 1;
	data->zoom = 2;
	data->near = 0.1f;
	data->far = 1000;
	data->fov = 90;
	data->vector.camera = (t_vec3d){ 0, 0, 0, 1 };
	data->vector.lightdir = (t_vec3d){ 0, 0, -1, 1 };
	data->vector.offset = (t_vec3d){ 1, 1, 0, 1 };
	rotxmatrix(&data->matrix.camrotx, data->xaw);
	rotymatrix(&data->matrix.camroty, data->yaw);
	pmatrix(data);
	rotxmatrix(&data->matrix.rotx, data->xtheta);
	rotymatrix(&data->matrix.roty, data->ytheta);
	rotzmatrix(&data->matrix.rotz, data->ztheta * 0.5f);
	transmatrix(&data->matrix.trans, 0, 0, data->zoom);
}

static void		cube(t_cube *data, int i)
{
	data->mesh[i].object = (t_triangle *)ft_memalloc(sizeof(t_triangle) * 12);
	data->mesh[i].object[0] = (t_triangle){(t_vec3d){ 0, 0, 0, 1 },
		(t_vec3d){ 0, 1, 0, 1 }, (t_vec3d){ 1, 1, 0, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 0, 0, 1 }, (t_vec2d){ 1, 0, 1 }};
	data->mesh[i].object[1] = (t_triangle){(t_vec3d){ 0, 0, 0, 1 },
		(t_vec3d){ 1, 1, 0, 1 }, (t_vec3d){ 1, 0, 0, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 1, 0, 1 }, (t_vec2d){ 1, 1, 1 }};
	data->mesh[i].object[2] = (t_triangle){(t_vec3d){ 1, 0, 0, 1 },
		(t_vec3d){ 1, 1, 0, 1 }, (t_vec3d){ 1, 1, 1, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 0, 0, 1 }, (t_vec2d){ 1, 0, 1 }};
	data->mesh[i].object[3] = (t_triangle){(t_vec3d){ 1, 0, 0, 1 },
		(t_vec3d){ 1, 1, 1, 1 }, (t_vec3d){ 1, 0, 1, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 1, 0, 1 }, (t_vec2d){ 1, 1, 1 }};
	data->mesh[i].object[4] = (t_triangle){(t_vec3d){ 1, 0, 1, 1 },
		(t_vec3d){ 1, 1, 1, 1 }, (t_vec3d){ 0, 1, 1, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 0, 0, 1 }, (t_vec2d){ 1, 0, 1 }};
	data->mesh[i].object[5] = (t_triangle){(t_vec3d){ 1, 0, 1, 1 },
		(t_vec3d){ 0, 1, 1, 1 }, (t_vec3d){ 0, 0, 1, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 1, 0, 1 }, (t_vec2d){ 1, 1, 1 }};
	data->mesh[i].object[6] = (t_triangle){(t_vec3d){ 0, 0, 1, 1 },
		(t_vec3d){ 0, 1, 1, 1 }, (t_vec3d){ 0, 1, 0, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 0, 0, 1 }, (t_vec2d){ 1, 0, 1 }};
	data->mesh[i].object[7] = (t_triangle){(t_vec3d){ 0, 0, 1, 1 },
		(t_vec3d){ 0, 1, 0, 1 }, (t_vec3d){ 0, 0, 0, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 1, 0, 1 }, (t_vec2d){ 1, 1, 1 }};
	data->mesh[i].object[8] = (t_triangle){(t_vec3d){ 0, 1, 0, 1 },
		(t_vec3d){ 0, 1, 1, 1 }, (t_vec3d){ 1, 1, 1, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 0, 0, 1 }, (t_vec2d){ 1, 0, 1 }};
	data->mesh[i].object[9] = (t_triangle){(t_vec3d){ 0, 1, 0, 1 },
		(t_vec3d){ 1, 1, 1, 1 }, (t_vec3d){ 1, 1, 0, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 1, 0, 1 }, (t_vec2d){ 1, 1, 1 }};
	data->mesh[i].object[10] = (t_triangle){(t_vec3d){ 1, 0, 1, 1 },
		(t_vec3d){ 0, 0, 1, 1 }, (t_vec3d){ 0, 0, 0, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 0, 0, 1 }, (t_vec2d){ 1, 0, 1 }};
	data->mesh[i].object[11] = (t_triangle){(t_vec3d){ 1, 0, 1, 1 },
		(t_vec3d){ 0, 0, 0, 1 }, (t_vec3d){ 1, 0, 0, 1 },
		(t_vec2d){ 0, 1, 1 }, (t_vec2d){ 1, 0, 1 }, (t_vec2d){ 1, 1, 1 }};
}

static void		init_data(t_cube *data)
{
	int		i;

	i = -1;
	while (++i  < data->ac - 1)
	{
		if (ft_strcmp(data->tab[i], "cube") == 0)
		{
			cube(data, i);
			data->mesh[i].size = 11;
			if (!(data->mesh[i].texture = SDL_LoadBMP("img/doom.bmp")))
				clean_exit(data, "cube3d: loading sprite doom error", 0);
		}
		else
		{
			get_object(data, &data->mesh[i], data->tab[i]);
			if (data->mesh[i].size == 0 || data->mesh[i].object == NULL)
				clean_exit(data, "cube3d: load object error", 0);
		}
	}
	init_matrix(data);
}

static void		launcher(t_cube *data)
{
	init_sdl(data);
	if (data->pwindow)
	{
		if (!(data->renderer = SDL_CreateRenderer(data->pwindow, -1, 0)))
			clean_exit(data, "cube3d: SDL_CreateRenderer fail", 0);
		if (!(data->screen = new_surface(W_WIDTH, W_HEIGHT)))
			clean_exit(data, "cube3d: error creating RGB surface", 0);
		init_data(data);
		while (1)
		{
			data->frame_start = SDL_GetTicks();
			if (get_fps(data) == 1)
			{
				events(data);
				display(data);
				printf("fps: %d\n", data->fps);
			}
		}
	}
	else
		clean_exit(data, "cube3d: SDL_CreateWindow fail", 0);
}

int				main(int ac, char **av)
{
	t_cube	data;

	if (ac > 1)
	{
		ft_memset(&data, 0, sizeof(t_cube));
		if (!(data.tab = (char **)ft_memalloc(sizeof(char *) * ac)))
			clean_exit(NULL, "cube3d: malloc error", 0);
		while (++data.ac < ac)
		{
			if (!(data.tab[data.ac - 1] = ft_strdup(av[data.ac])))
				clean_exit(&data, "cube3d: malloc error", 0);
		}
		launcher(&data);
	}
	else
		clean_exit(NULL, "cube3d: usage: ./cube3d [valid.obj]", 0);
	return (EXIT_SUCCESS);
}


