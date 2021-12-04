/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:06:15 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/17 12:24:42 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

/*
	source: https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
*/

float	myAbs(float value) {
	return ( value >= 0 ? value : -value );
}

float	area(Point a, Point b, Point c)
{
	Fixed temp;

	temp = a.getX() * (b.getY() - c.getY())
		+ b.getX() * (c.getY() - a.getY())
		+ c.getX() * (a.getY() - b.getY());
	return (myAbs(temp.toFloat() / 2));
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	float	A = area(a, b, c);
	float	A1 = area(point, b, c);
	float	A2 = area(a, point, c);
	float	A3 = area(a, b, point);
	
	return (A == A1 + A2 + A3);
}
