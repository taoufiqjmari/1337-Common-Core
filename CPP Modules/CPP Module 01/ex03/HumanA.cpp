/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:46:57 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/21 12:53:10 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &type) : _name(name), _type(type) {}

HumanA::~HumanA() {}

void	HumanA::attack(void) const {
	std::cout << this->_name << " attacks with his " << this->_type.getType() << std::endl;
}
