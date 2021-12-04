/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:00:08 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/21 10:40:27 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void) {
	// First one
	Zombie	One = Zombie("Zed");
	One.announce();

	// Second one
	Zombie	*Two = newZombie("Zoey");
	Two->announce();
	delete Two;

	// Third one
	randomChump("Bonzo");
	return (0);
}
