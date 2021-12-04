/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:47:10 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/21 12:53:03 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

class HumanA
{
private:
	std::string	_name;
	Weapon		&_type;
public:
	HumanA(std::string, Weapon &);
	~HumanA();
	void	attack(void) const;
};

#endif
