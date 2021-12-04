/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:54:36 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/24 15:11:31 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int const	Fixed::_numOfFractionalBits(8);

Fixed::Fixed() : _fixedPointValue(0) {}

Fixed::Fixed(Fixed const& src) {
	*this = src;
}

Fixed::Fixed(int const value) {
	this->_fixedPointValue = value << _numOfFractionalBits;
}

Fixed::Fixed(float const value) {
	this->_fixedPointValue = roundf(value * (1 << _numOfFractionalBits));
}

Fixed::~Fixed() {}

int	Fixed::getRawBits(void) const {
	return (this->_fixedPointValue);
}

void	Fixed::setRawBits(int const raw) {
	this->_fixedPointValue = raw;
}

Fixed	&Fixed::operator=(Fixed const& rhs) {
	this->_fixedPointValue = rhs.getRawBits();
	return (*this);
}

bool	Fixed::operator>(Fixed const& rhs) const {
	return (this->_fixedPointValue > rhs._fixedPointValue);
}

bool	Fixed::operator<(Fixed const& rhs) const {
	return !(*this > rhs);
}

bool	Fixed::operator>=(Fixed const& rhs) const {
	return (*this == rhs
			|| this->_fixedPointValue > rhs._fixedPointValue);
}

bool	Fixed::operator<=(Fixed const& rhs) const {
	return (*this == rhs
			|| this->_fixedPointValue < rhs._fixedPointValue);
}

bool	Fixed::operator==(Fixed const& rhs) const {
	return (this->_fixedPointValue == rhs._fixedPointValue);
}

bool	Fixed::operator!=(Fixed const& rhs) const {
	return !(*this == rhs);
}

Fixed	Fixed::operator+(Fixed const& rhs) const {
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed	Fixed::operator-(Fixed const& rhs) const {
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed	Fixed::operator*(Fixed const& rhs) const {
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed	Fixed::operator/(Fixed const& rhs) const {
	return (Fixed(this->toFloat() / rhs.toFloat()));
}

Fixed &Fixed::min(Fixed &v1, Fixed &v2) {
	if (v1.getRawBits() > v2.getRawBits())
		return (v2);
	return (v1);
}

Fixed const&	Fixed::min(Fixed const& v1, Fixed const& v2) {
	if (v1.getRawBits() > v2.getRawBits())
		return (v2);
	return (v1);
}

Fixed &Fixed::max(Fixed &v1, Fixed &v2) {
	if (v1.getRawBits() < v2.getRawBits())
		return (v2);
	return (v1);
}

Fixed const&	Fixed::max(Fixed const& v1, Fixed const& v2) {
	if (v1.getRawBits() < v2.getRawBits())
		return (v2);
	return (v1);
}

Fixed	&Fixed::operator++() {
	this->_fixedPointValue++;
	return (*this);
}

Fixed	Fixed::operator++(int) {
	Fixed	temp(*this);
	++*this;
	return (temp);
}

Fixed	&Fixed::operator--() {
	this->_fixedPointValue--;
	return (*this);
}

Fixed	Fixed::operator--(int) {
	Fixed	temp(*this);
	--*this;
	return (temp);
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
