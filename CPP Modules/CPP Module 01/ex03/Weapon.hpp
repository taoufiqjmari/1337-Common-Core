/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:37:44 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:26:08 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon
{
private:
	std::string	_type;
public:
	Weapon();
	Weapon(std::string);
	~Weapon();
	void		setType(std::string);
	std::string const&	getType(void) const;
};

#endif
