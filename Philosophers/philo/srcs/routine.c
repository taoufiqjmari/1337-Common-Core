/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:36:46 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/14 15:48:27 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	printing(t_philo *philo, int color, char *msg)
{
	long			difference;

	pthread_mutex_lock(philo->input->display);
	difference = time_difference(philo->input->start);
	printf("\033[0;%dm%.4ld	%d %s\n", color, difference, philo->id + 1, msg);
	pthread_mutex_unlock(philo->input->display);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->input->eating_manipulation);
	philo->is_eating = 1;
	philo->start_eating = time_difference(0);
	philo->eating_times++;
	pthread_mutex_unlock(philo->input->eating_manipulation);
	printing(philo, 34, "is eating");
	usleep(((philo->input->t_eat * 90) / 100) * 1000);
	while (time_difference(philo->start_eating) < philo->input->t_eat)
		usleep(100);
	pthread_mutex_lock(philo->input->eating_manipulation);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->input->eating_manipulation);
}

static void	sleeping_thinking(t_philo *philo)
{
	long	start_time;

	start_time = time_difference(0);
	printing(philo, 33, "is sleeping");
	usleep(((philo->input->t_sleep * 90) / 100) * 1000);
	while (time_difference(start_time) < philo->input->t_eat)
		usleep(100);
	printing(philo, 32, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		num_of_philos;
	int		id;

	philo = (t_philo *)arg;
	num_of_philos = philo->input->num_of_philos;
	id = philo->id;
	while (1)
	{
		pthread_mutex_lock(&philo->input->fork[id]);
		printing(philo, 37, "has taken a fork");
		pthread_mutex_lock(&philo->input->fork[(id + 1) % num_of_philos]);
		pthread_mutex_lock(&philo->input->death[id]);
		printing(philo, 37, "has taken a fork");
		eating(philo);
		pthread_mutex_unlock(&philo->input->death[id]);
		pthread_mutex_unlock(&philo->input->fork[id]);
		pthread_mutex_unlock(&philo->input->fork[(id + 1) % num_of_philos]);
		sleeping_thinking(philo);
	}
	return (NULL);
}
