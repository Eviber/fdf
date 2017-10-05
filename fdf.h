/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:56:33 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/05 23:38:08 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_W 1920.0
# define WIN_H 1080.0

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_line
{
	t_point		a;
	t_point		b;
}				t_line;

typedef struct	s_map
{
	t_point		**grid;
	int			**array;
	int			width;
	int			height;
}				t_map;

typedef struct	s_mlxdata
{
	void		*mlx;
	void		*win;
	void		*imgptr;
	char		*img;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_mlxdata;

typedef struct	s_wu
{
	double		gradient;
	t_point		end;
	t_point		pxstart;
	t_point		pxend;
	double		intery;
	int			steep;
}				t_wu;

typedef struct	s_color
{
	double		a;
	double		r;
	double		g;
	double		b;
}				t_color;

typedef struct	s_env
{
	t_map		map;
	t_point		d;
	int			startpoint;
}				t_env;

t_map			parse(char *path);

t_mlxdata		*getmlxdata(char *name);
int				keyhook(int key, void *cetruc);

void			ft_fswap(double *a, double *b);

double			fpart(double n);
double			rfpart(double n);
unsigned int	setal(float a, unsigned int rgb);
t_color			addcolors(t_color a, double r, double g, double b);
t_color			setcolors(double diff, unsigned int from, unsigned int to);

void			draw(t_env	env);
void			update(void);
void			drawline(t_point a, t_point b, unsigned int scol,
															unsigned int ecol);
void			draw_grid(t_env map);
void			draw_map(t_env map);

#endif
