/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:25:51 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/24 14:02:20 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
private:
	int					_fixedPointValue;
	static int const	_numOfFractionalBits;
public:
	Fixed();
	Fixed(Fixed const& src);
	Fixed(int const);
	Fixed(float const);
	~Fixed();

	int	getRawBits(void) const;
	void	setRawBits(int const raw);

	Fixed	&operator=(Fixed const& rhs);
	bool	operator>(Fixed const& rhs) const;
	bool	operator<(Fixed const& rhs) const;
	bool	operator>=(Fixed const& rhs) const;
	bool	operator<=(Fixed const& rhs) const;
	bool	operator==(Fixed const& rhs) const;
	bool	operator!=(Fixed const& rhs) const;
	Fixed	operator+(Fixed const& rhs) const;
	Fixed	operator-(Fixed const& rhs) const;
	Fixed	operator*(Fixed const& rhs) const;
	Fixed	operator/(Fixed const& rhs) const;
	Fixed	&operator++();		// Prefix increment operator.
	Fixed	operator++(int);	// Postfix increment operator.
	Fixed	&operator--();		// Prefix decrement operator.
	Fixed	operator--(int);	// Postfix decrement operator.

	static Fixed &min(Fixed &v1, Fixed &v2);
	static Fixed const&	min(Fixed const& v1, Fixed const& v2);
	static Fixed &max(Fixed &v1, Fixed &v2);
	static Fixed const&	max(Fixed const& v1, Fixed const& v2);

	int		toInt(void) const;
	float	toFloat(void) const;
};

std::ostream	&operator<<(std::ostream &output, Fixed const& i);

#endif
