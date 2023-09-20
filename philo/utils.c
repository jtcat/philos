/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:53:43 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 10:01:22 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_numb(char *str)
{
	while (*str)
		if (!ft_isdigit(*(str++)))
			return (0);
	return (1);
}

int	check_intof(char *str)
{
	char const	max_str[] = "2147483647";
	int			i;
	int			overdigit;

	i = 0;
	overdigit = 0;
	while (max_str[i] && str[i])
	{
		overdigit = str[i] > max_str[i];
		i++;
	}
	return (i == 10 && (str[i] || overdigit));
}

int	ft_atoi(char *str, int *dst)
{
	if (!is_numb(str) || check_intof(str))
	{
		printf("Argument is not a valid number: %s\n", str);
		return (0);
	}
	*dst = 0;
	while (*str)
	{
		*dst *= 10;
		*dst += (int)(*str - '0');
		str++;
	}
	return (1);
}
