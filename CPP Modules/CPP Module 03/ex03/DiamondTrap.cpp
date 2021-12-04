/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:09:57 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 14:55:22 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() {}

DiamondTrap::DiamondTrap(std::string name) {
	std::cout << "DiamondTrap name constructor called" << std::endl;
	this->_name = name;
	ClapTrap::_name = name + "_clap_name";
	this->_hitPoints = FragTrap::getHitPoints();
	this->_energyPoints = ScavTrap::getEnergyPoints();
	this->_attackDamage = FragTrap::getAttackDamage();
}

DiamondTrap::DiamondTrap(DiamondTrap const& src) {
	std::cout << "DiamondTrap copy constructor called" << std::endl;
	*this = src;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap destructor called" << std::endl;
}

DiamondTrap	&DiamondTrap::operator=(const DiamondTrap &rhs)
{
	std::cout << "DiamondTrap equal operator called" << std::endl;
	this->_name = rhs._name;
	this->_hitPoints = rhs._hitPoints;
	this->_energyPoints = rhs._energyPoints;
	this->_attackDamage = rhs._attackDamage;
	return (*this);
}

void	DiamondTrap::attack(std::string const& target) {
	ScavTrap::attack(target);
}

void	DiamondTrap::whoAmI() {
	std::cout << "name " << this->_name << std::endl;
	std::cout << "clapTrap name " << ClapTrap::getName() << std::endl;
}
