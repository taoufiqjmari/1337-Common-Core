/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:46:42 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/29 19:29:24 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BUREAUCRAT_HPP
#define	BUREAUCRAT_HPP

#include <iostream>

class Bureaucrat {
private:
	std::string	const	_name;
	int	_grade;
public:
	Bureaucrat();
	Bureaucrat(std::string const, int);
	Bureaucrat(Bureaucrat const&);
	~Bureaucrat();

	Bureaucrat	&operator=(const Bureaucrat &);

	class GradeTooHighException : public std::exception {
		virtual const char* what() const throw() {
			return ("Grade is too high");
		}
	};
	class GradeTooLowException : public std::exception {
		virtual const char* what() const throw() {
			return ("Grade is too low");
		}
	};

	std::string	const getName(void) const;
	int	getGrade(void) const;

	void	incrementGrade(void);
	void	decrementGrade(void);
};

std::ostream	&operator<<(std::ostream &output, Bureaucrat const& i);

#endif
