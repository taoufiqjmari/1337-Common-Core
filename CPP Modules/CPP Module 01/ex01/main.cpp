/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:50:29 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/21 11:10:32 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void) {
	int		N;
	Zombie	*Horde;

	N = 5;
	Horde = ZombieHorde(N, "Mailo");
	for (int i(0); i < N; i++)
		Horde[i].announce();
	delete [] Horde;
	return (0);
}
