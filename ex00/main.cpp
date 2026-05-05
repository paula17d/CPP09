/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:11:02 by pauladretta       #+#    #+#             */
/*   Updated: 2026/05/02 23:18:07 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*
- data.csv is the reference database (provided by subject) (first database)
- input.csv (is the input argument) (second database)
*/
int main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: no valid input file provided.\n"
              << "Usage Example: " << argv[0] << " input.csv" << std::endl;
        return 1;
    }

    BitcoinExchange bc(argv[1]); // parses input.csv

    return 0;
}