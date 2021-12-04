/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:26:18 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 12:21:44 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int	main(void) {
	ScavTrap	One("Sagat");
	ScavTrap	Two("Cammy");

	One.attack(Two.getName());
	Two.takeDamage(One.getAttackDamage());
	One.takeDamage(80);
	One.beRepaired(60);
	std::cout << One.getName() << " has " << One.getHitPoints()	<< " hit points " << std::endl;
	Two.guardGate();
	return (0);
}
