/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:27:39 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:28:48 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Cat type constructor called" << std::endl;
	this->_type = "Cat";
	this->_ideas = new Brain();
}

Cat::Cat(Cat const &src)
{
	std::cout << "Cat copy constructor called" << std::endl;
	*this = src;
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete _ideas;
}

Cat &Cat::operator=(const Cat &rhs)
{
	std::cout << "Cat equal operator called" << std::endl;
	if (this != &rhs)
	{
		this->_ideas = new Brain(rhs.getIdea());
		this->_type = rhs._type;
	}
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << "Meow" << std::endl;
}

std::string Cat::getIdea() const
{
	return (_ideas->getIdea());
}
