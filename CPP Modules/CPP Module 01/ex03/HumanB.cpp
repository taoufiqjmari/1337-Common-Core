/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:53:26 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:41:03 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB() {}

HumanB::HumanB(std::string name) : _name(name), _type(NULL) {}

HumanB::~HumanB() {}

void	HumanB::attack(void) const {
	std::cout << this->_name << " attacks with his " << this->_type->getType() << std::endl;
}

void	HumanB::setWeapon(Weapon &type) {
	this->_type = &type;
}
