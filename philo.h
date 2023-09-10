/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:49:31 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/07 16:01:02 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct s_philo
{
	pthread_t		*thread;
	pthread_mutex_t	*fork;
}	t_philo;

typedef struct s_params
{
	int		philo_n;
	int		ttd;
	int		tte;
	int		tts;
	int		min_eat_n;
	t_philo	*philos;
}	t_params;

int	ft_atoi(char *str);

#endif
