/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 09:19:06 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/18 10:12:58 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				sim;
	long			start_time;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_sim;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				n_meal;
	long			last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

// cleanup
void		cleanup(t_data *data);

// init
int			init_data(t_data *data);
int			ft_malloc(t_data *data);
int			init_mutex_forks_print(t_data *data);
void		init_philo(t_data *data);
int			init_threads(t_data *data);

// main
void		usage(void);

// monitoring
void		*monitoring(void *arg);
int			end_of_meal(t_data *data);

// parsing
t_data		parsing(t_data data, char **argv);
int			megatoi(char *str);
int			wrong_input(t_data data);
int			ft_isdigit_str(char *str);
long		ft_atol(const char *str);

// routine
void		*routine(void *arg);

// utils
int			ft_strlen(char *str);
long long	get_timestamp(void);
long		get_elapsed_time(t_data *data);
void		ft_print(t_philo *philo, char *str);
void		ft_sleep(long ms);

#endif
