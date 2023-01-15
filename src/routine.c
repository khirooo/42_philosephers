/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 01:28:48 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/06 01:29:29 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (check_simulation(data))
	{
		if (philo->index % 2)
			pthread_mutex_lock(&data->forks[philo->l_fork]);
		else
			pthread_mutex_lock(&data->forks[philo->r_fork]);
		if (check_simulation(data))
			print_philo(philo, 1);
		if (check_simulation(data))
		{
			if (philo->index % 2)
				pthread_mutex_lock(&data->forks[philo->r_fork]);
			else
				pthread_mutex_lock(&data->forks[philo->l_fork]);
			if (check_simulation(data))
				print_philo(philo, 1);
		}
	}
}

void	release_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->index % 2)
	{
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
		pthread_mutex_unlock(&data->forks[philo->r_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->r_fork]);
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
	}
}

void	eat(t_philo	*philo)
{
	t_data	*data;

	data = philo->data;
	if (check_simulation(data))
	{
		if (check_simulation(philo->data))
			print_philo(philo, 2);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = get_time_stemp(philo->data);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		psleep(data, data->eat_time);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->last_meal_mutex);
	}
}

void	dors(t_philo *philo)
{
	if (check_simulation(philo->data))
	{
		print_philo(philo, 3);
		psleep(philo->data, philo->data->sleep_time);
	}
}

void	think(t_philo *philo)
{
	t_data	*data;
	time_t	time_to_think;

	data = philo->data;
	if (check_simulation(data))
	{
		pthread_mutex_lock(&philo->last_meal_mutex);
		time_to_think = (data->death_time - (get_time_stemp(data) \
			- philo->last_meal) - data->eat_time) / 2;
		pthread_mutex_unlock(&philo->last_meal_mutex);
		if (check_simulation(data))
			print_philo(philo, 4);
		psleep(data, time_to_think);
	}
}
