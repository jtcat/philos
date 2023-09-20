/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoteix <joaoteix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:49:31 by joaoteix          #+#    #+#             */
/*   Updated: 2023/09/20 03:12:18 by joaoteix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bits/types/struct_timeval.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

enum e_fork_status
{
	FREE,
	OWNED
};

typedef struct s_philo
{
	pthread_t		thread;
	int				last_meal_ets;
	int				meals;
	int				fork_status;
	pthread_mutex_t	fork_crit;
}	t_philo;

typedef struct s_params
{
	int				philo_n;
	int				ttd;
	int				tte;
	int				tts;
	int				min_meals;
	int				init_ts;
	int				total_finished;
	t_philo			*philos;
	pthread_mutex_t	output_mtx;
	pthread_mutex_t	crit_mtx;
}	t_params;

typedef struct s_philo_args
{
	int			id;
	t_params	*params;
}	t_philo_args;

// Utils
int		left(t_params *params, int id);
int		right(t_params *params, int id);
int		get_ts(void);
int		get_ets(t_params *params);
int		ft_atoi(char *str, int *dst);

// Philo actions
int		philosleep(t_params *params, int id);
int		take_forks(t_params *params, int id);
int		eat(t_params *params, int id);
void	put_forks(t_params *params, int id);

#endif
