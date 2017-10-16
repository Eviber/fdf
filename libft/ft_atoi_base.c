/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 18:07:30 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/16 20:27:17 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	dtoi_base(char c)
{
	return ((ft_isdigit(c)) ? c - '0' : 10 + ft_toupper(c) - 'A');
}

int			ft_atoi_base(char *str, int base)
{
	size_t	i;
	int		sign;
	int		res;

	i = 0;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	i += (str[i] == '-' || str[i] == '+');
	i += (str[i] == '0' && (base == 8 || base == 16));
	i += (ft_toupper(str[i]) == 'X' && i && str[i - 1] == '0' && base == 16);
	while (ft_isalnum(str[i]) && dtoi_base(str[i]) < base)
		res = res * base + (sign * dtoi_base(str[i++]));
	return (res);
}
