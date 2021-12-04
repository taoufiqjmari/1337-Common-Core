/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:44:30 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 16:02:32 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void) {
	Bureaucrat	One("Tonton", 2);

	std::cout << One;
	try {
		std::cout << One.getName() << std::endl;
		std::cout << One.getGrade() << std::endl;
		One.incrementGrade();
		One.incrementGrade();
		std::cout << One.getGrade() << std::endl;
		One.incrementGrade();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << " _________________________________________________" << std::endl;
	std::cout << "|                                                 |" << std::endl;
	std::cout << " -------------------------------------------------" << std::endl;

	try {
		Bureaucrat	Two("Dine", 152);
		
		std::cout << Two;
		std::cout << Two.getName() << std::endl;
		std::cout << Two.getGrade() << std::endl;
		Two.incrementGrade();
		std::cout << Two.getGrade() << std::endl;
		Two.incrementGrade();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
