/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:54:29 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/18 10:12:05 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&data->m_forks[i++]);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_sim);
	free(data->m_forks);
	free(data->philo);
}
