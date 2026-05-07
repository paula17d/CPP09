/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:57:56 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/07 15:24:59 by pdrettas         ###   ########.fr       */
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
    // PARSE AND FILL BOTH CONTAINERS
    fillContainers(numSequence);

    // step 3: start the algo (group in pairs, etc.) (do seperate functions for each container) (all steps for one container)
    // 3.1: group into pairs (need to access first element from beginning first? bc of leftover at end or does it matter?)
    // 3.2: sort each pair internally (create two sequences: larger elements sequence, smaller elements sequence)
    // 3.3: sort larger elements sequence (recursion w same algorithm)
    // 3.4: insert the smaller elements from smaller sequence (jacobsthal numbes -> to determine in which order to insert)
    // 3.5: handle leftover elements from step 3.1 (insert at end)











    
   
}

void PmergeMe::fillContainers(char **numSequence)
{
    // step 1: parse char** to make sure input is all positive integers (argv[i] = one number)
    int i = 1;
    while (numSequence[i])
    {
        std::string s = numSequence[i];

        if (s.empty())
            throw std::invalid_argument("Error: empty argument.");

        // check if every character is a digit
        for (size_t j = 0; j < s.size(); ++j)
        {
            if (!std::isdigit(static_cast<unsigned char>(s[j])))
                throw std::invalid_argument("Error: not a valid positive number.");
        }

        // convert from string to int
        unsigned int num = std::stoul(s); // TODO: include an error check if int exceeds MAX w stou
        // std::cout << num << std::endl;
        
        // step 2: store them all in a container (once in vec, once in deque)
        vec.push_back(num);
        // std::cout << vec[i - 1] << std::endl;
        deque.push_back(num);
        // std::cout << deque[i - 1] << std::endl;
        
        i++;
    }
    
    // PRINT EACH CONTAINER (operator overloading)
    std::cout << "Before [vec]: " << vec << std::endl;
    std::cout << "Before [vec]: " << deque << std::endl;
    
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