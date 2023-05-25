/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:20:16 by iobba             #+#    #+#             */
/*   Updated: 2023/01/31 17:50:02 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/signal.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <pthread.h>
# include <stdlib.h>
# include  <sys/time.h>

struct	s_needs;

typedef struct s_philosopher
{
	pid_t			id;
	int				n;
	int				n_mls;
	time_t			last_meal;
	struct s_needs	*needs;
	sem_t			*check;
}				t_philosopher;

typedef struct s_needs
{
	int				n_philos;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				max_mls;
	time_t			start_time;
	sem_t			*forks;
	t_philosopher	*philos;
	sem_t			*print_sem;
	sem_t			*die_sem;
}				t_needs;

void	init_all(t_needs *needs, int ac, char **av);
void	is_digit(char **av);
time_t	get_time(void);
void	ft_usleep(int exact);
void	killing(t_needs *needs);
void	*wait_children(void *nee);
void	*check_death(void *phi);
void	printing(t_needs *needs, char *str, int n, int post);
int		ft_atoi(const char *s);
void	erorrrr(char *str);

#endif
