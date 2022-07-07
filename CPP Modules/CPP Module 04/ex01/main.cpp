/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:22:37 by tjmari            #+#    #+#             */
/*   Updated: 2022/07/07 00:29:20 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	Animal *array[2];
	array[0] = new Dog();
	array[1] = new Cat();

	Dog Bear;
	{
		Dog tmp = Bear;
	}
	std::cout << Bear.getIdea() << std::endl;
	for (int i(0); i < 2; i++)
		delete array[i];
}
