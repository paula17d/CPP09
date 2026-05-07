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
// TODO: start w vector for everthing, do deque later
PmergeMe::PmergeMe(char **numSequence)
{
    // PARSE AND FILL BOTH CONTAINERS
    fillContainers(numSequence);

    // step 3: start the algo (group in pairs, etc.) (do seperate functions for each container) (all steps for one container)
    // 3.1: group into pairs (need to access first element from beginning first? bc of leftover at end or does it matter?)

    // do the same loop for each pair (std::make_pair( , ), then create two chains where each smaller/larger element is being put into (int array))
    // start w one pair first (no loop yet)

    std::vector<int>::const_iterator it;
    for (it = vec.begin(); it != vec.end(); it++)
    {
        
        // TODO: edge case: if only one element left, dont do make_pair (leave it but save it potentially)

        // get two numbers and create a pair
        unsigned int numOne = *it;
        std::cout << "numOne = " << numOne << std::endl;
        it++;
        if (it == vec.end())
            break;
        unsigned int numTwo = *it;
        std::cout << "numTwo = " << numTwo << std::endl;
        std::make_pair(numOne, numTwo);

        // sort each pair (left is smaller, right is bigger)




        // put left num in A sequence, and right num in B sequence



    }










    // 3.2: sort each pair internally (create two sequences: larger elements sequence, smaller elements sequence)
    // 3.3: sort larger elements sequence (recursion w same algorithm)
    // 3.4: insert the smaller elements from smaller sequence (jacobsthal numbes -> to determine in which order to insert) (use lower_bound)
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
        deque.push_back(num);
        i++;
    }
    
    // PRINT EACH CONTAINER
    std::cout << "Before [vec]: " << vec << std::endl;
    std::cout << "Before [deque]: " << deque << std::endl;
    
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

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec)
{
    std::vector<int>::const_iterator it;

    for (it = vec.begin(); it != vec.end(); it++)
    {
        out << *it << " ";
    }
    
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::deque<int> &deque)
{
    std::deque<int>::const_iterator it;

    for (it = deque.begin(); it != deque.end(); it++)
    {
        out << *it << " ";
    }
    
    return out;
}