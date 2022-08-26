/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaterno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:25:13 by jpaterno          #+#    #+#             */
/*   Updated: 2022/08/08 01:26:06 by jpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <errno.h>

typedef struct f_data
{
	pthread_mutex_t	mutex_struct;
	pthread_t		god;
	int				count;
	useconds_t		start_at;
	int				nb_philos;
	useconds_t		mld;
	useconds_t		mle;
	useconds_t		mls;
	int				*check_ready;
	int				nbr_takeforks;
	useconds_t		start;
	void			*tab_philos;

}				t_data;

typedef struct f_philo
{
	pthread_mutex_t	mutex_struct;
	int				id;
	pthread_t		philo;
	struct f_philo	*right_philos;
	t_data			*g_vlb;
	pthread_mutex_t	mutex_philo;
	useconds_t		life_time_lasteat;
	useconds_t		actual_time;
	useconds_t		started_time;
	useconds_t		start_at;
	int				isitend;
	useconds_t		latence;
	int				nbr_takeforks;

}				t_philo;
int			ft_free(t_philo *philos, int nbphilo);
int			ft_atoiq(char *str);
useconds_t	get_time(void);
void		*ft_main_thread(void *bag);
int			ft_unlock_my_forks(pthread_mutex_t *left, pthread_mutex_t *right);
int			ft_lock_my_forks(pthread_mutex_t *left, pthread_mutex_t *right);
void		*ft_god_is_watching(void *earth);
void		ft_philos_factory(t_data *as);
int			ft_eat(t_philo *philo, useconds_t s);
int			ft_sleeping(t_philo *philo, useconds_t s);
int			ft_think(t_philo *philo);
void		ft_sleep(useconds_t ttw);
void		*ft_le_dessert(t_data *as, t_philo *philos, int i, useconds_t time);
void		*ft_dinner_time(t_philo *bag, useconds_t mle, useconds_t mls,
				int check);
int			ft_checkin(int argc, char **argv, t_data *as);

#endif
