/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 23:23:16 by gborne            #+#    #+#             */
/*   Updated: 2022/05/04 14:13:48 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		if (pthread_create(&data->philos[i].thread, NULL, &routine, (void*)&data->philos[i]) != 0 )
			ft_error("Can't create thread.\n");
}

int	monitoring(t_data *data)
{
	int					i;
	unsigned long long	time;

	i		= -1;
	time	= gettime();
	while (++i < data->nb_philo)
	{
		if (data->philos->time + data->time_die < time)
		{
			msg(data, i, "died", time);
			return (0);
		}
	}
	if (data->philos_end >= data->nb_philo)
		return (0);
	return (1);
}

static int	end(t_data *data)
{
	while (data->nb_philo--)
		pthread_mutex_destroy(&data->philos->forks);
	free(data->philos);
	pthread_mutex_lock(&data->write);
	//write(1, "End\n", 5);
	pthread_mutex_unlock(&data->write);
	pthread_mutex_destroy(&data->write);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data				data;

	if (argc != 6 || init(argv, &data))
		return (write(1, "Error\nWrong arguments\n", 23));
	start_thread(&data);
	while (monitoring(&data) == 1)
		;
	return (end(&data));
}
