/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oislamog <oislamog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:51:04 by oislamog          #+#    #+#             */
/*   Updated: 2024/11/22 18:51:04 by oislamog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_base(unsigned long nb, char *alpha)
{
	int	count;

	count = 0;
	if (nb >= 16)
		count += ft_base(nb / 16, alpha);
	count += ft_print_char(alpha[nb % 16]);
	return (count);
}
