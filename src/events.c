/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 21:32:04 by ygaude            #+#    #+#             */
/*   Updated: 2019/05/27 20:14:33 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <math.h>
#include "libft.h"
#include "fdf.h"

void	update(t_env env)
{
	t_winenv	*winenv;

	winenv = getsdlenv();
	SDL_SetRenderDrawBlendMode(winenv->render, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(winenv->render, winenv->tex);
	SDL_SetRenderDrawColor(winenv->render, 0, 0, 0, env.bg);
	//SDL_RenderClear(winenv->render);
	SDL_RenderFillRect(winenv->render, NULL);
	draw(env);
	SDL_SetRenderTarget(winenv->render, NULL);
	SDL_RenderCopy(winenv->render, winenv->tex, NULL, NULL);
	SDL_RenderPresent(winenv->render);
}

void	rotate(t_env *env, int up)
{
	env->rot += (5 * (env->d.x / 100)) * (up ? -1 : 1);
	if (env->rot > env->d.x * 2 || env->rot < -env->d.x * 2)
		env->rot = (env->rot > 0) ? -env->d.x * 2 : env->d.x * 2;
	env->dh = env->dhmax * (fabs(env->rot) - env->d.x) / env->d.x;
	env->d.y = env->rot;
	if (env->rot < -env->d.x)
		env->d.y = env->rot - 2 * (env->rot + env->d.x);
	else if (env->rot > env->d.x)
		env->d.y = env->rot - 2 * (env->rot - env->d.x);
	env->start = WIN_H / 2 - ((env->map.height - env->map.width) *
																env->d.y) / 2;
}

void	modifalti(t_env *env, const Uint8 *state)
{
	if (state[SDL_SCANCODE_KP_PLUS] || state[SDL_SCANCODE_KP_MINUS])
		env->dhmax += (state[SDL_SCANCODE_KP_MINUS]) ? 0.01 : -0.01;
	else
		env->dhmax += (state[SDL_SCANCODE_PAGEUP]) ? 0.1 : -0.1;
	env->dh = env->dhmax * (fabs(env->rot) - env->d.x) / env->d.x;
}

void	toggle(t_env *env, int key)
{
	if (key == SDL_SCANCODE_C)
		env->colorstyle = (env->colorstyle == NONE) ? MAPCOLOR : NONE;
	else if (key == SDL_SCANCODE_S)
		env->drawstyle = (env->drawstyle == POINT) ? WU : POINT;
	else
		env->trnsvrsl = !env->trnsvrsl;
}

int		keyhook(int key, t_env *env)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_PAGEDOWN] ||
			state[SDL_SCANCODE_PAGEUP] || state[SDL_SCANCODE_KP_PLUS] || state[SDL_SCANCODE_KP_MINUS])
	{
		if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN])
			rotate(env, state[SDL_SCANCODE_UP]);
		else
			modifalti(env, state);
		calc_map(*env);
	}
	if (key == SDL_SCANCODE_C || key == SDL_SCANCODE_S || key == SDL_SCANCODE_T)
		toggle(env, key);
	else if (key == SDL_SCANCODE_B)
		env->bg = ((unsigned)env->bg == 30) ? 255 : 30;
	if (state[SDL_SCANCODE_ESCAPE] || SDL_QuitRequested())
		exit(0);
	return (0);
}
