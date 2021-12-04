/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:13:26 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/13 19:36:51 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(float const x, float const y) : x(x), y(y) {}

Point::Point(Point const& src) : x(src.x), y(src.y) {}

Point::~Point() {}

Point	&Point::operator=(Point const& rhs) {
	(Fixed)x = rhs.x;
	(Fixed)y = rhs.y;
	return (*this);
}

const Fixed	&Point::getX() const {
	return (x);
}

const Fixed	&Point::getY() const {
	return (y);
}
