/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:57:56 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/18 01:23:36 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

/*
Your program must be able to use a positive integer sequence as an argument
*/
// TODO: start w vector for everthing, do deque later
// TODO: fix stoul error when entering a too large number
// TODO: change the printing structure at end like in subject described
PmergeMe::PmergeMe(char **inputSequence)
{
    parseInputAndFillContainers(inputSequence);
    std::cout << "Before: " << vec << std::endl;
    
    std::chrono::high_resolution_clock::time_point	start;
	std::chrono::high_resolution_clock::time_point	end;
	std::chrono::duration<double, std::micro>		elapsed;
    
    // TODO: put each container section in a "helper" function again and call it Sort or sth (less messy w all the time & print stuff together) -> measureTimeAndSortSequence
    // --SORT W VECTOR CONTAINER
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> mainChain = fordJohnsonAlgorithm(this->vec);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    
    std::cout << "After [vec]: " << mainChain << std::endl;
    std::cout << "Time to process a range of " << mainChain.size() << " elements with std::vector : " << elapsed.count() << " us" << std::endl;
    
    // --SORT W DEQUE CONTAINER
    // start = std::chrono::high_resolution_clock::now();
    // std::deque<int> mainChain = fordJohnsonAlgorithm(this->deq);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    
    // std::cout << "After [deque]: " << mainChain << std::endl;
    // std::cout << "Time to process a range of " << mainChain.size() << " elements with std::deque : " << elapsed.count() << " us" << std::endl;
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

void PmergeMe::parseInputAndFillContainers(char **inputSequence)
{
    // step 1: parse char** to make sure input is all positive integers (argv[i] = one number)
    int i = 1;
    while (inputSequence[i])
    {
        std::string s = inputSequence[i];

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
        deq.push_back(num);
        i++;
    }
}

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
