/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:52:11 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/06 02:40:16 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_philo(t_philo *philo, int state)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	if (state == 1)
		printf("%ld %d has taken a fork\n", get_time_stemp(data), \
			philo->index + 1);
	else if (state == 2)
		printf("%ld %d is eating\n", get_time_stemp(data), philo->index + 1);
	else if (state == 3)
		printf("%ld %d is sleeping\n", get_time_stemp(data), philo->index + 1);
	else if (state == 4)
		printf("%ld %d is thinking\n", get_time_stemp(data), philo->index + 1);
	else if (state == 5)
		printf("%ld %d died\n", get_time_stemp(data), philo->index + 1);
	pthread_mutex_unlock(&data->print_mutex);
}

int	check_simulation(t_data *data)
{
	pthread_mutex_lock(&data->state_mutex);
	if (data->state)
	{
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

void	*one_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->l_fork]);
	print_philo(philo, 1);
	psleep(data, data->death_time);
	pthread_mutex_unlock(&data->forks[philo->r_fork]);
	return (NULL);
}

void	*philo_routine(void	*param)
{
	t_philo		*philo;
	t_data		*data;

	philo = param;
	data = philo->data;
	if (!data->death_time || !data->nb_meals)
		return (NULL);
	if (data->nb_philos == 1)
		return (one_philo(philo));
	if (philo->index % 2)
		think(philo);
	while (check_simulation(data))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		dors(philo);
		think(philo);
	}
	return (NULL);
}

int	start_semulation(t_data *data)
{
	int			i;

	i = 0;
	data->start = get_time_in_ms();
	while (i < data->nb_philos)
	{
		data->philos[i].index = i;
		data->philos[i].data = data;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->nb_philos;
		data->philos[i].meals_count = 0;
		if (pthread_create(&data->philos[i].id, NULL, &philo_routine, \
			(void *)&data->philos[i]))
		{
			write(2, "Error fatal: pthread_create fail\n", 34);
			return (0);
		}
		i++;
	}
	monitor(data);
	i = 0;
	while (i < data->nb_philos && !pthread_join(data->philos[i].id, NULL))
		i++;
	return (1);
}
