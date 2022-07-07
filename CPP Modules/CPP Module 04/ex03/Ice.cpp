/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:07:27 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:31:11 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice()
{
    std::cout << "Ice default constructor called" << std::endl;
    _type = "ice";
}

Ice::Ice(Ice const &src)
{
    std::cout << "Ice copy constructor called" << std::endl;
    *this = src;
}

Ice::~Ice()
{
    std::cout << "Ice destructor called" << std::endl;
}

Ice &Ice::operator=(const Ice &rhs)
{
    (void)rhs;
    std::cout << "Ice equal operator called" << std::endl;
    return *this;
}

AMateria *Ice::clone() const
{
    return new Ice();
}

void Ice::use(ICharacter &target)
{
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
