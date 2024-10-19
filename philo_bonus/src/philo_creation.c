/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:06:08 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/19 14:11:39 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_philo_process(t_philo_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) 
	{
		philo_behaviour(data);
	} else 
	{
		data->pid = pid;
	}
	return (1);
}

t_philo_data	*build_philosopher(unsigned int id, t_params *params)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (data == NULL)
		return (NULL);
	data->params = params;
	data->id = id;
	data->n_meals = 0;
	if (!init_philo_process(data))
	{
		clean_philo_data(data);
		return (NULL);
	}
	return (data);
}
