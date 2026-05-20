/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:57:56 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/20 03:01:50 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

/*
Your program must be able to use a positive integer sequence as an argument
*/
// TODO: start w vector for everthing, do deque later
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
    std::vector<unsigned int> mainChain = fordJohnsonAlgorithm(this->vec);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    
    
    std::cout << "After [vec]: " << mainChain << std::endl;
    std::cout << "Time to process a range of " << mainChain.size() << " elements with std::vector : " << elapsed.count() << " us" << std::endl;
    
    if (!std::is_sorted(mainChain.begin(), mainChain.end()))
        std::cout << "--NOT SORTED--" << std::endl;
    else
        std::cout << "--SORTED--" << std::endl;

        
    // --SORT W DEQUE CONTAINER
    // start = std::chrono::high_resolution_clock::now();
    // std::deque<int> mainChain = fordJohnsonAlgorithm(this->deq);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    
    // std::cout << "After [deque]: " << mainChain << std::endl;
    // std::cout << "Time to process a range of " << mainChain.size() << " elements with std::deque : " << elapsed.count() << " us" << std::endl;

    // if (!std::is_sorted(mainChain.begin(), mainChain.end()))
    //     std::cout << "--NOT SORTED--" << std::endl;
    // else
    //     std::cout << "--SORTED--" << std::endl;
}

// TODO: edit these accordingly
PmergeMe::PmergeMe(const PmergeMe& other) 
{
    vec = other.vec;
    deq = other.deq;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
    if (this != &other) 
    {
        vec = other.vec;
        deq = other.deq;
    }
    
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

        unsigned int num;
        try 
        {
            unsigned long value = std::stoul(s); // stoul does throw std::out_of_range(); therefore catch it here for own error

            if (value > INT_MAX)
                throw std::runtime_error("Error: number out of range.");

            num = static_cast<unsigned int>(value);
        }
        catch (const std::exception&)
        {
            throw std::runtime_error("Error: number out of range.");
        }

        // std::cout << "num stol = " << num << std::endl;

        // step 2: store them all in a container (once in vec, once in deque)
        vec.push_back(num);
        deq.push_back(num);
        i++;
    } 
}

std::ostream &operator<<(std::ostream &out, const std::vector<unsigned int> &vec)
{
    std::vector<unsigned int>::const_iterator it;

    for (it = vec.begin(); it != vec.end(); it++)
    {
        out << *it << " ";
    }
    
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::deque<unsigned int> &deque)
{
    std::deque<unsigned int>::const_iterator it;

    for (it = deque.begin(); it != deque.end(); it++)
    {
        out << *it << " ";
    }
    
    return out;
}
