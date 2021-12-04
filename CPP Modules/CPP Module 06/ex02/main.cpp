/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:46:37 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/04 13:48:58 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base	*generate(void) {
	int randNum = rand() % (MAX - MIN + 1) + MIN;

	if (randNum == 1)
		return (new A());
	else if (randNum == 2)
		return (new B());
	else
		return (new C());
}

void	identify(Base *p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else
		std::cout << "C" << std::endl;
}

void	identify(Base &p) {
	Base	ref;

	try {
		ref = dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	} catch (std::bad_cast &e) {}

	try {
		ref = dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
	} catch (std::bad_cast &e) {}

	try {
		ref = dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
	} catch (std::bad_cast &e) {}
}

int	main(void) {
	Base	*p;

	srand(time(0));
	p = generate();
	identify(p);
	
	std::cout << "-" << std::endl;
	Base	&ref(*p);
	identify(ref);
}
