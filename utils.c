/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:53:43 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/07 15:53:49 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_is_sign(char c)
{
	return (c == '+' || c == '-');
}

int	ft_atoi(char *str)
{
	int	numb;
	int	sign;

	numb = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (ft_is_sign(*str))
	{
		sign *= (*str == '-') * -2 + 1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		numb *= 10;
		numb += (int)(*str - '0');
		str++;
	}
	return (sign * numb);
}
