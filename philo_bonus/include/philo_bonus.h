/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:30:16 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/20 13:12:21 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <stdio.h>
# include <time.h>
# include <errno.h>

typedef struct s_node
{
	unsigned int		id;
	struct s_node		*next;
	struct s_philo_data	*philo_data;
}	t_node;

typedef struct s_philo_data
{
	unsigned int	id;
	struct timeval	last_meal;
	unsigned int	n_meals;
	struct s_params	*params;
	pid_t				pid;
}	t_philo_data;

typedef struct s_params
{
	unsigned int	n_philo;
	unsigned int	t_die;
	unsigned int	t_sleep;
	unsigned int	t_eat;
	unsigned int	n_meals;
	struct timeval	t_start;
	sem_t			*forks;
	sem_t			*pickup;
	sem_t			*print;
}	t_params;

//parse & init

t_params	*init_params(int argc, char *argv[]);

t_node	*create_circle(t_params *params);

t_philo_data	*build_philosopher(unsigned int id, t_params *params);

size_t	ft_strlen(char *string);

int	init_philo_process(t_philo_data *data);

//philo behaviour

void philo_behaviour(t_philo_data *data);

void	real_sleep(int m_sec);

void	print_update(t_philo_data *data, char print_type);

//cleanup

void	wait_and_free(t_node **philos);

void	clean_params(t_params **params);

void	clean_philo_data(t_philo_data *data);

void	cleanse_list(t_node **list);


//utils

int	time_diff(struct timeval *start, struct timeval *end);

unsigned int	atou(char *string);

#endif