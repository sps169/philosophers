/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperez-s <sperez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:39:05 by sperez-s          #+#    #+#             */
/*   Updated: 2023/04/12 22:54:26 by sperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec * 1000 + end->tv_usec / 1000) - (start->tv_sec * 1000 + start->tv_usec / 1000));
}


size_t	ft_strlen(char *string)
{
	int	i;

	if (string == NULL)
		return (0);
	i = 0;
	while (string[i])
		i++;
	return (i);
}

int	ft_is_digit(char digit)
{
	return (digit >= '0' && digit <= '9');
}

unsigned int	atou(char *string)
{
	char			*curr;
	unsigned int	result;

	result = 0;
	curr = string;
	if (string == NULL)
		return (4294967295);
	if (ft_strlen(string) > 10)
		return (4294967295);
	if (ft_strlen(string) == 10 && string[0] > '2' && string[0] <= '9')
		return (4294967295);
	while (*curr)
	{
		if (!ft_is_digit(*curr))
			return (4294967295);
		result = result * 10 + *curr - '0';
		curr++;
	}
	if (result > 2147483647)
		return (4294967295);
	return (result);
}
