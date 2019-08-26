/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:56:33 by ygaude            #+#    #+#             */
/*   Updated: 2019/08/26 18:19:38 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <SDL.h>
# include <SDL_ttf.h>

# define WIN_W 1080.0
# define WIN_H 1080.0
# define FILE_MAXSIZE 100000000

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
	double		dt;
	int			start;
	int			drawstyle;
	int			colorstyle;
	int			trnsvrsl;
	int			bg;
}				t_env;

typedef struct		s_winenv
{
	SDL_DisplayMode	dispmode;
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Texture		*tex;
	TTF_Font		*bigfont;
	TTF_Font		*font;
	int				quit;
}					t_winenv;


/*
**	input
*/

t_map			parse(char *path);
char			*readfile(char *path);
t_fdfval		**randmap(int *w, int *h);


/*
** Utilities
*/

void				panic(const char *str, const char *str2);
SDL_Texture			*strtotex(char *str, t_winenv env, TTF_Font *f);
t_winenv			*getsdlenv(void);
double				dist(double x1, double y1, double x2, double y2);
int					quitvisu(t_winenv *env);


/*
** basic drawing
*/

void			imgputpixel(int x, int y, unsigned int color);
void			draw(t_env	env);
void			update(t_env env);
void			wuline(t_point a, t_point b, unsigned int scol, unsigned int ecol);


/*
**	xiaoling wu
*/

void			ft_fswap(double *a, double *b);
int				fdf_isnumber(char *str);
char			*nextnum(char *str);
double			fpart(double n);
double			rfpart(double n);
unsigned int	setal(float a, unsigned int rgb);
t_color			addcolors(t_color a, double r, double g, double b);
t_color			setcolors(double diff, unsigned int from, unsigned int to);


/*
**	tools
*/

int				keyhook(int key, t_env *env);


/*
**	drawing
*/

void			rawline(t_point a, t_point b, unsigned int color);
void			draw_grid(t_env map);
void			draw_map(t_env env);
void			calc_map(t_env env);

#endif
