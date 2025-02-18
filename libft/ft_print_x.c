/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oislamog <oislamog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:52:23 by oislamog          #+#    #+#             */
/*   Updated: 2024/11/22 18:52:23 by oislamog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_x(unsigned int nb, int type)
{
	char	*alpha;

	if (type == 'X')
		alpha = "0123456789ABCDEF";
	if (type == 'x')
		alpha = "0123456789abcdef";
	return (ft_base(nb, alpha));
}
