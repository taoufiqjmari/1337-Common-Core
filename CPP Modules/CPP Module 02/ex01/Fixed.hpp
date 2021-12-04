/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:25:51 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/23 17:17:13 by tjmari           ###   ########.fr       */
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

	Fixed	&operator=(Fixed const& rhs);

	int	getRawBits(void) const;
	void	setRawBits(int const raw);

	int	toInt(void) const;
	float	toFloat(void) const;
};

std::ostream	&operator<<(std::ostream &output, Fixed const& i);

#endif
