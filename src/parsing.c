/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:03:59 by sravizza          #+#    #+#             */
/*   Updated: 2025/04/18 09:24:52 by sravizza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
