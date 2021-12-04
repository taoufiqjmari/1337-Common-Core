/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:42:24 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/23 17:44:12 by tjmari           ###   ########.fr       */
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

Fixed::Fixed(int const value) {
	std::cout << "Int constructor called" << std::endl;
	this->_fixedPointValue = value << _numOfFractionalBits;
}

Fixed::Fixed(float const value) {
	std::cout << "Float constructor called" << std::endl;
	this->_fixedPointValue = roundf(value * (1 << _numOfFractionalBits));
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const {
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

int	Fixed::toInt(void) const {
	return (this->_fixedPointValue >> _numOfFractionalBits);
}

float	Fixed::toFloat(void) const {
	return ((float)this->_fixedPointValue / (1 << _numOfFractionalBits));
}

std::ostream	&operator<<(std::ostream &output, Fixed const& i) {
	output << i.toFloat();
	return (output);
}
