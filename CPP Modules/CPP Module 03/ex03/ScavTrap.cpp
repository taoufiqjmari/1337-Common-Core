/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:30:50 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 14:54:54 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() {
	std::cout << "ScavTrap default constructor called" << std::endl;
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
}

ScavTrap::ScavTrap(std::string name) {
	std::cout << "ScavTrap name constructor called" << std::endl;
	this->_name = name;
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
}

ScavTrap::ScavTrap(ScavTrap const& src) {
	std::cout << "ScavTrap copy constructor called" << std::endl;
	*this = src;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap destructor called" << std::endl;
}

ScavTrap	&ScavTrap::operator=(const ScavTrap &rhs)
{
	std::cout << "ScavTrap equal operator called" << std::endl;
	this->_name = rhs._name;
	this->_hitPoints = rhs._hitPoints;
	this->_energyPoints = rhs._energyPoints;
	this->_attackDamage = rhs._attackDamage;
	return (*this);
}

void	ScavTrap::attack(std::string const& target) {
	if (this->_hitPoints > 0) {
		std::cout << "ScavTrap " << this->_name << " attack " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
		this->_hitPoints--;
	}
	else
		std::cout << "No hit points left. Good luck next time." << std::endl;
}

void	ScavTrap::guardGate() {
	std::cout << "ScavTrap " << this->_name << " has enterred is Gate keeper mode" << std::endl;
}
