/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:40:45 by gborne            #+#    #+#             */
/*   Updated: 2022/07/14 12:42:25 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_usleep(size_t wait_time)
{
	struct timeval	tv;
	long			end;

	gettimeofday(&tv, NULL);
	end = (tv.tv_sec * 1000 + tv.tv_usec / 1000) + wait_time;
	while (tv.tv_sec * 1000 + tv.tv_usec / 1000 <= end)
	{
		gettimeofday(&tv, NULL);
		usleep(777);
	}
}

void	msg(t_data *data, int id, char *text, unsigned long long time)
{
	pthread_mutex_lock(&data->write);
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(id + 1);
	write(1, " ", 1);
	write(1, text, ft_strlen(text));
	write(1, "\n", 1);
	pthread_mutex_unlock(&data->write);
}

void	ft_error(char *error_msg)
{
	int	len;

	len = 0;
	while (error_msg[len++])
		;
	write(1, error_msg, len);
	exit(0);
}
