/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 03:13:28 by gborne            #+#    #+#             */
/*   Updated: 2022/07/08 17:33:00 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strisdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

void	ft_putnbr(unsigned long long n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 43 || *str == 45 || ft_isdigit(*str))
	{
		if (*str == 45)
			sign = -1;
		if (ft_isdigit(*str))
			result = result * 10 + (*str - 48);
		while (ft_isdigit(*++str))
			result = result * 10 + (*str - 48);
	}
	return (result * sign);
}

unsigned long long	gettime(void)
{
	struct timeval		time;
	unsigned long long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

static unsigned long	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	msg(t_data *data, int id, char *text, unsigned long long time)
{
	pthread_mutex_lock(&data->write);
	ft_putnbr(time / 1000);
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
