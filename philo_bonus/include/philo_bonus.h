/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:30:16 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/06 18:12:16 by sperez-s         ###   ########.fr       */
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
# include <time.h>

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
}	t_params;

//parse & init

t_params	*init_params(int argc, char *argv[]);

t_node	*create_circle(t_params *params);


size_t	ft_strlen(char *string);

//cleanup

void	clean_params(t_params **params);


#endif