/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:07 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/19 16:41:55 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has_taken_a_fork");
	if (philo->data->n_philo == 1)
	{
		ft_sleep(philo->data->t_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has_taken_a_fork");
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_print(philo, "is_eating");
	pthread_mutex_lock(&data->m_sim);
	philo->last_meal = get_timestamp();
	philo->n_meal++;
	pthread_mutex_unlock(&data->m_sim);
	ft_sleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_print(philo, "is_sleeping");
	ft_sleep(philo->data->t_sleep);
	ft_print(philo, "is_thinking");
	
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->m_sim);
		if (philo->data->sim == 0)
		{
			pthread_mutex_unlock(&philo->data->m_sim);
			break ;
		}
		pthread_mutex_unlock(&philo->data->m_sim);
		take_fork(philo);
		eat(philo);
	}
	ft_print(philo, "is_thinking");
	return (NULL);
}
