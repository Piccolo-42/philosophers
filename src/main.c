/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 09:16:08 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/19 14:12:50 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 7 | grep eat | awk {'print $2}' | sort | uniq -c | awk '{print $1}' | sort | uniq -c
int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (argc != 5 && argc != 6)
		return (usage(), 1);
	data = parsing(data, argv);
	if (wrong_input(data))
		return (usage(), 1);
	if (!init_data(&data))
		return (1);
	if (!init_threads(&data))
		return (1);
	usleep(1000);
	if (pthread_create(&monitor, NULL, monitoring, &data))
		return (1);
	pthread_join(monitor, NULL);
	pthread_mutex_lock(&data.m_sim);
	data.sim = 0;
	pthread_mutex_unlock(&data.m_sim);
	i = 0;
	while (i < data.n_philo)
		pthread_join(data.philo[i++].thread_id, NULL);
	cleanup(&data);
	return (0);
}

void	usage(void)
{
	printf("Wrong Input\n");
	printf("Usage: ./philo <n_philo> <t_die> ");
	printf("<t_eat> <t_sleep> <n_eat (optional)>\n");
}
