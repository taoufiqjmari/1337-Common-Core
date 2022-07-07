/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:22:37 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:27:36 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	const Animal *meta = new Animal("bird");
	const Animal *j = new Dog();
	const Animal *i = new Cat();

	std::cout << meta->getType() << " " << std::endl;
	meta->makeSound();
	std::cout << j->getType() << " " << std::endl;
	j->makeSound();
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();

	delete meta;
	delete i;
	delete j;

	std::cout << "_____________________________________" << std::endl;

	const WrongAnimal *meta2 = new WrongAnimal("bird");
	const WrongAnimal *i2 = new WrongCat();

	std::cout << meta2->getType() << " " << std::endl;
	meta2->makeSound();
	std::cout << i2->getType() << " " << std::endl;
	i2->makeSound();

	delete meta2;
	delete i2;
	return (0);
}
