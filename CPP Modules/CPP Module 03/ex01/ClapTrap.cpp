/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:23:45 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 12:25:51 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
		std::cout << "ClapTrap name constructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const& src) {
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = src;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap destructor called" << std::endl;
}

ClapTrap	&ClapTrap::operator=(const ClapTrap &rhs)
{
	std::cout << "ClapTrap equal operator called" << std::endl;
	this->_name = rhs._name;
	this->_hitPoints = rhs._hitPoints;
	this->_energyPoints = rhs._energyPoints;
	this->_attackDamage = rhs._attackDamage;
	return (*this);
}

std::string	ClapTrap::getName(void) {
	return (this->_name);
}

unsigned int	ClapTrap::getHitPoints(void) {
	return (this->_hitPoints);
}

unsigned int	ClapTrap::getEnergyPoints(void) {
	return (this->_energyPoints);
}

unsigned int	ClapTrap::getAttackDamage(void) {
	return (this->_attackDamage);
}

void	ClapTrap::attack(std::string const& target) {
	if (this->_hitPoints > 0) {
		std::cout << "ClapTrap " << this->_name << " attack " << target << ", causing " << _attackDamage << " points of damage! " << std::endl;
		this->_hitPoints--;
	}
	else
		std::cout << "No hit points left. Good luck next time." << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (amount > _energyPoints)
		amount = _energyPoints;
	_energyPoints -= amount;
	std::cout << "ClapTrap " << this->_name << " took damage loosing " << amount << " points of damage! " << std::endl;
	std::cout << this->_name << " has " << this->_energyPoints << " energy points" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	_energyPoints += amount;
	std::cout << "ClapTrap " << this->_name << " is repaired gaining " << amount << " points of damage! " << std::endl;
	std::cout << this->_name << " has " << this->_energyPoints << " energy points" << std::endl;
}
