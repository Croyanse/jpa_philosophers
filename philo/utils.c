/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaterno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:24:08 by jpaterno          #+#    #+#             */
/*   Updated: 2022/08/08 01:24:09 by jpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoiq(char *str)
{
	int	i;
	int	nbr;

	if (!str || str[0] == '\0')
		return (-1);
	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		nbr *= 10;
		nbr += str[i] - 48;
		i++;
	}
	return (nbr);
}

useconds_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_lock_my_forks(pthread_mutex_t *left, pthread_mutex_t *right)
{
	if (pthread_mutex_lock(left) != 0)
		return (2);
	if (pthread_mutex_lock(right) != 0)
		return (2);
	return (1);
}

int	ft_unlock_my_forks(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
	return (1);
}

void	ft_sleep(useconds_t ttw)
{
	useconds_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < ttw)
		usleep(300);
}
