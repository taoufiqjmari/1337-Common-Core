/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:13:34 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:30:58 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICharacter.hpp"

class Character : public ICharacter
{
private:
    std::string _name;
    AMateria *_inventory[4];
    AMateria *_floor[4];

public:
    Character();
    Character(std::string);
    Character(Character const &);
    ~Character();

    Character &operator=(const Character &);

    std::string const &getName() const;
    void equip(AMateria *);
    void unequip(int idx);
    void use(int idx, ICharacter &target);
};
