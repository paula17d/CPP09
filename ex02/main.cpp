/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:51:02 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/17 14:22:48 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main (int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: missing arguments.\n"
              << "Enter a sequence of only positive numbers.\n"
              << "Usage Example: " << argv[0] << " '5 2 6 9 4 3 7'" << std::endl;
        return 1;
    }

    try
    {
        PmergeMe pm(argv);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    // std::cout << argv[1] << std::endl;
    // std::cout << argv[2] << std::endl;
    // std::cout << argv[3] << std::endl;


    return 0;
}