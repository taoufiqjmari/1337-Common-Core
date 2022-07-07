/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:24:17 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:32:15 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
    std::cout << "MateriaSource default constructor called" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        _inventory[i] = NULL;
    }
}

MateriaSource::MateriaSource(MateriaSource const &src)
{
    std::cout << "MateriaSource copy constructor called" << std::endl;
    *this = src;
}

MateriaSource &MateriaSource::operator=(const MateriaSource &rhs)
{
    std::cout << "MateriaSource equal operator called" << std::endl;
    if (this != &rhs)
    {
        for (int i = 0; i < 4; i++)
        {
            if (rhs._inventory[i] != NULL)
                delete _inventory[i];
            if (rhs._inventory[i] != NULL)
                _inventory[i] = rhs._inventory[i]->clone();
            else
                _inventory[i] = NULL;
        }
    }
    return *this;
}

MateriaSource::~MateriaSource()
{
    std::cout << "MateriaSource destructor called" << std::endl;
    for (int n = 0; n < 4; n++)
        if (_inventory[n])
            delete _inventory[n];
}

void MateriaSource::learnMateria(AMateria *m)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (_inventory[i] == NULL)
        {
            _inventory[i] = m;
            break;
        }
    }
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
    for (int i = 0; i < 4; i++)
        if (_inventory[i] != NULL && _inventory[i]->getType() == type)
            return _inventory[i]->clone();
    return NULL;
}
