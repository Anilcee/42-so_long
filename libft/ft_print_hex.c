/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oislamog <oislamog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:51:42 by oislamog          #+#    #+#             */
/*   Updated: 2024/11/22 18:51:42 by oislamog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(void *arg)
{
	int				count;
	unsigned long	address;
	char			*alpha;

	alpha = "0123456789abcdef";
	address = (unsigned long)arg;
	count = 0;
	if (address == 0)
	{
		count += ft_print_str("(nil)");
	}
	else
	{
		count += ft_print_str("0x");
		count += ft_base(address, alpha);
	}
	return (count);
}
