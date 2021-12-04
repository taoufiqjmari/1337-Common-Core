/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:28:31 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/17 12:26:11 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

int	main(void) {
	Point a(1, 1);
	Point b(1, 10);
	Point c(10, 1);
	Point pt(5, 5);

	if (bsp(a, b, c, pt))
		std::cout << "Point is inside triangle" << std::endl;
	else
		std::cout << "Point is not inside triangle" << std::endl;
	return (0);
}
