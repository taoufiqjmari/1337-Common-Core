/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:26:02 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/13 11:58:33 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutantstack.hpp"

int	main() {
	MutantStack<int>    mstack;
	std::cout << "stack is ";
	mstack.empty() ? std::cout << "empty" << std::endl : std::cout << "not empty" << std::endl;
	mstack.push(5);
	mstack.push(17);
	std::cout << "stack is ";
	mstack.empty() ? std::cout << "empty" << std::endl : std::cout << "not empty" << std::endl;
	std::cout << std::endl;

	std::cout << "mstack.size(): " << mstack.size() << std::endl;
	std::cout << "mstack.top(): " << mstack.top() << std::endl;
	std::cout << "popping element." << std::endl;
	mstack.pop();
	std::cout << "mstack.size(): " << mstack.size() << std::endl;
	std::cout << "mstack.top(): " << mstack.top() << std::endl;

	std::cout << std::endl;
	std::cout << "filling with 4 more elements." << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	std::cout << "mstack.size(): " << mstack.size() << std::endl;

	std::cout << std::endl;
	std::cout << "iterating:" << std::endl;
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while(it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	return 0;
}
