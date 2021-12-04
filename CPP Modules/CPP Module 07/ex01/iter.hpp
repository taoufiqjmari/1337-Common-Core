/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:00:35 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/10 13:52:24 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ITER_HPP
#define	ITER_HPP

#include <iostream>

template <typename T>
void	iter(T *a, unsigned int lenght, void (*func)(const T &a)) {
	unsigned int	i(0);

	while (i < lenght) {
		func(a[i]);
		i++;
	}
}

#endif

