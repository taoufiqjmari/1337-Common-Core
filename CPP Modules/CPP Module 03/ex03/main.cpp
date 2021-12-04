/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:26:18 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 14:36:36 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int	main(void) {
	DiamondTrap	One("Sagat");
	DiamondTrap	Two("Cammy");

	One.attack(Two.getName());
	Two.takeDamage(One.getAttackDamage());
	One.takeDamage(80);
	One.beRepaired(60);
	std::cout << One.getName() << " has " << One.getHitPoints()	<< " hit points " << std::endl;
	One.guardGate();
	Two.highFivesGuys();
	One.whoAmI();
	return (0);
}
