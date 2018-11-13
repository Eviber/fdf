/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:06:28 by ygaude            #+#    #+#             */
/*   Updated: 2018/11/13 21:46:21 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include "libft.h"
#include "fdf.h"

t_fdfval	**randmap(int *w, int *h)
{
	t_fdfval	**array;
	t_fdfval	*ptr;
	int			i;
	int			j;

	srand(time(NULL));
	*w = rand() % 49 + 2;
	*h = rand() % 49 + 2;
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
			(array[i][j]).alti = rand() % 20 - 10;
			(array[i][j]).color = rand() % 0x1000000;
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
