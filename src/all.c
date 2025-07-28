
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

void	usage(void)
{
	printf("Wrong Input\n");
	printf("Usage: ./philo <n_philo> <t_die> ");
	printf("<t_eat> <t_sleep> <n_eat (optional)>\n");
}

t_data	parsing(t_data data, char **argv)
{
	data.n_philo = megatoi(argv[1]);
	data.t_die = megatoi(argv[2]);
	data.t_eat = megatoi(argv[3]);
	data.t_sleep = megatoi(argv[4]);
	if (argv[5])
		data.n_eat = megatoi(argv[5]);
	else
		data.n_eat = -2;
	return (data);
}

int	megatoi(char *str)
{
	long	temp;

	if (ft_strlen(str) > 12 || !ft_isdigit_str(str))
		return (-1);
	temp = ft_atol(str);
	if (temp < -2147483648 || temp > 2147483647)
		return (-1);
	return (temp);
}

int	wrong_input(t_data data)
{
	if (data.n_philo == -1)
		return (1);
	if (data.t_die == -1)
		return (1);
	if (data.t_eat == -1)
		return (1);
	if (data.t_sleep == -1)
		return (1);
	if (data.n_eat == -1)
		return (1);
	return (0);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

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
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (ms);
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
		return (0);
	usleep(1000);
	if (pthread_create(&monitor, NULL, monitoring, &data))
		return (1);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data.n_philo)
		pthread_join(data.philo[i++].thread_id, NULL);
	cleanup(&data);
	return (0);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	if (philo->data->n_philo == 1)
	{
		ft_sleep(philo->data->t_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_print(philo, "is eating");
	pthread_mutex_lock(&data->m_sim);
	philo->last_meal = get_timestamp();
	philo->n_meal++;
	pthread_mutex_unlock(&data->m_sim);
	ft_sleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_print(philo, "is sleeping");
	ft_sleep(philo->data->t_sleep);
	ft_print(philo, "is thinking");
	
}


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
	ft_print(philo, "is thinking");
	return (NULL);
}
