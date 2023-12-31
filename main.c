/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:57:05 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 12:55:51 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>

int	read_params(int argc, char **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments, must be 4 or 5\n");
		return (0);
	}
	if (ft_atoi(argv[1], &params->philo_n)
		&& ft_atoi(argv[2], &params->ttd)
		&& ft_atoi(argv[3], &params->tte)
		&& ft_atoi(argv[4], &params->tts))
	{
		params->min_meals = -1;
		if (argc == 6)
			return (ft_atoi(argv[5], &params->min_meals));
		return (1);
	}
	return (0);
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

	args = (t_philo_args *)vargs;
	args->params->philos[args->id].meals = 0;
	philo_routine(args->params, args->id);
	return (NULL);
}

void	cleanup_philos(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->philo_n)
		pthread_mutex_destroy(&params->philos[i++].fork_crit);
	pthread_mutex_destroy(&params->crit_mtx);
	pthread_mutex_destroy(&params->output_mtx);
	free(params->philos);
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
		args->params->philos[i].fork_status = -1;
		if (!(i % 2) && right(params, i) != 0)
		{
			printf("philo %2d is priviliged\n", i);
			args->params->philos[right(params, i)].fork_status = i;
			args->params->philos[left(params, i)].fork_status = i;
		}
		pthread_create(&params->philos[i].thread, NULL, &philo_init, args + i);
		i++;
	}
	while (--i > 0)
		pthread_join(params->philos[i].thread, NULL);
	free(args);
}

int	main(int argc, char **argv)
{
	t_params		params;

	if (!read_params(argc, argv, &params))
		return (1);
	params.total_finished = 0;
	params.dead_flag = 0;
	pthread_mutex_init(&params.crit_mtx, NULL);
	pthread_mutex_init(&params.output_mtx, NULL);
	init_threads(&params);
	cleanup_philos(&params);
}
