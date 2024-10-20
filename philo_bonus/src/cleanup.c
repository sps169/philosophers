/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:11:20 by sperez-s          #+#    #+#             */
/*   Updated: 2024/10/20 13:47:04 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_and_free(t_node **philos)
{
	int		first_node;
	t_node	*curr_node;
	int		status;

	curr_node = *philos;
	first_node = 1;
	while (curr_node->id != 1 || first_node)
	{
		if (curr_node->id == 1 && first_node)
			first_node = 0;
		waitpid(curr_node->philo_data->pid, &status, 0);
		curr_node = curr_node->next;
	}
	cleanse_list(philos);
}

void	clean_params(t_params **params)
{
	if (*params != NULL)
	{
		sem_close((*params)->forks);
		sem_close((*params)->pickup);
		free(*params);
	}
}

void	clean_philo_data(t_philo_data *data)
{
	if (data != NULL)
		free(data);
}
