/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:36:20 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/14 00:33:33 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <SDL.h>
#include "libft.h"
#include "fdf.h"

static t_winenv			*sdl_init(char *name)
{
	t_winenv	*w;

	w = getsdlenv();
	if (!w || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		panic("Error while initializing SDL: ", SDL_GetError());
	if (SDL_GetDesktopDisplayMode(0, &(w->dispmode)))
		panic("SDL_GetDesktopDisplayMode failed: ", SDL_GetError());
	w->win = SDL_CreateWindow(name,
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				w->dispmode.w, w->dispmode.h, 0*SDL_WINDOW_FULLSCREEN);
	if (!w->win)
		panic("Error while creating window: ", SDL_GetError());
	w->render = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED);
	if (!w->render)
		panic("Error while creating renderer: ", SDL_GetError());
	return (w);
}

int			texinit(t_winenv *w)
{
	SDL_Texture *tex;

	tex = SDL_CreateTexture(w->render, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, w->dispmode.w, w->dispmode.h);
	if (!tex)
		panic("Error while creating tex: ", SDL_GetError());
	if (TTF_Init() == -1 || !(w->font = TTF_OpenFont("minecraft.ttf", 18)) ||
							!(w->bigfont = TTF_OpenFont("chargen.ttf", 48)))
		panic("Error while initializing SDL_TTF: ", TTF_GetError());
	SDL_RenderClear(w->render);
	return (1);
}

void		draw(t_env env)
{
	draw_map(env);
}

t_env		initenv(char *str)
{
	t_env		env;

	env.map = parse(str);
	env.d.x = WIN_H / (env.map.width - 1 + env.map.height - 1);
	env.d.y = env.d.x / 2;
	env.rot = env.d.x / 2;
	env.dhmax = 10;
	env.dh = env.dhmax * (env.rot - env.d.x) / env.d.x;
	env.start = WIN_H / 2 - ((env.map.height - env.map.width) * env.d.y) / 2;
	env.drawstyle = WU;
	env.colorstyle = NONE;
	env.trnsvrsl = 0;
	env.bg = 0x00000000;
	return (env);
}

void		loop(t_winenv *win, t_env env)
{
	SDL_Event	event;
	while (!win->quit)
	{
		while (SDL_PollEvent(&event))
			if (event.type == SDL_KEYDOWN)
				keyhook(event.key.keysym.scancode, &env);
		update(env);
	}
}

int			main(int argc, char **argv)
{
	t_winenv	*win;
	t_env		env;

	if (argc != 2)
	{
		ft_putstr("usage: fdf -r | filename\n");
		return (0);
	}
	errno = 0;
	env = initenv(argv[1]);
	win = sdl_init(argv[0]);
	update(env);
	//mlx_hook(win->win, 2, 2, keyhook, &env);
	//mlx_loop_hook(win->mlx, frame, &env);
	calc_map(env);
	draw(env);
	//mlx_put_image_to_window(win->mlx, win->win, win->imgptr, 0, 0);
	//mlx_loop(win->mlx);
	loop(win, env);
	return (0);
}
