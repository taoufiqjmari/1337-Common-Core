/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:48:51 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/04 13:07:04 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BASE_HPP
#define	BASE_HPP

#include <iostream>

#define MIN	1
#define	MAX	3

class Base {
public:
	virtual ~Base() {};
};
class A : public Base {};
class B : public Base {};
class C : public Base {};

#endif
