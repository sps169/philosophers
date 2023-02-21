/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_measurement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:39:05 by sperez-s          #+#    #+#             */
/*   Updated: 2023/02/21 17:37:03 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec * 1000 + end->tv_usec / 1000) - (start->tv_sec * 1000 + start->tv_usec / 1000));
}
