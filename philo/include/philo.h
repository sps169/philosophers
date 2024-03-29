/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:50:45 by sperez-s          #+#    #+#             */
/*   Updated: 2023/09/19 16:00:34 by sperez-s         ###   ########.fr       */
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

typedef struct s_node
{
	unsigned int		id;
	struct s_node		*prev;
	struct s_node		*next;
	struct s_philo_data	*philo_data;
}	t_node;

typedef struct s_params
{
	unsigned int			n_philo;
	unsigned int			t_die;
	unsigned int			t_sleep;
	unsigned int			t_eat;
	unsigned int			n_meals;
	unsigned int			death;
	unsigned int			n_satisfied;
	int						kick_off;
	struct timeval			t_start;
	pthread_mutex_t			death_lock;
	pthread_mutex_t			print_lock;
	pthread_mutex_t			meal_lock;
	pthread_mutex_t			kick_off_lock;
	pthread_mutex_t			satisfaction_lock;
	pthread_mutex_t			starve_queue_lock;
	struct s_starve_node	*starve_queue;
}	t_params;

typedef struct s_philo_data
{
	int				time_left;
	unsigned int	id;
	unsigned int	n_meals;
	struct timeval	last_meal;
	struct s_params	*params;
	struct s_node	*list;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*n_meals_mutex;
	pthread_mutex_t	*last_meal_mutex;
}	t_philo_data;

typedef struct s_starve_node
{
	unsigned int			death_ms;
	struct s_philo_data		*philo;
	struct s_starve_node	*next;
}	t_starve_node;

t_node			*create_circle(t_params *params);

t_philo_data	*create_philosopher(unsigned int id,
					t_params *params, t_node *prev);

void			*philo_behaviour(void *philo_data);

int				time_diff(struct timeval *start, struct timeval *end);

void			wait_and_free(t_node **philos);

void			clean_params(t_params **params);

void			cleanse_list(t_node **list);

int				check_starvation(t_philo_data *data);

unsigned int	atou(char *string);

void			*lone_wolf(void *data);

t_params		*init_params(int argc, char *argv[]);

void			print_update(t_philo_data *data, char print_type);

void			print_death(t_philo_data *data);

void			update_meal_time(t_philo_data *philo_data);

void			real_sleep(int m_sec);

int				check_starvation(t_philo_data *data);

int				sleep_or_die(int sleep, t_philo_data *data);

void			die(t_philo_data *data);

int				wait_start(t_params *params);

void			take_forks(t_philo_data *philo_data);

int				eat(t_philo_data *philo_data);

void			clean_philo_data(t_philo_data *data);

t_starve_node	*create_starve_node(unsigned int death_ms, t_philo_data *data);

int				add_starve_node(unsigned int death_ms, t_philo_data *data);

t_starve_node	*get_next_starve_node(t_params *params);

void			erase_queue(t_params params);

#endif
