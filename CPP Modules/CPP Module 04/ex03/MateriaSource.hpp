/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:18:38 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:32:17 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
private:
    AMateria *_inventory[4];

public:
    MateriaSource();
    MateriaSource(MateriaSource const &);
    ~MateriaSource();

    MateriaSource &operator=(const MateriaSource &);

    void learnMateria(AMateria *);
    AMateria *createMateria(std::string const &type);
};

#endif
