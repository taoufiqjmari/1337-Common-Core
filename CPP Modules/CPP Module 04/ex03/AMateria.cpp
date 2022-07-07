/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:25:04 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:30:33 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria()
{
    std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(std::string const &type) : _type(type)
{
    std::cout << "Animal type constructor called" << std::endl;
}

AMateria::AMateria(AMateria const &src)
{
    std::cout << "AMateria copy constructor called" << std::endl;
    *this = src;
}

AMateria::~AMateria()
{
    std::cout << "AMateria destructor called" << std::endl;
}

AMateria &AMateria::operator=(const AMateria &rhs)
{
    std::cout << "AMateria equal operator called" << std::endl;
    if (this != &rhs)
        this->_type = rhs._type;
    return *this;
}

std::string const &AMateria::getType() const { return _type; }
