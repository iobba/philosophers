/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iobba <iobba@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:03:37 by iobba             #+#    #+#             */
/*   Updated: 2023/01/31 17:16:56 by iobba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

struct	s_needs;

typedef struct s_philosopher
{
	int				r_fork_indx;
	int				l_fork_indx;
	int				n;
	int				n_mls;
	time_t			last_meal;
	pthread_mutex_t	*check_meals;
	struct s_needs	*needs;
}				t_philosopher;

typedef struct s_needs
{
	int				n_philos;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				max_mls;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_t		*ths;
	t_philosopher	*philos;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*meals_mnger;
}				t_needs;

int		init_all(t_needs *needs, int ac, char **av);
int		is_digit(char **av);
int		free_all(t_needs *needs, int i);
time_t	get_time(void);
void	ft_usleep(int exact);
void	printing(t_needs *needs, char *str, int n, int unlock);
int		count_meals(t_needs *needs);
void	clear_all(t_needs *needs);
void	check_death(t_needs *needs);
int		ft_atoi(const char *s);
void	erorrrr(char *str);

#endif
