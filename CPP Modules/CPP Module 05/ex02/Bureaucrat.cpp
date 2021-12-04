/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:49:08 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:36:35 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

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

Bureaucrat::Bureaucrat(Bureaucrat const& src) {
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

void	Bureaucrat::signForm(const Form &form) const {
	if (form.getSigned())
		std::cout << _name << " signs " << form.getName() << std::endl;
	else
		std::cout << _name << " cannot sign " << form.getName() << " because grades are too low" << std::endl;
}

void	Bureaucrat::executeForm(Form const & form) {
	if (form.getSigned()) {
		if (this->getGrade() <= form.getExecGrade()) {
			form.execute(*this);
			std::cout << this->getName() << " executes " << form.getName() << std::endl;
			return ;
		}
		throw Bureaucrat::GradeTooLowException();
	}
	throw Bureaucrat::FormNotSigned();
}

std::ostream	&operator<<(std::ostream &output, Bureaucrat const& i) {
	output << i.getName() << ", bureaucrat grade " << i.getGrade() << std::endl;
	return (output);
}
