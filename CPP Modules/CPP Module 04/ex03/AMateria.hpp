/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:04:07 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:30:35 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <iostream>
#include "ICharacter.hpp"

class ICharacter;

class AMateria
{
protected:
    std::string _type;

public:
    AMateria();
    AMateria(std::string const &type);
    AMateria(AMateria const &);
    virtual ~AMateria();

    virtual AMateria &operator=(const AMateria &);

    std::string const &getType() const; // Returns the materia type

    virtual AMateria *clone() const = 0;
    virtual void use(ICharacter &target) = 0;
};

#endif
