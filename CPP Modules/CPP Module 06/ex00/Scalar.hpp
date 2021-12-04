/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scalar.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:54:19 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/04 13:41:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCALAR_HPP
#define	SCALAR_HPP

#include <iostream>
#include <string>
#include <math.h>

class Scalar {
private:
	std::string	_value;
public:
	Scalar();
	Scalar(std::string const);
	Scalar(Scalar const&);
	~Scalar();

	Scalar	&operator=(const Scalar &);

	std::string getValue(void) const;

	char	toChar(void) const;
	int		toInt(void) const;
	float	toFloat(void) const;
	double	toDouble(void)const;

	class Impossible : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class NonDisplayable : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class NANF : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

std::ostream	&operator<<(std::ostream &, const Scalar &);

#endif
