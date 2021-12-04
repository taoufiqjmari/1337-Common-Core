/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:49:59 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/30 18:44:51 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

SCF::SCF() : Form("", 145, 137, "") {
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

SCF::SCF(std::string target) : Form("theForm", 145, 137, target) {
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}

SCF::SCF(SCF const& src) {
	std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
	*this = src;
}

SCF::~SCF() {
	std::cout << "ShrubberyCreationForm default destructor called" << std::endl;
}

SCF	&SCF::operator=(const SCF &rhs) {
	(void)rhs;
	std::cout << "ShrubberyCreationForm equal operator called" << std::endl;
	return (*this);
}

static void	drawTree(std::ofstream &output) {
output << "	            ,@@@@@@@," << std::endl;
output << "       ,,,.   ,@@@@@@/@@,  .oo8888o. " << std::endl;
output << "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o " << std::endl;
output << "   ,%&\%&&%&&%,@@@\\@@@/@@@88\\88888/88' " << std::endl;
output << "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888' " << std::endl;
output << "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88' " << std::endl;
output << "   `&%\\ ` /%&'    |.|        \\ '|8' " << std::endl;
output << "       |o|        | |         | | " << std::endl;
output << "       |.|        | |         | | " << std::endl;
output << "    \\/ ._\\//_/__/  ,\\_//__\\/.  \\_//__/_ " << std::endl;
}

void	SCF::execute(Bureaucrat const & executor) const {
	if (this->getSigned()) {
		if (executor.getGrade() <= this->getExecGrade()) {
			std::string	outfileName = this->getTarget() + "_shrubbery";
			std::ofstream	output(outfileName.c_str());
			if (output)
				drawTree(output);
			output.close();
			return ;
		}
		throw Form::GradeTooLowException();
	}
	throw Form::FormNotSigned();
}
