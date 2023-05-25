/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:32:22 by iobba             #+#    #+#             */
/*   Updated: 2023/02/02 13:08:06 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		erorrrr("invalid number of arguments");
		return (1);
	}
	if (is_digit(av))
		return (1);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0
		|| ft_atoi(av[4]) < 0)
	{
		erorrrr("invalid arguments");
		return (1);
	}
	if (av[5] && ft_atoi(av[5]) < 0)
	{
		erorrrr("invalid arguments");
		return (1);
	}
	return (0);
}

int	free_all(t_needs *needs, int i)
{
	if (i == 1)
		free(needs->ths);
	else if (i == 2)
	{
		free(needs->ths);
		free(needs->print_mutex);
	}
	else if (i == 3)
	{
		free_all(needs, 2);
		free(needs->meals_mnger);
	}
	else if (i == 4)
	{
		free(needs->forks);
		return (free_all(needs, 3));
	}
	else if (i == 5)
	{
		free(needs->philos);
		free_all(needs, 4);
		free(needs);
	}
	return (1);
}

int	init_philos(t_needs *needs)
{
	int	i;

	i = 0;
	while (i < needs->n_philos)
	{
		needs->philos[i].check_meals = malloc(sizeof(pthread_mutex_t));
		if (!needs->philos[i].check_meals)
			return (erorrrr("failed allocation"), free_all(needs, 5));
		needs->philos[i].n = i + 1;
		needs->philos[i].r_fork_indx = i;
		if (i == needs->n_philos - 1)
			needs->philos[i].l_fork_indx = 0;
		else
			needs->philos[i].l_fork_indx = i + 1;
		needs->philos[i].n_mls = 0;
		needs->philos[i].last_meal = 0;
		needs->philos[i].needs = needs;
		if (pthread_mutex_init(needs->philos[i].check_meals, NULL))
			return (erorrrr("failed to init mutexes"), free_all(needs, 4));
		i++;
	}
	return (0);
}

int	init_mutex(t_needs *needs)
{
	int	i;

	needs->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!needs->print_mutex)
		return (erorrrr("failed allocation"), free_all(needs, 1));
	needs->meals_mnger = malloc(sizeof(pthread_mutex_t));
	if (!needs->meals_mnger)
		return (erorrrr("failed allocation"), free_all(needs, 2));
	needs->forks = malloc(needs->n_philos * sizeof(pthread_mutex_t));
	if (!needs->forks)
		return (erorrrr("failed allocation"), free_all(needs, 3));
	i = 0;
	while (i < needs->n_philos)
	{
		if (pthread_mutex_init(&(needs->forks[i]), NULL))
			return (erorrrr("failed to init mutexes"), free_all(needs, 4));
		i++;
	}
	if (pthread_mutex_init(needs->print_mutex, NULL)
		|| pthread_mutex_init(needs->meals_mnger, NULL))
		return (erorrrr("failed to init mutexes"), free_all(needs, 4));
	return (0);
}

int	init_all(t_needs *needs, int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
	needs->n_philos = ft_atoi(av[1]);
	needs->t_die = ft_atoi(av[2]);
	needs->t_eat = ft_atoi(av[3]);
	needs->t_sleep = ft_atoi(av[4]);
	if (av[5])
		needs->max_mls = ft_atoi(av[5]);
	else
		needs->max_mls = -1;
	needs->ths = malloc(needs->n_philos * sizeof(pthread_t));
	if (!needs->ths)
		return (erorrrr("failed allocation"), 1);
	if (init_mutex(needs))
		return (1);
	needs->philos = malloc(needs->n_philos * sizeof(t_philosopher));
	if (!needs->philos)
		return (erorrrr("failed allocation"), free_all(needs, 4));
	if (init_philos(needs))
		return (1);
	return (0);
}
