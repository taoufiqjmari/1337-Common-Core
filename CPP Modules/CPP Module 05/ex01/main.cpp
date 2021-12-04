/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:44:30 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 14:03:17 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

int	main(void) {
	try {
		Bureaucrat	One("Tonton", 20);
		Form	toDo("London", 25, 15);
		std::cout << One;
		std::cout << toDo;
		toDo.beSigned(One);
		std::cout << toDo;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << " _________________________________________________" << std::endl;
	std::cout << "|                                                 |" << std::endl;
	std::cout << " -------------------------------------------------" << std::endl;
	try {
		Bureaucrat	One("Tonton", 20);
		Form	toDo("London", 15, 15);
		std::cout << One;
		std::cout << toDo;
		toDo.beSigned(One);
		std::cout << toDo;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
