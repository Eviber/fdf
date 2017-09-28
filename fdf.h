/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:56:33 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/28 15:47:08 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_W 640
# define WIN_H 480

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

typedef struct	s_mlxdata { void			*mlx;
	void			*win;
	void			*imgptr;
	char			*img;
	int				bpp;
	int				sizeline;
	int				endian;
}				t_mlxdata;

typedef struct	s_wu
{
	double	gradient;
	t_point	end;
	t_point	pxstart;
	t_point	pxend;
	double	intery;
	int		steep;
}				t_wu;

t_mlxdata		*getmlxdata(char *name);

void			ft_fswap(double *a, double *b);

double			fpart(double n);
double			rfpart(double n);

unsigned int	setal(float a, unsigned int rgb);

void			drawline(t_point a, t_point b, unsigned int color);

#endif
