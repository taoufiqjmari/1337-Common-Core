/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:58:31 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/09 14:36:47 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	WHATEVER_HPP
#define	WHATEVER_HPP

#include <iostream>

template <typename T>
void	swap(T &a, T &b) {
	T	tmp;

	tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
T	min(const T& a, const T& b) {
	return (a < b ? a : b);
}

template <typename T>
T	max(const T& a, const T& b) {
	return (a > b ? a : b);
}

#endif
