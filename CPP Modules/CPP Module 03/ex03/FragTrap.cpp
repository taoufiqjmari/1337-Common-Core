/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:15:28 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 14:55:08 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() {
	std::cout << "FragTrap default constructor called" << std::endl;
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(std::string name) {
	std::cout << "FragTrap name constructor called" << std::endl;
	this->_name = name;
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(FragTrap const& src) {
	std::cout << "FragTrap copy constructor called" << std::endl;
	*this = src;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap	&FragTrap::operator=(const FragTrap &rhs)
{
	std::cout << "FragTrap equal operator called" << std::endl;
	this->_name = rhs._name;
	this->_hitPoints = rhs._hitPoints;
	this->_energyPoints = rhs._energyPoints;
	this->_attackDamage = rhs._attackDamage;
	return (*this);
}

void	FragTrap::attack(std::string const& target) {
	if (this->_hitPoints > 0) {
		std::cout << "FragTrap " << this->_name << " attack " << target << ", causing " << _attackDamage << " points of damage! " << std::endl;
		this->_hitPoints--;
	}
	else
		std::cout << "No hit points left. Good luck next time." << std::endl;
}

void	FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap " << this->_name << ": HIGH FIVE?" << std::endl;
}
