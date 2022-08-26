/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaterno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:07:11 by jpaterno          #+#    #+#             */
/*   Updated: 2022/08/19 22:07:12 by jpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo, useconds_t s)
{
	if (pthread_mutex_lock(&philo->mutex_struct) != 0)
		return (1);
	philo->life_time_lasteat = get_time();
	philo->actual_time = philo->life_time_lasteat;
	printf("%u %d has taken a fork\n%u %d has taken a fork\n%u %d is eating\n",
		philo->actual_time - philo->started_time, philo->id,
		philo->actual_time - philo->started_time, philo->id,
		philo->actual_time - philo->started_time, philo->id);
	if (pthread_mutex_unlock(&philo->mutex_struct) != 0)
		return (1);
	ft_sleep (s);
	ft_unlock_my_forks(&philo->mutex_philo, &philo->right_philos->mutex_philo);
	return (0);
}

int	ft_sleeping(t_philo *philo, useconds_t s)
{
	if (pthread_mutex_lock(&philo->mutex_struct) != 0)
		return (1);
	printf("%u %d is sleeping\n", get_time() - philo->started_time, philo->id);
	if (pthread_mutex_unlock(&philo->mutex_struct) != 0)
		return (1);
	ft_sleep(s);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->mutex_struct) != 0)
		return (1);
	printf("%u %d is thinking\n", get_time() - philo->started_time, philo->id);
	if (pthread_mutex_unlock(&philo->mutex_struct) != 0)
		return (1);
	return (0);
}
