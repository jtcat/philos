/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:04:25 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 10:36:57 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int	check_dead(t_params *params, int id)
{
	pthread_mutex_lock(&params->crit_mtx);
	if (params->dead_flag)
	{
		pthread_mutex_unlock(&params->crit_mtx);
		return (1);
	}
	pthread_mutex_unlock(&params->crit_mtx);
	if ((get_ets(params) - params->philos[id].last_meal_ets) >= params->ttd)
	{
		pthread_mutex_lock(&params->crit_mtx);
		params->dead_flag = 1;
		pthread_mutex_unlock(&params->crit_mtx);
		pthread_mutex_lock(&params->output_mtx);
		printf("%10d %2d died\n", get_ets(params), id);
		pthread_mutex_unlock(&params->output_mtx);
		return (1);
	}
	return (0);
}

int	philosleep(t_params *params, int id)
{
	int	start_ts;

	if (check_dead(params, id))
		return (0);
	start_ts = get_ets(params);
	pthread_mutex_lock(&params->output_mtx);
	printf("%10d %2d is sleeping\n", start_ts, id);
	pthread_mutex_unlock(&params->output_mtx);
	while ((get_ets(params) - start_ts) < params->tts)
		if (check_dead(params, id))
			return (0);
	return (1);
}

int	take_forks(t_params *params, int id)
{
	int	start_ts;
	int	owned_forks;

	if (check_dead(params, id))
		return (0);
	owned_forks = 0;
	start_ts = get_ets(params);
	pthread_mutex_lock(&params->output_mtx);
	printf("%10d %2d is thinking\n", start_ts, id);
	pthread_mutex_unlock(&params->output_mtx);
	while (!check_dead(params, id))
	{
		pthread_mutex_lock(&params->philos[left(params, id)].fork_crit);
		if (params->philos[left(params, id)].fork_status == FREE
			&& ++owned_forks)
			params->philos[left(params, id)].fork_status = OWNED;
		pthread_mutex_unlock(&params->philos[left(params, id)].fork_crit);
		pthread_mutex_lock(&params->philos[right(params, id)].fork_crit);
		if (params->philos[right(params, id)].fork_status == FREE
			&& ++owned_forks)
			params->philos[right(params, id)].fork_status = OWNED;
		pthread_mutex_unlock(&params->philos[right(params, id)].fork_crit);
		if (owned_forks == 2)
			return (1);
	}
	return (0);
}

int	eat(t_params *params, int id)
{
	if (check_dead(params, id))
		return (0);
	params->philos[id].last_meal_ets = get_ets(params);
	pthread_mutex_lock(&params->output_mtx);
	printf("%10d %2d is eating\n", params->philos[id].last_meal_ets, id);
	pthread_mutex_unlock(&params->output_mtx);
	while ((get_ets(params) - params->philos[id].last_meal_ets) < params->tte)
		if (check_dead(params, id))
			return (0);
	if (params->min_meals > -1
		&& ++params->philos[id].meals == params->min_meals)
	{
		pthread_mutex_lock(&params->crit_mtx);
		if (++params->total_finished == params->philo_n)
			return (0);
		pthread_mutex_unlock(&params->crit_mtx);
	}
	return (1);
}

void	put_forks(t_params *params, int id)
{
	pthread_mutex_lock(&params->philos[left(params, id)].fork_crit);
	params->philos[left(params, id)].fork_status = FREE;
	pthread_mutex_unlock(&params->philos[left(params, id)].fork_crit);
	pthread_mutex_lock(&params->philos[right(params, id)].fork_crit);
	params->philos[right(params, id)].fork_status = FREE;
	pthread_mutex_unlock(&params->philos[right(params, id)].fork_crit);
}
