/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oislamog <oislamog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:51:52 by oislamog          #+#    #+#             */
/*   Updated: 2025/02/10 17:12:57 by oislamog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr(int n)
{
	long	nb;
	int		count;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		count += ft_print_char('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		count += ft_print_nbr(nb / 10);
	}
	count += ft_print_char(nb % 10 + '0');
	return (count);
}
