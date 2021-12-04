/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 09:55:47 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:35:20 by tjmari           ###   ########.fr       */
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
