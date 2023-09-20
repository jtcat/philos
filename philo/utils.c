/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:53:43 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 19:30:33 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_dead(t_params *params, int id)
{
	pthread_mutex_lock(&params->crit_mtx);
	if (params->dead_flag)
	{
		pthread_mutex_unlock(&params->crit_mtx);
		return (1);
	}
	if ((get_ets(params) - params->philos[id].last_meal_ets) >= params->ttd)
	{
		params->dead_flag = 1;
		print_status(params, "%d philo %d died\n", get_ets(params), id);
		pthread_mutex_unlock(&params->crit_mtx);
		return (1);
	}
	pthread_mutex_unlock(&params->crit_mtx);
	return (0);
}
