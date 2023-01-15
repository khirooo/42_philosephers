/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 01:22:01 by kfergani          #+#    #+#             */
/*   Updated: 2022/12/06 02:33:04 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int		i;
	char	*s;

	i = 1;
	while (i < argc)
	{
		s = argv[i];
		while (*s && '0' <= *s && *s <= '9')
			s++;
		if (*s != '\0' || ft_atoi(argv[i]) < 0 || ft_atoi(argv[1]) == 0)
		{
			write(2, "Error: provide valid arguments\n", 32);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	data->nb_philos = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->nb_meals = -1;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	data->philos = (t_philo *)malloc(data->nb_philos * sizeof(t_philo));
	data->forks = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	if (!data->philos || !data->philos)
	{
		write(2, "Error fatal: malloc fail\n", 26);
		return (1);
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->state_mutex, NULL);
	data->state = true;
	return (init_forks(data));
}

void	free_philos(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		i++;
	}
	free(philos);
}

void	free_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
