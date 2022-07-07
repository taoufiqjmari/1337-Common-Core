/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:18:21 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:30:56 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() : _name("unnamed")
{
    std::cout << "Character default constructor called" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        _inventory[i] = NULL;
        _floor[i] = NULL;
    }
}

Character::Character(std::string name) : _name(name)
{
    std::cout << "Character name constructor called" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        _inventory[i] = NULL;
        _floor[i] = NULL;
    }
}

Character::Character(Character const &src)
{
    std::cout << "Character copy constructor called" << std::endl;
    *this = src;
}

Character::~Character()
{
    std::cout << "Character destructor called" << std::endl;

    for (int i = 0; i < 4; i++)
    {
        if (_inventory[i] != NULL)
            delete _inventory[i];
        if (_floor[i] != NULL)
            delete _floor[i];
    }
}

Character &Character::operator=(const Character &rhs)
{
    std::cout << "Character equal operator called" << std::endl;
    if (this != &rhs)
    {
        this->_name = rhs._name;
        for (int i = 0; i < 4; i++)
        {
            if (_inventory[i] != NULL)
                delete _inventory[i];
            if (rhs._inventory[i] != NULL)
                _inventory[i] = rhs._inventory[i]->clone();
            else
                _inventory[i] = NULL;
            if (_floor[i] != NULL)
                delete _floor[i];
            if (rhs._floor[i] != NULL)
                _floor[i] = rhs._floor[i]->clone();
            else
                _floor[i] = NULL;
        }
    }
    return *this;
}

std::string const &Character::getName() const { return _name; }

void Character::equip(AMateria *m)
{
    for (int i = 0; i < 4; i++)
    {
        if (_inventory[i] == NULL)
        {
            _inventory[i] = m;
            break;
        }
    }
}

void Character::unequip(int idx)
{
    if (!(idx < 0 || idx > 3) && _inventory[idx] != NULL)
    {
        for (int i = 0; i < 4; i++)
        {
            if (_floor[i] == NULL)
            {
                _floor[i] = _inventory[idx];
                _inventory[idx] = NULL;
                break;
            }
        }
    }
}

void Character::use(int idx, ICharacter &target)
{
    if (!(idx < 0 || idx > 3))
    {
        if (_inventory[idx] != NULL)
            _inventory[idx]->use(target);
    }
}
