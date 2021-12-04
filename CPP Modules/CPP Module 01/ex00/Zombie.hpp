/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 09:56:45 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:35:04 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie
{
private:
	std::string	_name;
public:
	Zombie();
	Zombie(std::string);
	~Zombie();
	void	announce(void) const;
};

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);

#endif
