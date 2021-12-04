/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:45 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/12 16:38:57 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

int main()
{
	Span sp = Span(5);
	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

// int main()
// {
// 	std::vector<int> v(10000, 10);
// 	try {
// 		Span sp = Span(10010);
// 		sp.addNumber(1);
// 		sp.addNumber(2);
// 		sp.addNumber(3);
// 		sp.addNumber(4);
// 		sp.addNumber(5);
// 		sp.addNumber(6);
// 		sp.addNumber(7);
// 		sp.addNumber(8);
// 		sp.addNumber(9);
// 		sp.addNumber(10);
// 		sp.addNumber(v.begin(), v.end());
// 		std::cout << sp.shortestSpan() << std::endl;
// 		std::cout << sp.longestSpan() << std::endl;
// 	} catch (std::exception &e) {
// 		std::cout << e.what() << std::endl;
// 	}
// }
