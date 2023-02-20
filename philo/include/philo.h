/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:50:45 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/20 12:54:05 by sperez-s         ###   ########.fr       */
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
} t_params;

typedef struct s_philo_data
{
	unsigned int	id;
	struct timeval	last_meal;
	pthread_t		thread;
	struct s_node	*forks;
	struct s_params	params;
} t_philo_data;


t_node	*create_fork_circle(int n_philo);

void	*philo_behaviour(void *philo_data);

int		time_diff(struct timeval *start, struct timeval *end);

void	cleanse_list(t_node **list);

void	print_list(t_node *list);
#endif
