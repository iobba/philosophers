/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:19:58 by iobba             #+#    #+#             */
/*   Updated: 2023/01/31 17:56:46 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philosopher *philo)
{
	t_needs	*needs;

	needs = philo->needs;
	sem_wait(needs->forks);
	printing(needs, "has taken a fork", philo->n, 1);
	sem_wait(needs->forks);
	printing(needs, "has taken a fork", philo->n, 1);
	printing(needs, "is eating", philo->n, 1);
	sem_wait(philo->check);
	philo->last_meal = get_time();
	sem_post(philo->check);
	ft_usleep(needs->t_eat);
	philo->n_mls++;
	sem_post(needs->forks);
	sem_post(needs->forks);
}

void	sleeping(t_philosopher *philo)
{
	t_needs	*needs;

	needs = philo->needs;
	printing(needs, "is sleeping", philo->n, 1);
	ft_usleep(needs->t_sleep);
}

void	cycle(t_philosopher *philo)
{
	t_needs			*needs;
	pthread_t		th;

	needs = philo->needs;
	sem_unlink("/check");
	philo->check = sem_open("/check", O_CREAT, 0644, 1);
	if (philo->check <= 0)
		erorrrr("failed to open semaphores");
	if (pthread_create(&th, NULL, &check_death, philo))
		erorrrr("failed to create thread");
	if (pthread_detach(th))
		erorrrr("failed to detach threads");
	if (philo->n % 2 == 0 && needs->n_philos > 1)
		usleep(200);
	while (1)
	{
		eating(philo);
		if (philo->n_mls == needs->max_mls)
			exit(0);
		sleeping(philo);
		printing(needs, "is thinking", philo->n, 1);
	}
}

void	create_philos(t_needs *needs)
{
	int	i;

	i = 0;
	while (i < needs->n_philos)
	{
		needs->philos[i].id = fork();
		needs->start_time = get_time();
		if (needs->philos[i].id == -1)
			erorrrr("failed to create childs (fork).");
		if (!needs->philos[i].id)
			cycle(&(needs->philos[i]));
		i++;
	}
}

int	main(int ac, char **av)
{
	t_needs		*needs;
	pthread_t	th_wait;

	needs = malloc(sizeof(t_needs));
	if (!needs)
		erorrrr("failed to allocate");
	init_all(needs, ac, av);
	create_philos(needs);
	if (pthread_create(&th_wait, NULL, &wait_children, &needs))
		erorrrr("failed to create thread");
	if (pthread_detach(th_wait))
		erorrrr("failed to detach threads");
	sem_wait(needs->die_sem);
	killing(needs);
	return (0);
}
