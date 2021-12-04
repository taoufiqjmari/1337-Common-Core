/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdcharp_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:09:55 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/03 12:12:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putdcharp_fd(char **argv, int fd)
{
	int	i;

	i = 0;
	if (argv)
		while (argv[i])
			ft_putendl_fd(argv[i++], fd);
}
