/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/07 06:01:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>

# include <SDL.h>

# include "../libft/libft.h"

# define W_WIDTH	1280
# define W_HEIGHT	720
# define W_LEN		W_WIDTH * W_HEIGHT

# define FPS		120

typedef union	u_rsqrt
{
	float		f;
	uint32_t	i;
}				t_rsqrt;

typedef struct	s_vec2d
{
	float		u;
	float		v;
	float		w;
}				t_vec2d;

typedef struct	s_vec3d
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec3d;

typedef struct	s_vectorlist
{
	t_vec3d		camera;
	t_vec3d		forward;
	t_vec3d		lightdir;
	t_vec3d		lookdir;
	t_vec3d		offset;
	t_vec3d		right;
	t_vec3d		target;
	t_vec3d		up;
}				t_vector;

typedef struct	s_triangle
{
	t_vec3d		v[3];
	t_vec2d		t[3];
	int			color;
}				t_triangle;

typedef struct	s_mesh
{
	t_triangle	*object;
	SDL_Surface	*texture;
	int			size;
}				t_mesh;

typedef struct	s_matrix
{
	float		m[4][4];
}				t_mat;

typedef struct	s_matrixlist
{
	t_mat		camrotx;
	t_mat		camroty;
	t_mat		pointat;
	t_mat		proj;
	t_mat		rotx;
	t_mat		roty;
	t_mat		rotz;
	t_mat		trans;
	t_mat		view;
	t_mat		world;
}				t_matrix;

typedef struct	s_filltriangle
{
	float		ax;
	float		bx;
	int			dx1;
	int			dy1;
	int			dx2;
	int			dy2;
	float		daxstep;
	float		dbxstep;
	float		du1;
	float		du1step;
	float		dv1;
	float		dv1step;
	float		dw1;
	float		dw1step;
	float		du2;
	float		du2step;
	float		dv2;
	float		dv2step;
	float		dw2;
	float		dw2step;
	float		texu;
	float		texv;
	float		texw;
	float		texsu;
	float		texsv;
	float		texsw;
	float		texeu;
	float		texev;
	float		texew;
}				t_fdata;

typedef struct	s_clipptriangle
{
	int			inside;
	int			outside;
	t_vec3d		nplane;
	t_vec3d		pplane;
	t_vec3d		ipoints[3];
	t_vec3d		opoints[3];
	t_vec2d		itex[3];
	t_vec2d		otex[3];
	t_triangle	in;
	t_triangle	out[2];
}				t_cdata;

typedef struct	s_variables
{
	int				ac;
	int				i;
	int				index;
	int				fps;
	double			coef;
	float			etime;
	float			frame_start;
	float			far;
	float			fov;
	float			near;
	float			t;
	float			xfactor;
	float			yfactor;
	float			xtheta;
	float			ytheta;
	float			ztheta;
	float			xaw;
	float			yaw;
}				t_var;

typedef struct	s_parser
{
	int				t;
	int				tx;
	int				v;
	t_vec2d			*texture;
	t_vec3d			*vertex;
}				t_pdata;

typedef struct	s_mainenv
{
	float			dbuffer[W_LEN + 1];
	char			*str;
	char			**tab;
	t_cdata			cdata;
	t_fdata			fdata;
	t_matrix		matrix;
	t_pdata			pdata;
	t_var			var;
	t_vector		vector;
	t_mesh			mesh[20];
	SDL_Event		event;
	SDL_Surface		*screen;
	SDL_Surface		*texture;
	SDL_Texture		*window;
	SDL_Renderer	*renderer;
	SDL_Window		*pwindow;
}				t_cube;

void			clean_exit(t_cube *data, char *str, int token);
float			ft_interpol(float nb1, float nb2, float alpha);
float			rsqrt(float number);

int             cliptriangle(t_cube *data);
int             newtriangles(t_cube *data);
void            rasterisation(t_cube *data, t_triangle triangle);

void			display(t_cube *data);
void			drawline(t_cube *data, t_vec3d p1, t_vec3d p2, int color);
void			drawtriangle(t_cube *data, t_triangle triangle, int color);
void			events(t_cube *data);
void            filltriangletext(t_cube *data, t_triangle triangle);
void            fill_top(t_cube *data, t_triangle triangle);
void            fill_bottom(t_cube *data, t_triangle triangle);
void            get_object(t_cube *data, t_mesh *mesh, char *file);

SDL_Surface		*new_surface(int w, int h);
uint32_t		get_pixel(t_cube *data, float samplex, float sampley);
void			putpixel(t_cube *data, int x, int y, int color);
void            swap_floats(float *a, float *b);

void			multiply_matrix(t_vec3d i, t_vec3d *o, t_mat m);
void			pmatrix(t_cube *data);
void			rotxmatrix(t_mat *matrix, float angle);
void			rotymatrix(t_mat *matrix, float angle);
void			rotzmatrix(t_mat *matrix, float angle);
void			transmatrix(t_mat *matrix, float x, float y, float z);

t_mat			mat_mulmatrix(t_mat m1, t_mat m2);
t_vec3d			mat_mulvector(t_mat m, t_vec3d i);
void			pointatmatrix(t_mat *matrix,
					t_vec3d pos, t_vec3d target, t_vec3d up);
void			quickinversematrix(t_mat *matrix, t_mat mpointat);

float			vecdotproduct(t_vec3d v1, t_vec3d v2);
float			veclen(t_vec3d v);
t_vec3d			vecadd(t_vec3d v1, t_vec3d v2);
t_vec3d			vecsub(t_vec3d v1, t_vec3d v2);
t_vec3d			veccrossproduct(t_vec3d v1, t_vec3d v2);
t_vec3d         vecintersectplane(t_cube *data, t_vec3d startl, t_vec3d endl);
t_vec3d			vecnormalise(t_vec3d v);
t_vec3d			vecmul(t_vec3d v, float k);
t_vec3d			vecdiv(t_vec3d v, float k);

#endif
