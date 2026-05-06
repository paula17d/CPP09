/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:51:02 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/06 18:23:14 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main (int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: missing arguments.\n"
              << "Numbers may only be positive.\n"
              << "Usage Example: " << argv[0] << " '4 2 8 5 9 7'" << std::endl;
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