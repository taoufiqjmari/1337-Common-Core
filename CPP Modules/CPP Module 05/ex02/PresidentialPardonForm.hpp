/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:46:54 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 16:26:14 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFROM_HPP
#define PRESIDENTIALPARDONFROM_HPP

#include "Form.hpp"

#define PPF	PresidentialPardonForm

class PPF : public Form {
public:
	PPF();
	PPF(std::string);
	PPF(PPF const&);
	~PPF();

	PPF	&operator=(const PPF &);

	virtual void	execute(Bureaucrat const & executor) const;
};

#endif
