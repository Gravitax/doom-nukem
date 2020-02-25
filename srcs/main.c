/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/25 18:37:35 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void		init_sdl(t_doom *data)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		clean_exit(data, "cube3d: SDL_Init fail", 0);
	data->pwindow = SDL_CreateWindow("maboye cube3d",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W_WIDTH, W_HEIGHT, 0);
}

static int		get_fps(t_doom *data)
{
	int	pframe;

	pframe = 1000 / FPS;
	data->var.fps = 1000 / (data->var.frame_start - data->var.etime);
	if (data->var.frame_start - data->var.etime >= pframe)
	{
		data->var.etime = data->var.frame_start;
		return (1);
	}
	SDL_Delay(pframe - (data->var.frame_start - data->var.etime));
	return (0);
}

static void		init_matrix(t_doom *data)
{
	data->var.xfactor = 0.5f * (float)W_WIDTH;
	data->var.yfactor = 0.5f * (float)W_HEIGHT;
	data->var.xtheta = 1;
	data->var.ytheta = 1;
	data->var.ztheta = 1;
	data->var.near = 0.1f;
	data->var.far = 1000;
	data->var.fov = 90;
	data->vector.camera = (t_vec3d){ 0, 0, 0, 1 };
	data->vector.lightdir = (t_vec3d){ 0, 0, -1, 1 };
	data->vector.offset = (t_vec3d){ 1, 1, 0, 1 };
	rotxmatrix(&data->matrix.camrotx, data->var.xaw);
	rotymatrix(&data->matrix.camroty, data->var.yaw);
	pmatrix(data);
	rotxmatrix(&data->matrix.rotx, data->var.xtheta);
	rotymatrix(&data->matrix.roty, data->var.ytheta);
	rotzmatrix(&data->matrix.rotz, data->var.ztheta * 0.5f);
	transmatrix(&data->matrix.trans, 0, 0, 2);
}

static void		init_data(t_doom *data)
{
	int		i;

	i = -1;
	parser_mtl(data);
	while (++i  < data->var.ac - 1)
	{
		get_object(data, &data->scene[i], data->tab[i]);
		if (!(data->scene[i].texture = SDL_LoadBMP("img/doom.bmp")))
			clean_exit(data, "cube3d: loading sprite doom error", 0);
	}
	init_matrix(data);
}

static void		launcher(t_doom *data)
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
			data->var.frame_start = SDL_GetTicks();
			if (get_fps(data) == 1)
			{
				events(data);
				display(data);
				printf("fps: %d\n", data->var.fps);
			}
		}
	}
	else
		clean_exit(data, "cube3d: SDL_CreateWindow fail", 0);
}

int				main(int ac, char **av)
{
	t_doom	data;

	if (ac > 1)
	{
		ft_memset(&data, 0, sizeof(t_doom));
		if (!(data.tab = (char **)ft_memalloc(sizeof(char *) * ac)))
			clean_exit(NULL, "cube3d: malloc error", 0);
		while (++data.var.ac < ac)
		{
			if (!(data.tab[data.var.ac - 1] = ft_strdup(av[data.var.ac])))
				clean_exit(&data, "cube3d: malloc error", 0);
		}
		launcher(&data);
	}
	else
		clean_exit(NULL, "cube3d: usage: ./cube3d [valid.obj]", 0);
	return (EXIT_SUCCESS);
}
