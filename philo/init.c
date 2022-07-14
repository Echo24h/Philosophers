/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 03:22:44 by gborne            #+#    #+#             */
/*   Updated: 2022/07/14 12:16:08 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_data(int argc, char **argv, t_data *data, unsigned long long starttime)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!ft_strisdigit(argv[i]) || ft_atoi(argv[i]) <= 0)
			ft_error("Error\nWrong arguments\n");
	data->nb_philo = ft_atoi(argv[1]);
	data->philos_end = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	data->starttime = starttime;
	pthread_mutex_init(&data->write, NULL);
	return (EXIT_SUCCESS);
}

static void	init_philo(t_philo *philo, t_data *data, int id)
{
	pthread_mutex_init(&philo->forks, NULL);
	philo->nb_eat = 0;
	philo->data = data;
	philo->state = STATE_THINK;
	philo->id = id;
	philo->time = gettime();
}

int	init(int argc, char **argv, t_data *data, unsigned long long starttime)
{
	int	i;

	if (init_data(argc, argv, data, starttime))
		return (EXIT_FAILURE);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	i = -1;
	while (++i < data->nb_philo)
		init_philo(&data->philos[i], data, i);
	return (EXIT_SUCCESS);
}
