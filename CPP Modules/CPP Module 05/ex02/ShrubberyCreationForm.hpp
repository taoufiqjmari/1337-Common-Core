/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:49:10 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 14:12:30 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include <fstream>
#include "Form.hpp"

#define SCF	ShrubberyCreationForm

class SCF : public Form {
public:
	SCF();
	SCF(std::string);
	SCF(SCF const&);
	~SCF();

	SCF	&operator=(const SCF &);

	virtual void	execute(Bureaucrat const & executor) const;
};

#endif
