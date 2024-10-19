/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:04:02 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/19 15:49:15 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void philo_behaviour(t_philo_data *data)
{
	while (1)
	{
		sem_wait(data->params->pickup);
		sem_wait(data->params->forks);
		print_update(data, 'l');
		sem_wait(data->params->forks);
		print_update(data, 'r');
		sem_post(data->params->pickup);
		print_update(data, 'e');
		real_sleep(100);	//eat
		sem_post(data->params->forks);
		sem_post(data->params->forks);
		print_update(data, 's');
		real_sleep(100);	//sleep
	}
}