/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:31:38 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:39:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FORM_HPP
#define	FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Form {
private:
	std::string const	_name;
	int const	_sign_grade;
	int const	_exec_grade;
	bool		_signed;
	std::string const	_target;
public:
	Form();
	Form(std::string, int, int, std::string);
	Form(Form const&);
	~Form();

	Form	&operator=(const Form &);

	std::string const	getName(void) const;
	int		getSignGrade(void) const;
	int		getExecGrade(void) const;
	bool	getSigned(void) const;
	std::string	getTarget(void) const;
	void	beSigned(Bureaucrat const&);
	virtual void	execute(Bureaucrat const & executor) const = 0;

	class GradeTooHighException : public Bureaucrat::GradeTooHighException {};
	class GradeTooLowException : public Bureaucrat::GradeTooLowException {};
	class FormNotSigned : public Bureaucrat::FormNotSigned {};
};

std::ostream	&operator<<(std::ostream &output, Form const& i);

#endif
