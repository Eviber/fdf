/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:48 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/11 20:37:09 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "libft/libft.h"
#include "fdf.h"

int			**randmap(char *path, int *w, int *h)
{
	int		**array;
	int		*ptr;
	int		i;
	int		j;

	(void)path;
	*w = rand() % 50 + 2;
	*h = rand() % 50 + 2;
	array = (int **)ft_memalloc(*h * sizeof(int *) + (*w * *h * sizeof(int)));
	ptr = (int *)(array + *h);
	i = -1;
	while (++i < *h)
		array[i] = ptr + (i * *w);
	i = -1;
	while (++i < *h && (j = -1))
		while (++j < *w)
			array[i][j] = rand() % 50;
	i = -1;
	while (++i < *h && (j = -1))
	{
		while (++j < *w)
			printf("%-5d", array[i][j]);
		printf("\n");
	}
	return (array);
}

void		exit_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(errno);
}

#define FILE_MAXSIZE 100000000
#include <unistd.h>

char		*readfile(char *path)
{
	ssize_t	size;
	int		fd;
	char	*str;

	fd = open(path, O_RDONLY);
	if (fd == -1 || !(str = malloc(FILE_MAXSIZE + 1)))
		exit_error(strerror(errno));
	if ((size = read(fd, str, FILE_MAXSIZE + 1)) == -1)
		exit_error(strerror(errno));
	if (size > FILE_MAXSIZE)
		exit_error("File too large");
	str[size] = '\0';
	return (str);
}

int			isnumber(char *str)
{
	int		i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
	{
		i++;
	}
}

void		getmapsize(char *str, int *w, int *h)
{
	int		i;
	int		wd;

	*w = 0;
	*h = -1;
	while (*str)
	{
		i = 0;
		while (*str && *str != '\n')
		{
			i += ((!i || ft_isspace(*str)) && !ft_isspace(*str));
			str++;
		}
		if (i != *w && *w != -1)
			exit_error("Map error (line length)");
		*w = i;
		str += i + (str[i] == '\n');
		*str = (*str == '\n') ? '\0' : *str;
		(*w)++;
	}
}

int			**parsefile(char *path, int *w, int *h)
{
	char	*file;

	file = readfile(path);
	getmapsize(file, w, h);
	printf("w = %d, h = %d\n", *w, *h);
	free(file);
}

t_map		parse(char *path)
{
	t_map	map;
	t_point	*ptr;
	int		i;

	if (ft_strequ(path, "-r"))
		map.array = randmap(path, &(map.width), &(map.height));
	else
		map.array = parsefile(path, &(map.width), &(map.height));
	map.grid = (t_point **)ft_memalloc(map.height * sizeof(t_point *) + (map.width * map.height * sizeof(t_point *)));
	ptr = (t_point *)(map.grid + map.height);
	i = -1;
	while (++i < map.height)
		map.grid[i] = ptr + (i * map.width);
	return (map);
}
