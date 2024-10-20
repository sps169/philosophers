/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:06:08 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/20 13:21:57 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo_process(t_philo_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) 
	{
		philo_behaviour(data);
	} 
	else if (pid == -1)
		return (0);
	else
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
	return (data);
}
