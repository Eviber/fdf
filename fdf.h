/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:56:33 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/29 23:17:28 by ygaude           ###   ########.fr       */
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

typedef struct	s_mlxdata {
	t_map		map;
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

t_map			parse(char *path);

t_mlxdata		*getmlxdata(char *name);

void			ft_fswap(double *a, double *b);

double			fpart(double n);
double			rfpart(double n);
unsigned int	setal(float a, unsigned int rgb);
t_color			addcolors(t_color a, double r, double g, double b);
t_color			setcolors(t_wu wu, unsigned int from, unsigned int to);

void			drawline(t_point a, t_point b, unsigned int scol,
															unsigned int ecol);

#endif
