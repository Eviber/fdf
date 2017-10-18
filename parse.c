/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:48 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/18 04:01:53 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "libft/libft.h"
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
				exit_error("Parse error");
			wd++;
			str = nextnum(str);
		}
		if (wd != *w && *w != -1 && !(!(*str) && (*w)))
			exit_error("Map error (line length)");
		(*h) += (*str || wd);
		if (*str)
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

	array = (t_fdfval **)ft_memalloc(h * sizeof(t_fdfval *) +
									(w * h * sizeof(t_fdfval)));
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
	map.grid = (t_point **)ft_memalloc(map.height * sizeof(t_point *) +
				(map.width * map.height * sizeof(t_point)));
	ptr = (t_point *)(map.grid + map.height);
	i = -1;
	while (++i < map.height)
		map.grid[i] = ptr + (i * map.width);
	return (map);
}
