/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:01:18 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/14 12:49:31 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static _Bool	*make_philos_ate_max(int num_of_philos)
{
	int		i;
	_Bool	*philos_eaten_max;

	i = 0;
	philos_eaten_max = malloc(num_of_philos * sizeof(_Bool));
	if (!philos_eaten_max)
		return (NULL);
	while (i < num_of_philos)
		philos_eaten_max[i++] = 0;
	return (philos_eaten_max);
}

static void	fill_philos_ate_max(t_philo *philos, _Bool *philos_eaten_max, int i)
{
	if ((*philos).input->must_eat >= 0)
	{
		pthread_mutex_lock((*philos).input->eating_manipulation);
		if (philos[i].eating_times == (*philos).input->must_eat)
			philos_eaten_max[i] = 1;
		pthread_mutex_unlock((*philos).input->eating_manipulation);
	}
}

static _Bool	check_philos_ate_max(_Bool *philo_eaten_max, int num_of_philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < num_of_philo)
	{
		if (philo_eaten_max[i] == 1)
			count++;
		i++;
	}
	if (count == num_of_philo)
	{
		free(philo_eaten_max);
		return (1);
	}
	return (0);
}

static _Bool	must_die(t_philo *philos, int i)
{
	long	diff;

	pthread_mutex_lock((*philos).input->eating_manipulation);
	diff = time_difference(philos[i].input->start);
	if (!philos[i].is_eating
		&& time_difference(philos[i].start_eating) > (*philos).input->t_die)
	{
		pthread_mutex_lock(&philos[i].input->death[i]);
		pthread_mutex_lock(philos[i].input->display);
		printf("\033[0;31m%.4ld	%d died\n", diff, i + 1);
		return (1);
	}
	pthread_mutex_unlock((*philos).input->eating_manipulation);
	return (0);
}

_Bool	supervisor(t_philo *philos)
{
	int		i;
	int		num_of_philos;
	_Bool	*philos_eaten_max;

	num_of_philos = (*philos).input->num_of_philos;
	philos_eaten_max = make_philos_ate_max(num_of_philos);
	if (!philos_eaten_max)
		return (1);
	while (1)
	{
		i = 0;
		while (i < num_of_philos)
		{
			if (must_die(philos, i))
				return (1);
			fill_philos_ate_max(philos, philos_eaten_max, i);
			i++;
		}
		if (check_philos_ate_max(philos_eaten_max, num_of_philos))
			return (1);
		usleep(500);
	}
	return (0);
}
