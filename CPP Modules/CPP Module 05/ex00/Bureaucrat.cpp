/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:49:08 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 10:28:09 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() {
	std::cout << "Bureaucrat default constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string const name, int grade) : _name(name) {
	std::cout << "Bureaucrat constructor called" << std::endl;

	if (grade < 1) {
		throw Bureaucrat::GradeTooHighException();
	} else if (grade > 150) {
		throw Bureaucrat::GradeTooLowException();
	} else
		_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const& src)
	: _name(src._name)
{
	std::cout << "Bureaucrat copy constructor called" << std::endl;
	*this = src;
}

Bureaucrat::~Bureaucrat() {
	std::cout << "Bureaucrat default destructor called" << std::endl;
}

Bureaucrat	&Bureaucrat::operator=(const Bureaucrat &rhs)
{
	std::cout << "Bureaucrat equal operator called" << std::endl;
	this->_grade = rhs._grade;
	return (*this);
}

std::string const	Bureaucrat::getName(void) const {
	return (_name);
}

int	Bureaucrat::getGrade(void) const {
	return (_grade);
}

void	Bureaucrat::incrementGrade(void) {
	if (_grade > 1)
		_grade--;
	else
		throw Bureaucrat::GradeTooHighException();
}

void	Bureaucrat::decrementGrade(void) {
	if (_grade < 150)
		_grade++;
	else
		throw Bureaucrat::GradeTooLowException();
}

std::ostream	&operator<<(std::ostream &output, Bureaucrat const& i) {
	output << i.getName() << ", bureaucrat grade " << i.getGrade() << std::endl;
	return (output);
}
