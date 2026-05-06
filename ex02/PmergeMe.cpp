/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:57:56 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/06 18:35:25 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

/*
Your program must be able to use a positive integer sequence as an argument
*/
PmergeMe::PmergeMe(char **numSequence)
{
    (void) numSequence;
    
    // step 1: parse char** to make sure input is all positive integers (argv[i] = one number)
    int i = 1;
    while (numSequence[i])
    {
        // check if string (atoi)
        unsigned int num = std::stoi(numSequence[i]); // if 26a, stoi returns 26
        // TODO: go thru string and use isdigit for each [i] in a loop instead of stoi -> easier
        
        if ()
            throw std::invalid_argument("Error: not a positive number.");

        i++;
    }

    
    // step 2: store them all in a container (once in vec, once in deque)
    
    

    // step 3: start the algo (group in pairs, etc.)


    
}

// TODO: edit these accordingly
PmergeMe::PmergeMe(const PmergeMe& other) 
{
    (void) other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
    if (this != &other) 
    {}
    
    return *this;
}

PmergeMe::~PmergeMe()
{}