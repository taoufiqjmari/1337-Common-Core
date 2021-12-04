/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:35:05 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/27 18:45:37 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() {
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(std::string type) : _type(type) {
	std::cout << "Animal type constructor called" << std::endl;
}

Animal::Animal(Animal const& src) {
	std::cout << "Animal copy constructor called" << std::endl;
	*this = src;
}

Animal::~Animal() {
	std::cout << "Animal destructor called" << std::endl;
}

Animal	&Animal::operator=(const Animal &rhs)
{
	std::cout << "Animal equal operator called" << std::endl;
	this->_type = rhs._type;
	return (*this);
}

std::string	Animal::getType(void) const {
	return (this->_type);
}
