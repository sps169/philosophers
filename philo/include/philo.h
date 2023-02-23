/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:50:45 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/23 13:25:15 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>

typedef struct	s_node
{
	unsigned int	id;
	struct s_node	*prev;
	struct s_node	*next;
	pthread_mutex_t	fork;
} t_node;

typedef struct	s_params
{
	unsigned int	n_philo;
	unsigned int	t_die;
	unsigned int	t_sleep;
	unsigned int	t_eat;
	unsigned int	n_meals;
	struct timeval	t_start;
	unsigned int	death;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	int				kick_off;
} t_params;

typedef struct s_philo_data
{
	unsigned int	id;
	struct timeval	last_meal;
	int				is_block;
	struct timeval	time_block;
	int				time_left;
	pthread_t		thread;
	struct s_node	*forks;
	struct s_params	*params;
} t_philo_data;


t_node	*create_fork_circle(int n_philo);

void	*philo_behaviour(void *philo_data);

void	die(t_philo_data *data, int result);

int	check_death(t_params *params);

int		time_diff(struct timeval *start, struct timeval *end);

void	free_philos(t_philo_data **philos, int last_philo);

void	wait_and_free(t_node **forks, t_philo_data **philos, int last_philo);

void	clean_params(t_params **params);

void	cleanse_list(t_node **list);

void	print_list(t_node *list);
#endif
