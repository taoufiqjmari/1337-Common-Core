/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:00:38 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/10 13:52:28 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

#define LENGHT	5

template <typename T>
void	putf(const T &n) {
	std::cout << n << '\t';
}

template <typename T>
void	func(const T &n) {
	std::cout <<  n * 2 << '\t';
}

int	main(void) {
	int	arr[LENGHT] = {49, 50, 51, 52, 53};

	std::cout << "putf:\t";
	iter<int>(arr, LENGHT, putf);
	std::cout << std::endl << "func:\t";
	iter<int>(arr, LENGHT, func);
	std::cout << std::endl;
}

