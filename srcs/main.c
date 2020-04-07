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
	data->var.xfactor = W_WIDTH / 2;
	data->var.yfactor = W_HEIGHT / 2;
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
	rotzmatrix(&data->matrix.rotz, data->var.ztheta);
	transmatrix(&data->matrix.trans, 0, 0, 2);
}

static void			put_block(t_doom *data, int index, int x, int z)
{
	static int	i = 0;

	data->tmp[0].object[i].mesh = (t_triangle *)ft_memalloc(sizeof(t_triangle) * 13);
	data->tmp[0].object[i].size = 13;
	data->tmp[0].object[i].texture = data->scene[index].object[0].texture;
	for (int j = 0; j < 13; j++)
	{
		data->tmp[0].object[i].mesh[j] = data->scene[index].object[0].mesh[j];
		for (int k = 0; k < 3; k++)
		{
			data->tmp[0].object[i].mesh[j].v[k].x += x;
			data->tmp[0].object[i].mesh[j].v[k].z += z;		
		}
	}
	++i;
}

static void			create_mesh(t_doom *data, int index, int size)
{
	if (!(data->tmp[0].object = (t_obj *)ft_memalloc(sizeof(t_obj) * size)))
		clean_exit(data, NULL, 0);
	for (int i = 0; i < size; i++)
		if (!(data->tmp[0].object[i].mesh = (t_triangle *)ft_memalloc(sizeof(t_triangle) * 13)))
        	clean_exit(data, NULL, 0);
}

static void			create_ground(t_doom *data, int index)
{
	const int	block_size = 1;
	const int	width = 4;
	const int	depth = 4;
	int			x = 0;
	int			z;

	create_mesh(data, index, width * depth);
	for (int i = 0; i < width; i++)
	{
		z = 0;
		for (int j = 0; j < depth; j++)
		{
			put_block(data, index, x, z);
			z += block_size;
		}
		x += block_size;
	}
	data->tmp[0].iobj = width * depth;
	free_scene(&data->scene[index]);
	data->scene[index] = data->tmp[0];
}

static void		init_data(t_doom *data)
{
	int		i;

	i = -1;
	parser_mtl(data);
	while (++i < data->var.ac - 1)
	{
		data->scene[i].i = i;
		get_object(data, &data->scene[i], data->tab[i]);
		if (ft_strcmp(data->tab[i], "cube") == 0)
			create_ground(data, i);
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
