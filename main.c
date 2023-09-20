/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:57:05 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 02:28:36 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>

int	read_params(int argc, char **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
		return (0);
	params->philo_n = ft_atoi(argv[1]);
	params->ttd = ft_atoi(argv[2]);
	params->tte = ft_atoi(argv[3]);
	params->tts = ft_atoi(argv[4]);
	params->min_meals = -1;
	if (argc == 6)
		params->min_meals = ft_atoi(argv[5]);
	return (1);
}

void	philo_routine(t_params *params, int id)
{
	while (take_forks(params, id) && eat(params, id))
	{
		put_forks(params, id);
		if (!philosleep(params, id))
			break ;
	}
}

void	*philo_init(void *vargs)
{
	t_philo_args	*args;
	int				i;

	args = (t_philo_args *)vargs;
	args->params->philos[args->id].meals = 0;
	pthread_detach(args->params->philos[args->id].thread);
	i = 0;
	while (i < args->params->philo_n)
	{
		if (i != args->id)
			pthread_join(args->params->philos[i].thread, NULL);
		i++;
	}
	philo_routine(args->params, args->id);
	return (NULL);
}

void	init_threads(t_params *params)
{
	t_philo_args	*args;
	int				i;

	i = 0;
	args = malloc(sizeof(t_philo_args) * params->philo_n);
	params->philos = malloc(sizeof(t_philo) * params->philo_n);
	params->init_ts = get_ts();
	while (i < params->philo_n)
	{
		args[i].id = i;
		args[i].params = params;
		pthread_mutex_init(&params->philos[i].fork_crit, NULL);
		args->params->philos[i].last_meal_ets = 0;
		args->params->philos[i].fork_status = FREE;
		pthread_create(&params->philos->thread, NULL, &philo_init, args + i);
		i++;
	}
	while (--i > 0)
		pthread_join(params->philos[i].thread, NULL);
	free(params->philos);
	free(args);
}

int	main(int argc, char **argv)
{
	t_params		params;

	if (!read_params(argc, argv, &params))
		return (1);
	params.total_finished = 0;
	pthread_mutex_init(&params.crit_mtx, NULL);
	pthread_mutex_init(&params.output_mtx, NULL);
	init_threads(&params);
	pthread_mutex_destroy(&params.crit_mtx);
	pthread_mutex_destroy(&params.output_mtx);
}
