/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:03:21 by iobba             #+#    #+#             */
/*   Updated: 2023/01/31 17:44:24 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher *philo)
{
	t_needs	*needs;

	needs = philo->needs;
	pthread_mutex_lock(&(needs->forks[philo->r_fork_indx]));
	printing(needs, "has taken a fork", philo->n, 1);
	pthread_mutex_lock(&(needs->forks[philo->l_fork_indx]));
	printing(needs, "has taken a fork", philo->n, 1);
	printing(needs, "is eating", philo->n, 1);
	pthread_mutex_lock(needs->meals_mnger);
	philo->last_meal = get_time();
	pthread_mutex_unlock(needs->meals_mnger);
	ft_usleep(needs->t_eat);
	pthread_mutex_lock(philo->check_meals);
	philo->n_mls++;
	pthread_mutex_unlock(philo->check_meals);
	pthread_mutex_unlock(&(needs->forks[philo->r_fork_indx]));
	pthread_mutex_unlock(&(needs->forks[philo->l_fork_indx]));
}

void	sleeping(t_philosopher *philo)
{
	t_needs	*needs;

	needs = philo->needs;
	printing(needs, "is sleeping", philo->n, 1);
	ft_usleep(needs->t_sleep);
}

void	*cycle(void *phi)
{
	t_philosopher	*philo;
	t_needs			*needs;

	philo = (t_philosopher *) phi;
	needs = philo->needs;
	if (philo->n % 2 == 0 && needs->n_philos > 1)
		usleep(200);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		printing(needs, "is thinking", philo->n, 1);
	}
	return (NULL);
}

void	clear_all(t_needs *needs)
{
	int	i;

	i = 0;
	while (i < needs->n_philos)
	{
		pthread_detach(needs->ths[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_needs	*needs;
	int		i;

	needs = malloc(sizeof(t_needs));
	if (!needs)
		return (erorrrr("failed to allocate"), 1);
	if (init_all(needs, ac, av))
		return (2);
	needs->start_time = get_time();
	i = 0;
	while (i < needs->n_philos)
	{
		if (pthread_create(&(needs->ths[i]), NULL, &cycle, &(needs->philos[i])))
		{
			free_all(needs, 5);
			erorrrr("failed to create pthreads");
			return (3);
		}	
		i++;
	}
	check_death(needs);
	clear_all(needs);
	return (0);
}
