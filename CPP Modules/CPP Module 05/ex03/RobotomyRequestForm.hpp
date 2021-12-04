/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:47:55 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:59:33 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "Form.hpp"
#include <cstdlib>
#include <ctime>

#define RRF	RobotomyRequestForm

class RRF : public Form {
public:
	RRF();
	RRF(std::string);
	RRF(RRF const&);
	~RRF();

	RRF	&operator=(const RRF &);

	virtual void	execute(Bureaucrat const & executor) const;
	static Form	*clone(std::string const&);
	class Failure : public std::exception {
		virtual const char* what() const throw() {
			return ("It’s a failure");
		}
	};
};

#endif
