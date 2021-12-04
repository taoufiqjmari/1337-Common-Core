/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:23:16 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/13 11:12:00 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>

const char *notFound::what() const throw() {
	return ("Not Found");
}

int	main(void) {
	// VECTOR
	std::vector<int> V(5, 5);
	V.push_back(8);
	V.push_back(9);
	V.push_back(10);

	std::vector<int>::iterator it;
	try {
		it = easyfind(V, 8);
		std::cout << *it << std::endl;
	} catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// LIST
	std::list<int> L;
	L.push_back(4);
	L.push_back(5);
	L.push_back(6);
	std::list<int>::iterator it2;
	try {
		it2 = easyfind(L, 5);
		std::cout << *it2 << std::endl;
	} catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// DEQUE
	std::deque<int> D;
	D.push_back(4);
	D.push_back(5);
	D.push_back(6);
	std::deque<int>::iterator it3;
	try {
		it3 = easyfind(D, 5);
		std::cout << *it3 << std::endl;
	} catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
