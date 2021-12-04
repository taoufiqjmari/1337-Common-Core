/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:31:38 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 11:23:55 by tjmari           ###   ########.fr       */
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
public:
	Form();
	Form(std::string, int, int);
	Form(Form const&);
	~Form();

	Form	&operator=(const Form &);

	std::string const	getName(void) const;
	int		getSignGrade(void) const;
	int		getExecGrade(void) const;
	bool	getSigned(void) const;
	void	beSigned(Bureaucrat const&);
	
	class GradeTooHighException : public Bureaucrat::GradeTooHighException {};
	class GradeTooLowException : public Bureaucrat::GradeTooLowException {};
};

std::ostream	&operator<<(std::ostream &output, Form const& i);

#endif
