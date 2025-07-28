/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:52 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/19 14:15:38 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->m_sim);
			if (get_timestamp() - data->philo[i].last_meal > data->t_die)
			{
				data->sim = 0;
				pthread_mutex_unlock(&data->m_sim);
				ft_print(&data->philo[i], NULL);
				return (NULL);
			}
			pthread_mutex_unlock(&data->m_sim);
			i++;
		}
		if (data->n_eat != -2 && end_of_meal(data))
			return (NULL);
		usleep(1000);
	}
}


int	end_of_meal(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->m_sim);
		if (data->philo[i].n_meal < data->n_eat)
		{
			pthread_mutex_unlock(&data->m_sim);
			return (0);
		}
		pthread_mutex_unlock(&data->m_sim);
		i++;
	}
	pthread_mutex_lock(&data->m_sim);
	data->sim = 0;
	pthread_mutex_unlock(&data->m_sim);
	return (1);
}
