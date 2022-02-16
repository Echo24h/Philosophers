/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 03:22:44 by gborne            #+#    #+#             */
/*   Updated: 2022/02/16 21:47:17 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(char **argv, t_data *data)
{
	int i;

	i = 0;
	while (argv[++i])
		if (!ft_strisdigit(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (write(1, "ERROR: init.c -> init_data()\n", 30));
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&data->end, NULL);
	return (EXIT_SUCCESS);
}

void	init_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_init(&philo->forks, NULL);
	philo->data = data;
	philo->state = STATE_THINK;
}

int	init(char **argv, t_data *data)
{
	int	i;
	if(init_data(argv, data))
		return (EXIT_FAILURE);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	i = data->nb_philo;
	while (--i >= 0)
		init_philo(&data->philos[i], data);
	return (EXIT_SUCCESS);
}
