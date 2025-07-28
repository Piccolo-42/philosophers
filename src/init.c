/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:52:42 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/19 10:01:50 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	if (!ft_malloc(data))
		return (0);
	if (!init_mutex_forks_print(data))
		return (0);
	init_philo(data);
	data->sim = 1;
	return (1);
}

int	ft_malloc(t_data *data)
{
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->m_forks)
		return (0);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (free(data->m_forks), 0);
	return (1);
}

int	init_mutex_forks_print(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->m_print, NULL))
		return (0);
	if (pthread_mutex_init(&data->m_sim, NULL))
		return (0);
	return (1);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].n_meal = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].left_fork = &data->m_forks[i];
		data->philo[i].right_fork = &data->m_forks[(i + 1) % data->n_philo];
		data->philo[i].data = data;
		i++;
	}
}

int	init_threads(t_data *data)
{
	int			i;
	long long	start;

	start = get_timestamp();
	data->start_time = start;
	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].last_meal = start;
		if (pthread_create(&data->philo[i].thread_id, NULL, 
				routine, &data->philo[i]))
			return (0);
		i++;
	}
	return (1);
}
