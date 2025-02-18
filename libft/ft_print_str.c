/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oislamog <oislamog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:52:08 by oislamog          #+#    #+#             */
/*   Updated: 2025/02/10 17:13:00 by oislamog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *c)
{
	int	count;
	int	i;

	if (!c)
		return (ft_print_str("(null)"));
	i = 0;
	count = 0;
	while (c[i])
	{
		count += ft_print_char(c[i]);
		i++;
	}
	return (count);
}
