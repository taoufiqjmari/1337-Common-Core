/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:28:23 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:31:26 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {
	std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(Intern const &src) {
	std::cout << "Intern copy constructor called" << std::endl;
	*this = src;
}

Intern::~Intern() {
	std::cout << "Intern default destructor called" << std::endl;
}

Intern	&Intern::operator=(const Intern &rhs) {
	std::cout << "Intern equal operator called" << std::endl;
	(void)rhs;
	return (*this);
}

Form	*Intern::makeForm(std::string const &form, std::string const &target) {
	Form*	(*func[FORMS])(std::string const&) = {SCF::clone, RRF::clone, PPF::clone};
	std::string	forms[FORMS] = {"shrubbery creation", "robotomy request", "presidential pardon"};

	for (int i(0); i < FORMS; i++) {
		if (form == forms[i]) {
			std::cout << "Intern creates " << form << std::endl;
			return (func[i](target));
		}
	}
	throw FormNotFound();
	return (NULL);
}
