/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaterno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:34:43 by jpaterno          #+#    #+#             */
/*   Updated: 2022/08/09 17:34:44 by jpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_main_thread(void *in)
{
	t_philo		*bag;
	useconds_t	mle;
	useconds_t	mls;
	int			check;

	bag = in;
	pthread_mutex_lock(&bag->g_vlb->mutex_struct);
	mle = bag->g_vlb->mle;
	mls = bag->g_vlb->mls;
	pthread_mutex_unlock(&bag->g_vlb->mutex_struct);
	check = 0;
	if (bag->id % 2 == 1 && ++check == 1)
		ft_lock_my_forks(&bag->mutex_philo, &bag->right_philos->mutex_philo);
	pthread_mutex_lock(&bag->mutex_struct);
	bag->started_time = bag->start_at;
	bag->actual_time = bag->started_time;
	bag->life_time_lasteat = bag->started_time;
	pthread_mutex_unlock(&bag->mutex_struct);
	ft_sleep(bag->start_at - get_time());
	return (ft_dinner_time(bag, mle, mls, check));
}

void	*ft_dinner_time(t_philo *bag, useconds_t mle, useconds_t mls, int check)
{
	int	id;

	id = bag->id;
	while (1)
	{
		if (id % 2 == 0 || id == 0)
			usleep(bag->latence);
		if (check == 0)
			ft_lock_my_forks(&bag->mutex_philo,
				&bag->right_philos->mutex_philo);
		check = 0;
		if (ft_eat(bag, mle) == 1)
			return (NULL);
		if (--bag->nbr_takeforks == 0)
		{
			bag->nbr_takeforks = -555;
			usleep(1000000);
		}
		if (ft_sleeping(bag, mls) == 1)
			return (NULL);
		if (ft_think(bag) == 1)
			return (NULL);
	}
	return (NULL);
}
