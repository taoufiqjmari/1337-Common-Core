/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:52:48 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 11:04:36 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
private:
	std::string	_name;
	Weapon		*_type;
public:
	HumanB();
	HumanB(std::string);
	~HumanB();
	void	attack(void) const;
	void	setWeapon(Weapon &);
};

#endif
