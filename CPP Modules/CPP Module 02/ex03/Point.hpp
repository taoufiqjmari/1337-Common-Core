/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:13:21 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/13 19:06:45 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include <iostream>
# include "Fixed.hpp"

class Point
{
private:
	const Fixed	x;
	const Fixed	y;
public:
	Point();
	Point(const Point &);
	Point(const float, const float);
	~Point();

	Point &operator=(const Point &);

	const Fixed	&getX() const;
	const Fixed	&getY() const;
};

bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif
