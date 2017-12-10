/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:56:33 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/10 16:48:35 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_W 1080.0
# define WIN_H 1080.0
# define FILE_MAXSIZE 100000000

# define ARROW_UP 0x7e
# define ARROW_DOWN 0x7d
# define ARROW_LEFT 0x7b
# define ARROW_RIGHT 0x7c
# define NUMPAD_PLUS 0x4e
# define NUMPAD_MINUS 0x45
# define KEY_C 0x8
# define KEY_S 0x1
# define KEY_T 0x11
# define KEY_PGDWN 0x79
# define KEY_PGUP 0x74

enum { POINT, QUICK, WU };
enum { NONE, MAPCOLOR, ALTICOLOR };

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_intpoint
{
	int			x;
	int			y;
}				t_intpoint;

typedef struct	s_line
{
	t_point		a;
	t_point		b;
}				t_line;

typedef struct	s_fdfval
{
	int				alti;
	unsigned int	color;
}				t_fdfval;

typedef struct	s_map
{
	t_point		**grid;
	t_fdfval	**array;
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
	double		rot;
	double		dh;
	double		dhmax;
	int			start;
	int			drawstyle;
	int			colorstyle;
	int			trnsvrsl;
	int			bg;
}				t_env;

void			exit_error(char *str);
t_map			parse(char *path);

char			*readfile(char *path);
t_fdfval		**randmap(int *w, int *h);
t_mlxdata		*getmlxdata(char *name);
int				keyhook(int key, void *cetruc);

void			ft_fswap(double *a, double *b);

int				isnumber(char *str);
char			*nextnum(char *str);
double			fpart(double n);
double			rfpart(double n);
unsigned int	setal(float a, unsigned int rgb);
t_color			addcolors(t_color a, double r, double g, double b);
t_color			setcolors(double diff, unsigned int from, unsigned int to);

void			imgputpixel(int x, int y, unsigned int color);
void			draw(t_env	env);
void			update(t_env env);
void			wuline(t_point a, t_point b, unsigned int scol,
															unsigned int ecol);
void			rawline(t_point a, t_point b, unsigned int color);
void			draw_grid(t_env map);
void			draw_map(t_env env);
void			calc_map(t_env env);

#endif
