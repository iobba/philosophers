/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:22:03 by iobba             #+#    #+#             */
/*   Updated: 2023/02/04 11:40:56 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		erorrrr("invalid number of arguments");
	is_digit(av);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0
		|| ft_atoi(av[4]) < 0)
		erorrrr("invalid arguments");
	if (av[5] && ft_atoi(av[5]) < 0)
		erorrrr("invalid arguments");
}

void	init_sem(t_needs *needs)
{
	sem_unlink("/forks");
	sem_unlink("/print_sem");
	sem_unlink("/die_sem");
	needs->forks = sem_open("/forks", O_CREAT, 0644, needs->n_philos);
	needs->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	needs->die_sem = sem_open("/die_sem", O_CREAT, 0644, 0);
	if (needs->forks <= 0 || needs->print_sem <= 0 || needs->die_sem <= 0)
	{
		free(needs->philos);
		erorrrr("failed to open semaphores");
	}
}

void	init_philos(t_needs *needs)
{
	int	i;

	needs->philos = malloc(needs->n_philos * sizeof(t_philosopher));
	if (!needs->philos)
		erorrrr("failed allocation philos");
	i = 0;
	while (i < needs->n_philos)
	{
		needs->philos[i].n = i + 1;
		needs->philos[i].n_mls = 0;
		needs->philos[i].last_meal = get_time();
		needs->philos[i].needs = needs;
		i++;
	}
}

void	init_all(t_needs *needs, int ac, char **av)
{
	check_args(ac, av);
	needs->n_philos = ft_atoi(av[1]);
	needs->t_die = ft_atoi(av[2]);
	needs->t_eat = ft_atoi(av[3]);
	needs->t_sleep = ft_atoi(av[4]);
	if (av[5])
		needs->max_mls = ft_atoi(av[5]);
	else
		needs->max_mls = -1;
	init_philos(needs);
	init_sem(needs);
}
