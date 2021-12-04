/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:20:40 by tjmari            #+#    #+#             */
/*   Updated: 2021/11/04 12:03:02 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

struct Data {
	char	C;
	int		I;
	float	F;
	double	D;
	std::string	S;
};

uintptr_t	serialize(Data *ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data	*deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data *>(raw));
}

int	main(void) {
	struct	Data	beforeData;
	struct	Data	*afterData;
	uintptr_t		ip;

	beforeData.C = 'a';
	beforeData.I = 25;
	beforeData.F = 5.5f;
	beforeData.D = 30.5;
	beforeData.S = "Execute it!";

	std::cout << "ORIGINAL DATA" << std::endl;
	std::cout << beforeData.C << std::endl;
	std::cout << beforeData.I << std::endl;
	std::cout << beforeData.F << std::endl;
	std::cout << beforeData.D << std::endl;
	std::cout << beforeData.S << std::endl;
	std::cout << "------------------------" << std::endl;

	ip = serialize(&beforeData);
	std::cout << "uintptr_t: "<< ip << std::endl;
	afterData = deserialize(ip);

	std::cout << "------------------------" << std::endl;
	std::cout << "DATA AFTER SERIALIZATION" << std::endl;
	std::cout << afterData->C << std::endl;
	std::cout << afterData->I << std::endl;
	std::cout << afterData->F << std::endl;
	std::cout << afterData->D << std::endl;
	std::cout << afterData->S << std::endl;
	return (0);
}
