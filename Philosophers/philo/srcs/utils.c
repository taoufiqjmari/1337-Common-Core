/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:06:47 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/14 12:13:06 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	time_difference(long old)
{
	struct timeval	time;
	long			difference;

	gettimeofday(&time, NULL);
	difference = (time.tv_sec * 1000) + (time.tv_usec / 1000) - old;
	return (difference);
}

void	init_mutexes(t_input *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_mutex_init(&data->death[i], NULL);
		i++;
	}
	pthread_mutex_init(data->display, NULL);
	pthread_mutex_init(data->eating_manipulation, NULL);
}

_Bool	start_evens(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (*philos).input->num_of_philos)
	{
		if (!(i % 2))
		{
			if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
			{
				printf("Failed to create thread\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

_Bool	start_odds(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (*philos).input->num_of_philos)
	{
		if (i % 2)
		{
			if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
			{
				printf("Failed to create thread\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	free_resources(t_philo *philos, t_input *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->death[i]);
		i++;
	}
	pthread_mutex_destroy(data->display);
	pthread_mutex_destroy(data->eating_manipulation);
	free(data->fork);
	free(data->death);
	free(data->display);
	free(data);
	free(philos);
}
