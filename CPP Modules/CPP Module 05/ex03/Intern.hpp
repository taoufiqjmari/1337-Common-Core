/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:28:33 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:23:21 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#define	FORMS	3

class Intern {
public:
	Intern();
	Intern(Intern const&);
	~Intern();

	Intern	&operator=(const Intern &);

	Form	*makeForm(std::string const&, std::string const&);

	class FormNotFound : public std::exception {
		virtual const char* what() const throw() {
			return ("Form type not found");
		}
	};
};

#endif
