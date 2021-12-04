/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:46:56 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:39:47 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PPF::PPF() : Form("", 25, 5, "") {
	std::cout << "PresidentialPardonForm default constructor called" << std::endl;
}

PPF::PPF(std::string target) : Form("theForm", 25, 5, target) {
	std::cout << "PresidentialPardonForm constructor called" << std::endl;
}

PPF::PPF(PPF const& src) {
	std::cout << "PresidentialPardonForm copy constructor called" << std::endl;
	*this = src;
}

PPF::~PPF() {
	std::cout << "PresidentialPardonForm default destructor called" << std::endl;
}

PPF	&PPF::operator=(const PPF &rhs) {
	(void)rhs;
	std::cout << "PresidentialPardonForm equal operator called" << std::endl;
	return (*this);
}

void	PPF::execute(Bureaucrat const & executor) const {
	if (this->getSigned()) {
		if (executor.getGrade() <= this->getExecGrade()) {
			std::cout << this->getTarget() << " has been pardoned by Zafod Beeblebrox" << std::endl;
			return ;
		}
		throw Form::GradeTooLowException();
	}
	throw Form::FormNotSigned();
}
