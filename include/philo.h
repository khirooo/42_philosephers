/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:52:23 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/06 02:46:14 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		id;
	int				index;
	int				meals_count;
	int				l_fork;
	int				r_fork;
	int				death_time;
	pthread_mutex_t	last_meal_mutex;
	int				last_meal;
	struct s_data	*data;
}t_philo;

typedef struct s_data
{
	time_t			start;
	int				nb_philos;
	time_t			eat_time;
	time_t			sleep_time;
	time_t			death_time;
	int				nb_meals;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	bool			state;
}	t_data;

int		init_data(t_data *data, int argc, char **argv);
void	free_philos(t_philo *philos, int n);
void	free_forks(pthread_mutex_t *forks, int n);
void	clear_data(t_data *data);
int		start_semulation(t_data *data);
time_t	get_time_in_ms(void);
void	psleep(t_data *data, time_t sleep_time);
time_t	get_time_stemp(t_data *data);
void	print_philo(t_philo *philo, int state);
int		ft_atoi(const char *str);
void	monitor(t_data *data);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	eat(t_philo	*philo);
void	dors(t_philo *philo);
void	think(t_philo *philo);
int		check_simulation(t_data *data);

#endif
