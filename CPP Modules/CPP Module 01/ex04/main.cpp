/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:41:05 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/22 10:46:05 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

std::string	replace(std::string &fileContent, std::string const & s1, std::string const & s2) {
	std::string	finalContent;
	std::string	temp;
	size_t		foundHere;

	foundHere = fileContent.find(s1);
	while (foundHere != std::string::npos) {
		temp = fileContent.substr(0, foundHere);
		fileContent = fileContent.substr((foundHere + s1.length()),
						(fileContent.length() - (foundHere + s1.length())));
		finalContent += temp += s2;
		foundHere = fileContent.find(s1);
	}
	finalContent += fileContent;
	return (finalContent);
}

int	main(int argc, char *argv[]) {
	if (argc == 4)
	{
		std::string const infileName(argv[1]);
		std::string	fileContent;
		std::string const outfileName(infileName + ".replace");
		std::string const s1(argv[2]);
		std::string const s2(argv[3]);

		// CHECK EMPTY STRING
		if (s1.empty() || s2.empty()) {
			std::cout << "\033[0;31mERROR: \033[0msecond and third parameter shoud not be empty." << std::endl;
			return (1);
		}

		// READING
		std::ifstream	input(infileName.c_str());
		if (input) {
			std::string	tempContent;
			while (getline(input, tempContent))
				fileContent += tempContent += '\n';
		}
		else {
			std::cout << "\033[0;31mERROR: \033[0m\"" << infileName << "\" coudn't get opened." << std::endl;
			return (1);
		}

		// WRITING
		std::ofstream	output(outfileName.c_str());
		if (output)
			output << replace(fileContent, s1, s2) << std::endl;
		else {
			std::cout << "\033[0;31mERROR: \033[0m\"" << outfileName << "\" coudn't get opened." << std::endl;
			input.close();
			return (1);
		}
		input.close();
		output.close();
		return (0);
	}
	std::cout << "\033[0;31mUSAGE: \033[0m./replace filename s1 s2." << std::endl;
	return (1);
}
