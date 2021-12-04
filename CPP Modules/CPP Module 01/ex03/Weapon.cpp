/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:38:00 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:26:22 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon() {}

Weapon::Weapon(std::string type) : _type(type) {}

Weapon::~Weapon() {}

void	Weapon::setType(std::string type) {
	this->_type = type;
}

std::string const&	Weapon::getType(void) const {
	return (this->_type);
}
