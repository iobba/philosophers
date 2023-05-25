/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:26:19 by iobba             #+#    #+#             */
/*   Updated: 2023/02/04 11:31:12 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	is_digit(char **av)
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
			}
			j++;
		}
		i++;
	}
}

void	printing(t_needs *needs, char *str, int n, int post)
{
	sem_wait(needs->print_sem);
	printf("%7ld\t%d %s\n", get_time() - needs->start_time, n, str);
	if (!post)
		sem_post(needs->die_sem);
	else
		sem_post(needs->print_sem);
}

void	*check_death(void *phi)
{
	t_philosopher	*philo;
	t_needs			*needs;
	time_t			diff;

	philo = (t_philosopher *) phi;
	needs = philo->needs;
	while (1)
	{
		sem_wait(philo->check);
		diff = get_time() - philo->last_meal;
		if (diff > needs->t_die)
		{
			printing(needs, "is died", philo->n, 0);
			exit (1);
		}
		sem_post(philo->check);
	}
	return (NULL);
}

void	*wait_children(void *nee)
{
	t_needs	*needs;
	int		i;
	int		s;

	needs = (t_needs *) nee;
	i = 0;
	while (waitpid(-1, &s, 0) != -1)
	{
		if (s == 1)
			exit(1);
	}
	exit(0);
}

void	killing(t_needs *needs)
{
	int	i;	

	i = 0;
	while (i < needs->n_philos)
	{
		kill(needs->philos[i].id, SIGKILL);
		i++;
	}
	free(needs->philos);
	free(needs);
}
