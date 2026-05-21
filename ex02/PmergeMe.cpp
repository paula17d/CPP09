/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:57:56 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/22 00:41:45 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(char **inputSequence)
{
    parseInputAndFillContainers(inputSequence);
    
    sortContainerAndMeasureTime(this->vec, "std::vector");
    sortContainerAndMeasureTime(this->deq, "std::deque");
}

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
            unsigned long value = std::stoul(s);

            if (value > UINT_MAX)
                throw std::runtime_error("Error: number out of range.");

            num = static_cast<unsigned int>(value);
        }
        catch (const std::exception&)
        {
            throw std::runtime_error("Error: number out of range.");
        }

        // step 2: store them all in a container (once in vec, once in deque)
        vec.push_back(num);
        deq.push_back(num);
        i++;
    } 
    
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
        if (i == 20)
        {
            std::cout << "[...]";
            break;
        }
    }
    std::cout << std::endl << std::endl;
}

template <typename Container>
void PmergeMe::sortContainerAndMeasureTime(Container &c, const std::string& containerName)
{
    std::chrono::high_resolution_clock::time_point	start;
	std::chrono::high_resolution_clock::time_point	end;
	std::chrono::duration<double, std::micro>		elapsed;
    const size_t                                    inputSize = c.size();
    
    start = std::chrono::high_resolution_clock::now();
    
    Container sortedSequence = fordJohnsonAlgorithm(c);
    
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    
    printSortedSequence(sortedSequence, elapsed, inputSize, containerName);
}

template <typename Container>
void PmergeMe::printSortedSequence(const Container &sortedSequence, std::chrono::duration<double, std::micro> &elapsed, const size_t &inputSize, const std::string& containerName)
{   
    std::cout << "After: ";
    for (size_t i = 0; i < sortedSequence.size(); i++)
    {
        std::cout << sortedSequence[i] << " ";
        if (i == 20)
        {
            std::cout << "[...]";
            break;
        }
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << inputSize << \
        " elements with [" << containerName << "] : " << \
        elapsed.count() << " us" << std::endl;

    if (!std::is_sorted(sortedSequence.begin(), sortedSequence.end()))
        std::cout << RED << "Sequence is not sorted." << RESET << std::endl;
    else
        std::cout << GREEN << "Sequence has successfully been sorted." << RESET << std::endl;    
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& out, const vector& vec)
{
    std::vector<unsigned int>::const_iterator it;

    for (it = vec.begin(); it != vec.end(); it++)
    {
        out << *it << " ";
    }
    
    return out;
}

std::ostream& operator<<(std::ostream& out, const deque& deque)
{
    std::deque<unsigned int>::const_iterator it;

    for (it = deque.begin(); it != deque.end(); it++)
    {
        out << *it << " ";
    }
    
    return out;
}
