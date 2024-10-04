/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:30:16 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/04 23:01:21 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_node
{
	unsigned int		id;
	struct s_node		*prev;
	struct s_node		*next;
	struct s_philo_data	*philo_data;
}	t_node;

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

size_t	ft_strlen(char *string);


#endif