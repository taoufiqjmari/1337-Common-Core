/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scalar.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:57:40 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/04 13:54:29 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scalar.hpp"

Scalar::Scalar() {}

Scalar::Scalar(std::string value) : _value(value) {}

Scalar::Scalar(const Scalar &src) {
	*this = src;
}

Scalar::~Scalar() {}

Scalar	&Scalar::operator=(const Scalar &rhs)
{
	this->_value = rhs._value;
	return (*this);
}

std::string	Scalar::getValue(void) const {
	return (_value);
}

char	Scalar::toChar(void) const {
	char	C;

	try {
		C = static_cast<char>(std::stoi(_value));
		if (!isprint(C))
			throw Scalar::NonDisplayable();
	}
	catch (Scalar::NonDisplayable &e) {
		throw Scalar::NonDisplayable();
	}
	catch (std::exception &e) {
		throw Scalar::Impossible();
	}
	return (C);
}

int		Scalar::toInt(void) const {
	int	I;

	try {
		I = static_cast<int>(std::stoi(_value));
	}
	catch (std::exception &e) {
		throw Scalar::Impossible();
	}
	return (I);
}

float	Scalar::toFloat(void) const {
	float	F;

	try {
		F = std::stof(_value);
		if (isnan(F))
			throw Scalar::NANF();
	}
	catch (Scalar::NANF &e) {
		throw Scalar::NANF();
	}
	catch (std::exception &e) {
		throw Scalar::Impossible();
	}
	return (F);
}

double	Scalar::toDouble(void) const {
	double	D;

	try {
		D = std::stod(_value);
	}
	catch (Scalar::NANF &e) {
		throw std::exception();
	}
	catch (std::exception &e) {
		throw Scalar::Impossible();
	}
	return (D);
}

std::ostream	&operator<<(std::ostream &output, const Scalar &i) {
	try {
		char	C = i.toChar();
		output << "char: '" << C << "'" << std::endl;
	} catch (std::exception &e) {
		output << "char: ";
		std::cerr << e.what() << std::endl;
	}

	try {
		int	I = i.toInt();
		output << "int: " << I << std::endl;
	} catch (std::exception &e) {
		output << "int: ";
		std::cerr << e.what() << std::endl;
	}

	try {
		float	F = i.toFloat();
		output << "float: " << F;
		if (!isinf(F)) {
			if (roundf(F) == F)
				output << ".0f";
			else
				output << "f";
		}
		else
			output << "f";
		std::cout << std::endl;
	} catch (std::exception &e) {
		output << "float: ";
		std::cerr << e.what() << std::endl;
	}

	try {
		double	D = i.toDouble();
		output << "double: " << D;
		if (!isinf(D))
			if (roundf(D) == D)
				output << ".0";
		std::cout << std::endl;
	} catch (std::exception &e) {
		output << "double: ";
		std::cerr << e.what() << std::endl;
	}
	return (output);
}

const char	*Scalar::Impossible::what() const throw() {
	return ("impossible");
}

const char	*Scalar::NonDisplayable::what() const throw() {
	return ("Non displayable");
}

const char	*Scalar::NANF::what() const throw() {
	return ("nanf");;
}
