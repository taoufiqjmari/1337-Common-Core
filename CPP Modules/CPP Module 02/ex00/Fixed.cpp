/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:12:54 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/23 15:36:58 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int const	Fixed::_numOfFractionalBits(8);

Fixed::Fixed() : _fixedPointValue(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const& src) {
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_fixedPointValue);
}

void	Fixed::setRawBits(int const raw) {
	this->_fixedPointValue = raw;
}

Fixed	&Fixed::operator=(Fixed const& rhs) {
	std::cout << "Assignation operator called" << std::endl;
	this->_fixedPointValue = rhs.getRawBits();
	return (*this);
}
