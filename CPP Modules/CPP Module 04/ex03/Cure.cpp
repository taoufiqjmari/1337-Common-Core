/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:07:27 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:31:08 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure()
{
    std::cout << "Cure default constructor called" << std::endl;
    _type = "cure";
}

Cure::Cure(Cure const &src)
{
    std::cout << "Cure copy constructor called" << std::endl;
    *this = src;
}

Cure::~Cure()
{
    std::cout << "Cure destructor called" << std::endl;
}

Cure &Cure::operator=(const Cure &rhs)
{
    (void)rhs;
    std::cout << "Cure equal operator called" << std::endl;
    return *this;
}

AMateria *Cure::clone() const
{
    return new Cure();
}

void Cure::use(ICharacter &target)
{
    std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
