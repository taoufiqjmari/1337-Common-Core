/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:44:30 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:27:28 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int	main(void) {
	try {
		Intern  someRandomIntern;
		Form*   rrf;
	
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf)
			std::cout << rrf->getTarget() << " // " << rrf->getSignGrade() << std::endl;
	
		delete rrf;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
