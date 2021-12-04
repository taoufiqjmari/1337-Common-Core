/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:48:55 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:58:49 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RRF::RRF() : Form("", 72, 45, "") {
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}

RRF::RRF(std::string target) : Form("theForm", 72, 45, target) {
	std::cout << "RobotomyRequestForm constructor called" << std::endl;
}

RRF::RRF(RRF const& src) {
	std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
	*this = src;
}

RRF::~RRF() {
	std::cout << "RobotomyRequestForm default destructor called" << std::endl;
}

RRF	&RRF::operator=(const RRF &rhs) {
	(void)rhs;
	std::cout << "RobotomyRequestForm equal operator called" << std::endl;
	return (*this);
}

void	RRF::execute(Bureaucrat const & executor) const {
	if (this->getSigned()) {
		if (executor.getGrade() <= this->getExecGrade()) {
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			if (std::rand() % 2) {
				std::cout << "patapata ..." << std::endl;
				std::cout << this->getTarget() << " has been robotomized successfully" << std::endl;
				return ;
			}
			throw RRF::Failure();
		}
		throw Form::GradeTooLowException();
	}
	throw Form::FormNotSigned();
}

Form	*RRF::clone(std::string const& target) {
	return (new RobotomyRequestForm(target));
}
