/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:04:25 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 17:56:50 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	print_status(t_params *params, char *fstring, int ts, int id)
{
	pthread_mutex_lock(&params->output_mtx);
	printf(fstring, ts, id + 1);
	pthread_mutex_unlock(&params->output_mtx);
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

int	philosleep(t_params *params, int id)
{
	int	start_ts;

	if (check_dead(params, id))
		return (0);
	start_ts = get_ets(params);
	print_status(params, "%d %d is sleeping\n", start_ts, id);
	while ((get_ets(params) - start_ts) < params->tts)
		if (check_dead(params, id))
			return (0);
	return (1);
}

void	try_forks(t_params *params, int id, int *forks)
{
	pthread_mutex_lock(&params->philos[left(params, id)].fork_crit);
	if (!(*forks & L_FORK)
		&& (params->philos[left(params, id)].fork_status == -1
			|| params->philos[left(params, id)].fork_status == id))
	{
		//print_status(params, "%10d %2d got left fork\n", get_ets(params), id);
		*forks |= L_FORK;
		params->philos[left(params, id)].fork_status = id;
	}
	pthread_mutex_unlock(&params->philos[left(params, id)].fork_crit);
	pthread_mutex_lock(&params->philos[right(params, id)].fork_crit);
	if (right(params, id) != left(params, id) && !(*forks & R_FORK)
		&& (params->philos[right(params, id)].fork_status == -1
			|| params->philos[right(params, id)].fork_status == id))
	{
		//print_status(params, "%10d %2d got right fork\n", get_ets(params), id);
		*forks |= R_FORK;
		params->philos[right(params, id)].fork_status = id;
	}
	pthread_mutex_unlock(&params->philos[right(params, id)].fork_crit);
}

int	take_forks(t_params *params, int id)
{
	int	start_ts;
	int	forks;

	if (check_dead(params, id))
		return (0);
	forks = 0;
	start_ts = get_ets(params);
	print_status(params, "%d %d is thinking\n", start_ts, id);
	while (!check_dead(params, id))
	{
		try_forks(params, id, &forks);
		if (forks == BOTH_FORKS)
			return (1);
	}
	return (0);
}

int	eat(t_params *params, int id)
{
	if (check_dead(params, id))
		return (0);
	params->philos[id].last_meal_ets = get_ets(params);
	print_status(params, "%d %d is eating\n", \
			params->philos[id].last_meal_ets, id);
	while ((get_ets(params) - params->philos[id].last_meal_ets) < params->tte)
		if (check_dead(params, id))
			return (0);
	if (params->min_meals > -1
		&& ++params->philos[id].meals == params->min_meals)
	{
		pthread_mutex_lock(&params->crit_mtx);
		if (++params->total_finished == params->philo_n)
		{
			params->dead_flag = 1;
			pthread_mutex_unlock(&params->crit_mtx);
			return (0);
		}
		pthread_mutex_unlock(&params->crit_mtx);
	}
	return (1);
}

void	put_forks(t_params *params, int id)
{
	pthread_mutex_lock(&params->philos[left(params, id)].fork_crit);
	params->philos[left(params, id)].fork_status = -1;
	pthread_mutex_unlock(&params->philos[left(params, id)].fork_crit);
	pthread_mutex_lock(&params->philos[right(params, id)].fork_crit);
	params->philos[right(params, id)].fork_status = -1;
	pthread_mutex_unlock(&params->philos[right(params, id)].fork_crit);
}
