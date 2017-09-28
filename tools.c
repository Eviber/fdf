/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:02:27 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/28 16:40:33 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "minilibx_macos/mlx.h"
#include "fdf.h"

double			fpart(double n)
{
	return (n - floor(n));
}

double			rfpart(double n)
{
	return (1 - fpart(n));
}

unsigned int	setal(float a, unsigned int rgb)
{
	return ((((char)round(255 - (a * 255))) << 24) + rgb);
}
