/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:48 by ygaude            #+#    #+#             */
/*   Updated: 2019/05/28 16:25:48 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "libft.h"
#include "fdf.h"

void		getmapsize(char *str, int *w, int *h)
{
	int		wd;

	*w = -1;
	*h = 0;
	while (*str)
	{
		wd = 0;
		while (ft_isspace(*str))
			str++;
		while (*str && *str != '\n')
		{
			if (!isnumber(str))
				panic("Parse error", "\n");
			wd++;
			str = nextnum(str);
		}
		if (wd != *w && *w != -1 && !(!(*str) && !(wd)))
			panic("Map error (line length)", "\n");
		(*h) += (*str || wd);
		if (*w == -1)
			*w = wd;
	}
}

t_fdfval	getval(char *str)
{
	t_fdfval	val;

	val.alti = ft_atoi(str);
	val.color = 0x00FFFFFF;
	while (ft_isdigit(*str))
		str++;
	if (*str == ',')
	{
		str++;
		if (str[0] == '0' && ft_toupper(str[1]) == 'X')
			val.color = ft_atoi_base(str, 16);
		else
			val.color = ft_atoi_base(str, 10);
	}
	return (val);
}

t_fdfval	**parsemap(char *file, int w, int h)
{
	t_fdfval	**array;
	t_fdfval	*ptr;
	int			i;
	int			j;

	if (!(array = (t_fdfval **)ft_memalloc(h * sizeof(t_fdfval *) +
									(w * h * sizeof(t_fdfval)))))
		panic(strerror(errno), "\n");
	ptr = (t_fdfval *)(array + h);
	i = -1;
	while (++i < h)
		array[i] = ptr + (i * w);
	i = -1;
	while (++i < h && (j = -1))
		while (++j < w)
		{
			while (*file && ft_isspace(*file))
				file++;
			if (*file)
			{
				array[i][j] = getval(file);
				file = nextnum(file);
			}
		}
	return (array);
}

int			setval(int x, int y, double ratio)
{
	return (round((double)x + ((double)(y - x) * ratio)));
}

int			blend(int cx, int cy, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = setval((cx >> 16) & 0xFF, (cy >> 16) & 0xFF, ratio);
	g = setval((cx >> 8) & 0xFF, (cy >> 8) & 0xFF, ratio);
	b = setval(cx & 0xFF, cy & 0xFF, ratio);
	return (r << 16 | g << 8 | b);
}

void		setcolor(t_fdfval **array, int w, int h)
{
	int		i;
	int		j;
	int		max;
	int		min;

	max = array[0][0].alti;
	min = max;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (array[i][j].alti > max)
				max = array[i][j].alti;
			else if (array[i][j].alti < min)
				min = array[i][j].alti;
			j++;
		}
		i++;
	}
	printf("%d\n", min);
	int		colors[4];
	double	alti;

	colors[0] = 0x0a4f01;
	colors[1] = 0xf6ff46;
	colors[2] = 0x760600;
	colors[3] = 0xf0dfd7;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			alti = (double)(array[i][j].alti - min) / (double)(max - min);
			if (alti < 37./74.)
				array[i][j].color = blend(colors[0], colors[1], alti / (37./74.));
			else if (alti < 65./74.)
				array[i][j].color = blend(colors[1], colors[2], (alti - (37./74.)) / ((65./74.) - (37./74.)));
			else
				array[i][j].color = blend(colors[2], colors[3], (alti - (65./74.)) / (1 - (65./74.)));
			array[i][j].color = blend(0x00cc00, 0xffffff, (double)(array[i][j].alti) / (double)(max));
			if (array[i][j].alti <= 0)
			{
				array[i][j].color = blend(0x000055, 0x6666dd, (double)(array[i][j].alti - min) / (double)(-min));
			}
			j++;
		}
		i++;
	}
}

t_map		parse(char *path)
{
	t_map	map;
	t_point	*ptr;
	char	*file;
	int		i;

	if (ft_strequ(path, "-r"))
		map.array = randmap(&(map.width), &(map.height));
	else
	{
		file = readfile(path);
		getmapsize(file, &(map.width), &(map.height));
		map.array = parsemap(file, map.width, map.height);
		ft_strdel(&file);
	}
	setcolor(map.array, map.width, map.height);
	if (!(map.grid = (t_point **)malloc(map.height * sizeof(t_point *) +
				(map.width * map.height * sizeof(t_point)))))
		panic(strerror(errno), "\n");
	ptr = (t_point *)(map.grid + map.height);
	i = -1;
	while (++i < map.height)
		map.grid[i] = ptr + (i * map.width);
	return (map);
}
