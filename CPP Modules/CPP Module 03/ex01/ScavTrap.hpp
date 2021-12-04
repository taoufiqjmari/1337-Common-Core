/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:28:02 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/26 14:55:37 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {

public:
	ScavTrap();
	ScavTrap(std::string);
	ScavTrap(ScavTrap const&);
	~ScavTrap();

	ScavTrap	&operator=(const ScavTrap &);

	void	attack(std::string const&target);
	void	guardGate();
};

#endif
