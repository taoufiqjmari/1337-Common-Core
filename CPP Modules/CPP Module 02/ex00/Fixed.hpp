/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:25:51 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/23 15:23:55 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string>

class Fixed
{
private:
	int					_fixedPointValue;
	static int const	_numOfFractionalBits;
public:
	Fixed();
	Fixed(Fixed const& src);
	~Fixed();

	Fixed	&operator=(Fixed const& rhs);

	int	getRawBits(void) const;
	void	setRawBits(int const raw);
};

#endif
