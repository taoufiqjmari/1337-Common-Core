/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:52:31 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/21 11:06:57 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	*ZombieHorde(int N, std::string name) {
	Zombie	*Horde = new Zombie[N];

	for(int i(0); i < N; i++)
		Horde[i].setName(name);
	return (Horde);
}
