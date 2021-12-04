/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:09:03 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/14 12:47:06 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>	// memset(3)
# include <stdio.h>		// printf(1)
# include <stdlib.h>	// malloc(3), free(3)
# include <unistd.h>	// write(2), usleep(3)
# include <sys/time.h>	// gettimeofday(2)
# include <pthread.h>	// pthread_create(3), pthread_detach(3), pthread_join(3)
						// pthread_mutex_init(3), pthread_mutex_destroy(3)
						// pthread_mutex_lock(3), pthread_mutex_unlock(3)

typedef struct s_input {
	int				num_of_philos;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			must_eat;
	long			start;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*display;
	pthread_mutex_t	*death;
	pthread_mutex_t	*eating_manipulation;
}					t_input;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	long			start_eating;
	int				eating_times;
	int				is_eating;
	struct s_input	*input;
}					t_philo;

int		ft_atoi(const char *str);

void	*routine(void *args);
_Bool	supervisor(t_philo *philos);

void	printing(t_philo *philo, int color, char *msg);
long	time_difference(long old);
void	init_mutexes(t_input *data);
_Bool	start_evens(t_philo *philos);
_Bool	start_odds(t_philo *philos);
void	free_resources(t_philo *philos, t_input *data);

#endif
