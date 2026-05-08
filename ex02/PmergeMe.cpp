/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:57:56 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/09 00:27:00 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

/*
Your program must be able to use a positive integer sequence as an argument
*/
// TODO: start w vector for everthing, do deque later
PmergeMe::PmergeMe(char **elementSequence)
{
    // PARSE AND FILL BOTH CONTAINERS
    fillContainers(elementSequence);
    // --SORT THE MAIN CHAIN (LARGERELEMENTSEQUENCE)--
    // CREATE PAIRS - SORT EACH PAIR INTERNALLY - ADD SMALLER/LARGER ELEMENT OF EACH PAIR TO SMALLERELEMENTSEQUENCE/LARGERELEMENTSEQUENCE
    // CREATE PAIRS AGAIN (FROM LARGERELEMENTSEQUENCE ONLY) AND SO ON
    mergeInsertion(this->vec);

    
    // -- --
    // 3.4: insert the smaller elements from smaller sequence (jacobsthal numbes -> to determine in which order to insert) (use lower_bound)
    // 3.5: handle leftover elements from step 3.1 (insert at end)
    
}



void PmergeMe::mergeInsertion(std::vector<int>& sequence)
{
    // step 3: MERGE INSERTION. start the algo (group in pairs, etc.) (do seperate functions for each container) (all steps for one container)
    std::vector<int>::const_iterator it;
    unsigned int leftoverElement;
    std::vector<std::pair<int, int>> pairs;
    std::vector<int> smallerElementSequence;
    std::vector<int> largerElementSequence;
    // save leftover element (if the size of the vector is uneven)
    if (sequence.size() % 2 != 0)
    {
        leftoverElement = sequence.back(); 
        // std::cout << "leftoverNum = " << leftoverNum << std::endl;  
        sequence.pop_back();
    }
    
    for (it = sequence.begin(); it != sequence.end(); it += 2)
    {
        // --- THIS IS BASICALLY WHERE THE FORD-JOHNSON ALGORITHM STARTS (make pairs from the current sequence, sort the pairs within for left is smaller, right is bigger. now we put them into a new small sequence, and new big sequence again. within the bigger one, create pairs again and so on....)
        // recursion happens to sort the main chain 
        
        
        
        // **** 3.1: group into pairs
        // get two numbers and create/add them as a pair to the pair vector
        unsigned int elementOne = *it;
        std::cout << "elementOne = " << elementOne << std::endl;
        unsigned int elementTwo = *(it + 1);
        std::cout << "elementTwo = " << elementTwo << std::endl;
        pairs.emplace_back(elementOne, elementTwo); // now have to move the pair iterator 2 ahead
        std::cout << "pair = {" << pairs.back().first << ", " << pairs.back().second << "}" << std::endl;
        
        // sort each pair (left should be smaller, right should be bigger) (back() accesses the last element pair in the vector)
        if (!(pairs.back().first < pairs.back().second))
            std::swap(pairs.back().first, pairs.back().second);
        std::cout << "sorted pair = {" << pairs.back().first << ", " << pairs.back().second << "}" << std::endl;
        
        // **** 3.2: "split up" each pair internally (create two sequences: larger elements sequence, smaller elements sequence)
        // put left num in A sequence, and right num in B sequence
        smallerElementSequence.push_back(pairs.back().first);
        std::cout << "smallerElementSequence = " << smallerElementSequence << std::endl;
        largerElementSequence.push_back(pairs.back().second);
        std::cout << "largerElementSequence = " << largerElementSequence << std::endl;
    
    }
    // 3.3: sort larger elements sequence (recursion w same algorithm) (call the mergeInsertion ft again)
    if (!(largerElementSequence.size() <= 1))
        mergeInsertion(largerElementSequence);
    
    
    
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