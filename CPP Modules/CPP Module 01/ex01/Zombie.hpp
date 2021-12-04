/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:48:22 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:59:10 by tjmari           ###   ########.fr       */
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
	void	setName(std::string const & name);
};

Zombie	*ZombieHorde(int N, std::string name);

#endif
