/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:02:27 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/17 16:28:16 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include "libft.h"

int				isnumber(char *str)
{
	while (ft_isspace(*str) && *str != '\n')
		str++;
	str += (*str == '-');
	while (ft_isdigit(*str))
		str++;
	if (*str == ',')
	{
		str += (str[1] == '0' && ft_toupper(str[2]) == 'X') ? 3 : 1;
		while (ft_isalnum(*str) && ft_toupper(*str) <= 'F')
			str++;
	}
	return (ft_isspace(*str) || !(*str));
}

char			*nextnum(char *str)
{
	while (*str && !ft_isspace(*str) && *str != '\n')
		str++;
	while (ft_isspace(*str) && *str != '\n')
		str++;
	return (str);
}

void			exit_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(errno);
}
