/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:31:36 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 19:16:08 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form()
	: _sign_grade(1)
	, _exec_grade(1)
	, _signed(false)
{
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(std::string name, int sign_grade, int exec_grade, std::string target)
	: _name(name)
	, _sign_grade(sign_grade)
	, _exec_grade(exec_grade)
	, _signed(false)
	, _target(target)
{
	std::cout << "Form constructor called" << std::endl;
	
	if (_sign_grade < 1 || _exec_grade < 1)
		throw Form::GradeTooHighException();
	if (_sign_grade > 150 || _exec_grade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(Form const& src) 
	: _sign_grade(src._sign_grade)
	, _exec_grade(src._exec_grade)
{
	std::cout << "Form copy constructor called" << std::endl;
	*this = src;
}

Form::~Form() {
	std::cout << "Form default destructor called" << std::endl;
}

Form	&Form::operator=(const Form &rhs)
{
	std::cout << "Form equal operator called" << std::endl;
	this->_signed = rhs._signed;
	return (*this);
}

std::string const	Form::getName(void) const {
	return (_name);
}

int	Form::getSignGrade(void) const {
	return (_sign_grade);
}

int	Form::getExecGrade(void) const {
	return (_exec_grade);
}

bool	Form::getSigned(void) const {
	return (_signed);
}

std::string	Form::getTarget(void) const {
	return (_target);
}

void	Form::beSigned(Bureaucrat const& One) {
	if (One.getGrade() <= _sign_grade) {
		_signed = true;
		One.signForm(*this);
	}
	else {
		One.signForm(*this);
		throw Form::GradeTooLowException();
	}
}

std::ostream	&operator<<(std::ostream &output, Form const& i) {
	output << i.getName() << " Form requires " << i.getSignGrade() << " grades to sign and ";
	output << i.getExecGrade() << " grades to execute and "; 
	if (i.getSigned())
		output << "it's signed" << std::endl;
	else
		output << "it isn't signed" << std::endl;
	return (output);
}
