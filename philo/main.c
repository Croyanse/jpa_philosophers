/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaterno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:24:03 by jpaterno          #+#    #+#             */
/*   Updated: 2022/08/08 01:24:04 by jpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		i;
	t_data	as;
	t_philo	*philos;
	void	*retval;

	i = -1;
	pthread_mutex_init(&as.mutex_struct, NULL);
	as.nb_philos = ft_atoiq(argv[1]);
	as.mld = (useconds_t)ft_atoiq(argv[2]);
	as.mle = (useconds_t)ft_atoiq(argv[3]);
	as.mls = (useconds_t)ft_atoiq(argv[4]);
	if (ft_checkin(argc, argv, &as) == 1)
		return (0);
	philos = malloc(sizeof(t_philo) * as.nb_philos);
	as.tab_philos = philos;
	ft_philos_factory(&as);
	while (++i != as.nb_philos)
	{
		usleep (500);
		pthread_create(&philos[i].philo, NULL, ft_main_thread, &philos[i]);
		pthread_detach(philos[i].philo);
	}
	pthread_create(&as.god, NULL, ft_god_is_watching, &as);
	pthread_join(as.god, &retval);
	usleep(500);
}

void	ft_philos_factory(t_data *as)
{
	int			i;
	t_philo		*philos;
	useconds_t	time;

	i = -1;
	philos = (t_philo *)as->tab_philos;
	time = get_time();
	as->start_at = time + (as->nb_philos * 2);
	while (++i != as->nb_philos)
	{
		philos[i].right_philos = &philos[i + 1];
		philos[i].life_time_lasteat = 0;
		philos[i].g_vlb = as;
		philos[i].id = i;
		philos[i].latence = 100;
		philos[i].nbr_takeforks = as->nbr_takeforks;
		philos[i].isitend = -1;
		philos[i].start_at = as->start_at;
		if (i + 1 == as->nb_philos)
			philos[i].right_philos = &philos[0];
		pthread_mutex_init(&philos[i].mutex_philo, NULL);
		pthread_mutex_init(&philos[i].mutex_struct, NULL);
	}
}

void	*ft_god_is_watching(void *earth)
{
	t_data		*as;
	t_philo		*philos;
	int			i;
	int			ix;
	useconds_t	time;

	as = earth;
	philos = (t_philo *)as->tab_philos;
	while (get_time() < as->start_at)
		ft_sleep(1);
	as->start = as->start_at;
	i = 0;
	ft_sleep(50);
	while (1)
	{
		pthread_mutex_lock(&philos[i].mutex_struct);
		time = get_time();
		if ((time - philos[i].life_time_lasteat) > as->mld)
			return (ft_le_dessert(as, philos, i, time));
		pthread_mutex_unlock(&philos[i].mutex_struct);
		if (++i == as->nb_philos)
			i = usleep(10);
	}
	free(philos);
	return (NULL);
}

void	*ft_le_dessert(t_data *as, t_philo *philos, int i, useconds_t time)
{
	int	ix;

	ix = i;
	i = -1;
	while (++i != as->nb_philos)
	{
		pthread_mutex_destroy(&philos[i].mutex_struct);
		pthread_mutex_destroy(&philos[i].mutex_philo);
	}
	if (philos[ix].nbr_takeforks == -555)
		return (NULL);
	printf("%d %d is dead after %d of waiting\n", time - as->start,
		philos[ix].id, time - philos[ix].life_time_lasteat);
	return (NULL);
}

int	ft_checkin(int argc, char **argv, t_data *as)
{
	int	i;

	i = 0;
	if (argc > 6 || argc < 5)
		return (1);
	if (as->mld < 1 || as->mld > 50000)
		return (1);
	if (as->mls < 1 || as->mls > 50000)
		return (1);
	if (as->mle < 1 || as->mle > 50000)
		return (1);
	if (as->nb_philos < 1 || as->nb_philos > 500)
		return (1);
	if (argc == 6)
	{
		as->nbr_takeforks = ft_atoiq(argv[5]);
		if (as->nbr_takeforks < 1 || as->nbr_takeforks > 50000)
			return (1);
	}
	else
		as->nbr_takeforks = -1;
	return (0);
}
