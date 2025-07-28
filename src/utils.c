/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 09:39:53 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/19 14:17:13 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

long	get_elapsed_time(t_data *data)
{
	return (get_timestamp() - data->start_time);
}

void	ft_print(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->data->m_sim);
	pthread_mutex_lock(&philo->data->m_print);
	time = get_elapsed_time(philo->data);
	if (philo->data->sim == 1)
		printf("%ld %d %s\n", time, philo->id, str);
	else if (!str)
		printf("%ld %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->m_sim);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	ft_sleep(long ms)
{
	long	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < ms)
		usleep(500);
}
