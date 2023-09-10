/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:57:05 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/07 16:03:49 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_params(int argc, char **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
		return (0);
	params->philo_n = ft_atoi(argv[1]);
	params->ttd = ft_atoi(argv[2]);
	params->tte = ft_atoi(argv[3]);
	params->tts = ft_atoi(argv[4]);
	if (argc == 6)
		params->min_eat_n = ft_atoi(argv[5]);
	return (1);
}

void	init_threads(t_params *params)
{
	int	i;

	i = 0;
	params->philos = malloc(sizeof(t_philo) * params->philo_n);
	while (i < params->philo_n)
	{
		pthread_mutext_init(params->philos[i].fork);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (!read_params(argc, argv, &params))
		return (1);
	init_threads(&params);
}
