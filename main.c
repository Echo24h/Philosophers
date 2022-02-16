/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 23:23:16 by gborne            #+#    #+#             */
/*   Updated: 2022/02/16 03:04:50 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	routine(void *p_philo)
{
	t_philo *philo;

	philo = (t_philo*)p_philo;
	pthread_mutex_lock(&philo->mutex);
	printf("test from threads\n");
	usleep(1000000);
	printf("End\n");
	pthread_mutex_unlock(&philo->mutex);
	return NULL;
}

void	start_thread(t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		pthread_create(&data->philos[i].thread, NULL, &routine, (void*)&data->philos[i]);
		pthread_join(data->philos[i].thread, NULL);
	}
}

void	clear_data(t_data *data)
{
	while (data->nb_philo--)
		pthread_mutex_destroy(&data->philos->mutex);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 6 || init(argv, &data))
		return (write(1, "ERROR: Mauvais arguments.\n", 27));
	start_thread(&data);
	clear_data(&data);
	return EXIT_SUCCESS;
}
