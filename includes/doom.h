/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/26 18:19:27 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>

# include <SDL2/SDL.h>

# include "../libft/libft.h"

# define W_WIDTH	1280
# define W_HEIGHT	720
# define W_LEN		W_WIDTH * W_HEIGHT
# define PNB_CHAR	10

# define FPS		120

enum			e_key
{
	DOWN,
	UP,
	R,
	S,
	X,
	Y,
	Z,
	KEY_MAX
};

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

typedef struct	s_mtl
{
	char		*name;
	int			i;
	int			ka;
	int			kd;
	int			ks;
	int			d;
	int			tr;
	int			ns;
	int			illum;
	int			map_ka;
	int			map_kd;
	int			map_ks;
	char		*map_name;
}				t_mtl;

typedef struct	s_triangle
{
	t_vec3d		v[3];
	t_vec2d		t[3];
	int			color;
	int			i;
	int			tex;
	t_mtl		ressources;
	SDL_Surface	*texture;
}				t_triangle;

typedef struct	s_object
{
	int			i;
	int			si;
	int			size;
	int			texture;
	char		*name;
	t_triangle	*mesh;
}				t_obj;

typedef struct	s_scene
{
	int			i;
	int			iobj;
	SDL_Surface	*texture;
	t_obj		*object;
}				t_scene;

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
	float		x1;
	float		y1;
	float		x2;
	float		y2;
	float		ax;
	float		bx;
	float		dax;
	float		dbx;
	float		u1;
	float		v1;
	float		w1;
	float		du1;
	float		dv1;
	float		dw1;
	float		u2;
	float		v2;
	float		w2;
	float		du2;
	float		dv2;
	float		dw2;
	float		su;
	float		sv;
	float		sw;
	float		eu;
	float		ev;
	float		ew;
	float		simples[6];
	float		steps[6];
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
	int				io;
	int				is;
	int				it;
	int				ac;
	int				color;
	int				fps;
	int				i;
	int				index;
	int				texture;
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
	int				io;
	int				s;
	int				ti;
	int				vcount;
	int				vtcount;
	int				vi;
	int				vti;
	int				nb;
	int				tnb;
	int				v[3];
	int				t[3];
	char			c[PNB_CHAR];
	int				mtl_max;
	t_mtl			*mtl_ressources;
	t_vec2d			*texture;
	t_vec3d			*vertex;
}				t_pdata;

typedef struct	s_mapeditor
{
	int			key[KEY_MAX];
}				t_editor;


typedef struct	s_mainenv
{
	float			dbuffer[W_LEN + 1];
	char			*str;
	char			**tab;
	t_cdata			cdata;
	t_editor		editor;
	t_fdata			fdata;
	t_matrix		matrix;
	t_pdata			pdata;
	t_var			var;
	t_vector		vector;
	t_scene			scene[20];
	SDL_Event		event;
	SDL_Surface		*screen;
	SDL_Surface		*texture;
	SDL_Texture		*window;
	SDL_Renderer	*renderer;
	SDL_Window		*pwindow;
}				t_doom;

void			clean_exit(t_doom *data, char *str, int token);
float			ft_interpol(float nb1, float nb2, float alpha);
float			rsqrt(float number);

int             cliptriangle(t_doom *data);
int             newtriangles(t_doom *data);
void            rasterisation(t_doom *data, t_triangle triangle);

void			display(t_doom *data);
void			drawline(t_doom *data, t_vec3d p1, t_vec3d p2, int color);
void			drawtriangle(t_doom *data, t_triangle triangle, int color);
void			events(t_doom *data);
void            filltriangletext(t_doom *data, t_triangle triangle);
void            fill_top(t_doom *data, t_triangle triangle);
void            fill_bottom(t_doom *data, t_triangle triangle);

void            get_object(t_doom *data, t_scene *scene, char *file);
void            parser_error(t_doom *data);
int             parser_goodchar(t_doom *data, char c);
void            parser_mtl(t_doom *data);
void            parser_mtlassign(t_doom *data, t_scene *scene, int *i);
void            parser_handlevertex(t_doom *data, t_scene *scene, int *start);
void			parser_stockvertex(t_doom *data, t_scene *scene, int *i);
void            skip_line(char *str, int *start);

void		    map_editor(t_doom *data);

SDL_Surface		*new_surface(int w, int h);
uint32_t		get_pixel(t_doom *data, float samplex, float sampley);
void			putpixel(t_doom *data, int x, int y, int color);
void            swap_floats(float *a, float *b);

void			pmatrix(t_doom *data);
void			rotxmatrix(t_mat *matrix, float angle);
void			rotymatrix(t_mat *matrix, float angle);
void			rotzmatrix(t_mat *matrix, float angle);
void			transmatrix(t_mat *matrix, float x, float y, float z);

t_triangle		mmvtriangle(t_mat matrix, t_triangle triangle);
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
t_vec3d         vecintersectplane(t_doom *data, t_vec3d startl, t_vec3d endl);
t_vec3d			vecnormalise(t_vec3d v);
t_vec3d			vecmul(t_vec3d v, float k);
t_vec3d			vecdiv(t_vec3d v, float k);

#endif
