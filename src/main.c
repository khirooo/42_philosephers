/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:57:01 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/06 02:44:16 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_full(t_data *data)
{
	int	i;

	if (data->nb_meals == -1)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		if (data->philos[i].meals_count != data->nb_meals)
		{
			pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		i++;
	}
	return (1);
}

void	monitor(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(&data->philos[i].last_meal_mutex);
			if ((get_time_stemp(data) \
				- data->philos[i].last_meal > data->death_time)
				|| all_full(data))
			{
				pthread_mutex_lock(&data->state_mutex);
				data->state = false;
				pthread_mutex_unlock(&data->state_mutex);
				if (!all_full(data))
					print_philo(data->philos + i, 5);
				pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
				return ;
			}
			pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
			i++;
		}
		usleep(100);
	}
}

void	free_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->state_mutex);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.forks = NULL;
	if (argc != 5 && argc != 6)
	{
		write(2, "Error: provide valid arguments\n", 32);
		return (1);
	}
	if (init_data(&data, argc, argv))
	{
		clear_data(&data);
		return (1);
	}
	if (!start_semulation(&data))
		return (1);
	clear_data(&data);
	return (0);
}
