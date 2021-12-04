/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:34:55 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 14:55:13 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
private:
	std::string	_name;
public:
	DiamondTrap();
	DiamondTrap(std::string);
	DiamondTrap(DiamondTrap const&);
	~DiamondTrap();

	DiamondTrap	&operator=(const DiamondTrap &);

	void	attack(std::string const&target);
	void	whoAmI();
};

#endif
