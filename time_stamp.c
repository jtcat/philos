/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:52:18 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 02:11:48 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Milliseconds
int	get_ts(void)
{
	struct timeval	ts;

	gettimeofday(&ts, NULL);
	return (ts.tv_sec * 1000 + ts.tv_usec / 1000);
}

int	get_ets(t_params *params)
{
	return (get_ts() - params->init_ts);
}

int	left(t_params *params, int id)
{
	return ((id + params->philo_n) % params->philo_n);
}

int	right(t_params *params, int id)
{
	return ((id + 1) % params->philo_n);
}
