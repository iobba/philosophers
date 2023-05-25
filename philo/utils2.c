/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:49:22 by iobba             #+#    #+#             */
/*   Updated: 2023/02/02 18:44:24 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				erorrrr("arguments shoud be digits");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	printing(t_needs *needs, char *str, int n, int unlock)
{
	pthread_mutex_lock(needs->print_mutex);
	printf("%7ld ms\t%d %s\n", get_time() - needs->start_time, n, str);
	if (unlock)
		pthread_mutex_unlock(needs->print_mutex);
}

int	count_meals(t_needs *needs)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < needs->n_philos)
	{
		pthread_mutex_lock(needs->philos[i].check_meals);
		if (needs->philos[i].n_mls >= needs->max_mls)
			k++;
		pthread_mutex_unlock(needs->philos[i].check_meals);
		i++;
	}
	if (k == needs->n_philos)
	{
		return (1);
	}
	return (0);
}

void	check_death(t_needs *needs)
{
	int		i;
	time_t	diff;

	while (1)
	{
		i = 0;
		while (i < needs->n_philos)
		{
			pthread_mutex_lock(needs->meals_mnger);
			if (!needs->philos[i].last_meal)
				needs->philos[i].last_meal = needs->start_time;
			diff = get_time() - needs->philos[i].last_meal;
			if (diff > needs->t_die)
			{
				printing(needs, "died", needs->philos[i].n, 0);
				return ;
			}
			if (needs->max_mls != -1 && count_meals(needs))
				return ;
			pthread_mutex_unlock(needs->meals_mnger);
			i++;
		}
	}
}
