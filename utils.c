/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:53:43 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 02:40:35 by joaoteix         ###   ########.fr       */
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

int	is_numb(char *str)
{
	while (*str)
		if (!ft_isdigit(*(str++)))
			return (0);
	return (1);
}

int	check_intof(char *str)
{
	char const	*max_str = "2147483647";
	int			is_of;
	int			i;

	is_of = 1;
	i = 1;
	while (str[i])
	{
		is_of = str[i] < max_str[i];
		i++;
	}
	return (is_of);
}

int	ft_atoi(char *str)
{
	int	numb;
	int	sign;

	numb = 0;
	sign = 1;
	if (!is_numb(str))
		return (-1);
	if (check_intof(str))
		return (-2);
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
