/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:10:16 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/14 12:12:48 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static _Bool	check_and_fill_data(int argc, char **argv, t_input *data)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->fork = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	data->death = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	data->display = malloc(sizeof(pthread_mutex_t));
	data->eating_manipulation = malloc(sizeof(pthread_mutex_t));
	if (data->num_of_philos <= 0 || data->t_die <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0 || data->must_eat < -1
		|| !data->fork || !data->death || !data->display)
		return (1);
	init_mutexes(data);
	return (0);
}

static t_philo	*make_philos(t_input *data)
{
	t_philo	*temp;
	int		i;

	temp = malloc(data->num_of_philos * sizeof(t_philo));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		temp[i].id = i;
		temp[i].input = data;
		temp[i].start_eating = time_difference(0);
		temp[i].eating_times = 0;
		i++;
	}
	return (temp);
}

static _Bool	run_threads(t_philo *philos)
{
	(*philos).input->start = time_difference(0);
	if ((*philos).input->must_eat == 0)
		return (1);
	if (start_evens(philos))
		return (1);
	usleep(100);
	if (start_odds(philos))
		return (1);
	if (supervisor(philos))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	*philos;
	t_input	*data;

	data = malloc(sizeof(t_input));
	if ((argc < 5 || argc > 6) || check_and_fill_data(argc, argv, data))
	{
		printf("%s\n", "\033[1;31mError: \033[0mwrong input");
		return (1);
	}
	philos = make_philos(data);
	if (!philos || run_threads(philos))
		return (1);
	free_resources(philos, data);
	return (0);
}
