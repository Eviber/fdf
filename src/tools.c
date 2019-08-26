/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:02:27 by ygaude            #+#    #+#             */
/*   Updated: 2019/08/26 18:19:24 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "fdf.h"
#include "libft.h"

int				fdf_isnumber(char *str)
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
