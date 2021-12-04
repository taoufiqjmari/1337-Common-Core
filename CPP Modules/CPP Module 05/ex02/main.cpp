/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:44:30 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 16:34:57 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main(void) {
	{
		try {
			Bureaucrat	One("Tomtom", 100);
			SCF	draw("home");
			draw.beSigned(One);
			One.executeForm(draw);
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
	std::cout << " _________________________________________________" << std::endl;
	std::cout << "|                                                 |" << std::endl;
	std::cout << " -------------------------------------------------" << std::endl;
	try {
		Bureaucrat	Two("Timtim", 20);
		RRF	robo("Cui");
		robo.beSigned(Two);
		Two.executeForm(robo);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << " _________________________________________________" << std::endl;
	std::cout << "|                                                 |" << std::endl;
	std::cout << " -------------------------------------------------" << std::endl;
	try {
		Bureaucrat	Three("Tamtam", 1);
		PPF	sir("Obm");
		sir.beSigned(Three);
		Three.executeForm(sir);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
