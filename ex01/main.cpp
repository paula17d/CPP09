/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 21:46:58 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/20 23:15:19 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*
Your program must process the Polish mathematical expression 
and output the correct result on the standard output.

If an error occurs during the execution of the program an error message should be
displayed on the standard error.

Your program must be able to handle operations with these tokens: "+ - / *".

You don’t need to handle brackets or decimal numbers.
*/
int main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << RED << "Error: missing argument.\n"
              << "Add an inverted Polish mathematical expression.\n"
              << "Numbers may only range between 0 to 9.\n"
              << "Usage Example: " << argv[0] << " '1 2 * 2 / 2 * 2 4 - +'" << RESET << std::endl;
        return 1;
    }
    
    try 
    {
        RPN rpn(argv[1]);
    }
    catch (std::exception &e)
    {
        std::cerr << RED << e.what() << RESET << std::endl;
    }

    return 0;
}