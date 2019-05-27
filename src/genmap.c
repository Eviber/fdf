/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:06:28 by ygaude            #+#    #+#             */
/*   Updated: 2019/05/27 21:25:59 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include "libft.h"
#include "fdf.h"
#include "open-simplex-noise.h"

#define FEATURE_SIZE 24

int			getVal(struct osn_context *ctx, int x, int y)
{
	double v0;
	double v1;
	double v2;
	double value;

	v0 = open_simplex_noise2(ctx, (double) x / FEATURE_SIZE / 4, (double) y / FEATURE_SIZE / 4);
	v1 = open_simplex_noise2(ctx, (double) x / FEATURE_SIZE / 2, (double) y / FEATURE_SIZE / 2);
	v2 = open_simplex_noise2(ctx, (double) x / FEATURE_SIZE / 1, (double) y / FEATURE_SIZE / 1);
	value = v0 * 4 / 7.0 + v1 * 2 / 7.0 + v2 * 1 / 7.0;
	return ((int)lround(value * 100));
}

t_fdfval	**randmap(int *w, int *h)
{
	t_fdfval	**array;
	t_fdfval	*ptr;
	int			i;
	int			j;
	struct osn_context *ctx;

	srand(time(NULL));
	open_simplex_noise(rand(), &ctx);
	*w = rand() % 512 + 512;
	*h = *w;
	if (!(array = (t_fdfval **)malloc(*h * sizeof(t_fdfval *) +
					(*w * *h * sizeof(t_fdfval)))))
		panic(strerror(errno), "\n");
	ptr = (t_fdfval *)(array + *h);
	i = -1;
	while (++i < *h)
		array[i] = ptr + (i * *w);
	i = -1;
	while (++i < *h && (j = -1))
		while (++j < *w)
		{
			(array[i][j]).alti = getVal(ctx, i, j);
			(array[i][j]).color = 0xFFFFFF;
		}
	return (array);
}

char		*readfile(char *path)
{
	ssize_t	size;
	int		fd;
	char	*str;

	str = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1 || !(str = malloc(FILE_MAXSIZE + 1)))
		panic(strerror(errno), "\n");
	if ((size = read(fd, str, FILE_MAXSIZE + 1)) == -1)
		panic(strerror(errno), "\n");
	if (size > FILE_MAXSIZE)
		panic("File too large", "\n");
	str[size] = '\0';
	return (str);
}
