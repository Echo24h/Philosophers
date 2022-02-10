/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 23:23:16 by gborne            #+#    #+#             */
/*   Updated: 2022/02/10 04:02:41 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	routine()
{
	printf("test from threads\n");
	sleep(3);
	printf("End\n");
	return NULL;
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 6 || init(argv, &data))
		return (write(1, "ERROR: Mauvais arguments.\n", 27));
	pthread_create(&data.philos[0].thread, NULL, &routine, NULL);
	sleep(1);
	pthread_create(&data.philos[1].thread, NULL, &routine, NULL);
	pthread_join(data.philos[0].thread, NULL);
	free(data.philos);
	return EXIT_SUCCESS;
}
