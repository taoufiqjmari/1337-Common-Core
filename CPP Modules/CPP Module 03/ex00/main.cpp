/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:26:18 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 11:22:56 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void) {
	ClapTrap	One("Ryu");
	ClapTrap	Two("Chun-Li");

	One.attack(Two.getName());
	Two.takeDamage(One.getAttackDamage());
	One.takeDamage(800);
	One.beRepaired(60);
	std::cout << One.getName() << " has " << One.getHitPoints()	<< " hit points " << std::endl;
	return (0);
}
