/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:22:37 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 11:16:59 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

class ClapTrap
{
private:
	std::string		_name;
	unsigned int	_hitPoints;
	unsigned int	_energyPoints;
	unsigned int	_attackDamage;
public:
	ClapTrap();
	ClapTrap(std::string);
	ClapTrap(ClapTrap const&);
	~ClapTrap();

	ClapTrap	&operator=(const ClapTrap &);

	std::string		getName(void);
	unsigned int	getHitPoints(void);
	unsigned int	getEnergyPoints(void);
	unsigned int	getAttackDamage(void);

	void	attack(std::string const&target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};

#endif
