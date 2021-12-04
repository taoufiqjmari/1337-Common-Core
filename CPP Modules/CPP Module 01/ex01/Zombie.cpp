/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:50:14 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:59:13 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() {}

Zombie::Zombie(std::string name) : _name(name) {}

Zombie::~Zombie() {
	std::cout << this->_name << " is gone!" << std::endl;
}

void	Zombie::announce(void) const {
	std::cout << this->_name << " BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(std::string const & name) {
	this->_name = name;
}
