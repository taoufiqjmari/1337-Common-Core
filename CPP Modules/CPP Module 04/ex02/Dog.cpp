/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:27:37 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:30:10 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog type constructor called" << std::endl;
	this->_type = "Dog";
	this->_ideas = new Brain();
}

Dog::Dog(Dog const &src)
{
	std::cout << "Dog copy constructor called" << std::endl;
	*this = src;
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete _ideas;
}

Dog &Dog::operator=(const Dog &rhs)
{
	std::cout << "Dog equal operator called" << std::endl;
	if (this != &rhs)
	{
		this->_ideas = new Brain(rhs.getIdea());
		this->_type = rhs._type;
	}
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << "Bark" << std::endl;
}

std::string Dog::getIdea() const
{
	return (_ideas->getIdea());
}
