/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:27:39 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/27 14:36:04 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() {
	std::cout << "WrongCat type constructor called" << std::endl;
	this->_type = "WrongCat";
}

WrongCat::WrongCat(WrongCat const& src) {
	std::cout << "WrongCat copy constructor called" << std::endl;
	*this = src;
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat	&WrongCat::operator=(const WrongCat &rhs)
{
	std::cout << "WrongCat equal operator called" << std::endl;
	this->_type = rhs._type;
	return (*this);
}

void	WrongCat::makeSound() const {
	std::cout << "Meow" << std::endl;
}
