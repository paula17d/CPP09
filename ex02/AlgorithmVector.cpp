/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgorithmVector.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 20:18:31 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/22 00:32:43 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

vector PmergeMe::fordJohnsonAlgorithm(vector &inputSequence)
{
    vectorPair pairs;
    vector pendElements;
    vector mainChain;
    unsigned int leftoverElement;
    bool leftoverFound = false;
    vector jacobsthalSequence; 
    vector insertionOrder;
    
    if (inputSequence.size() <= 1) 
        return inputSequence;
    
    extractLeftoverElement(inputSequence, leftoverElement, leftoverFound);
    createAndSortPairs(inputSequence, pairs, pendElements, mainChain);

    mainChain = fordJohnsonAlgorithm(mainChain); 

    calculateJacobsthalSequence(jacobsthalSequence, pendElements);
    generateJacobsthalInsertionOrder(insertionOrder, jacobsthalSequence, pendElements);
    insertPendElementsIntoMainChain(insertionOrder, pairs, pendElements, mainChain);
    addLeftoverElement(leftoverElement, leftoverFound, mainChain);

    return mainChain;
}


// --HELPER FUNCTIONS--

void PmergeMe::extractLeftoverElement(vector &inputSequence, unsigned int &leftoverElement, bool &leftoverFound)
{
    if (inputSequence.size() % 2 != 0)
    {
        leftoverFound = true;
        leftoverElement = inputSequence.back(); 
        inputSequence.pop_back();
    }
}

// sort input numbers into larger Elements and smaller Elements (one pair per loop)
void PmergeMe::createAndSortPairs(vector &inputSequence, vectorPair &pairs, vector &pendElements, vector &mainChain)
{
    vector::const_iterator it;
    
    for (it = inputSequence.begin(); it != inputSequence.end(); it += 2)
    {
        unsigned int elementOne = *it;
        unsigned int elementTwo = *(it + 1);
        pairs.emplace_back(elementOne, elementTwo); 
        
        if (!(pairs.back().first < pairs.back().second))
            std::swap(pairs.back().first, pairs.back().second);
        
        pendElements.push_back(pairs.back().first);
        mainChain.push_back(pairs.back().second);
    }
}

/*
- generate the amount of jacobsthal numbers needed
- jt formula needs two numbers (0, 1) as base to calculate next numbers in loop
- building the sequence number by number (0, 1, 1, 3, 5, 11, ...) (without 0, 1)
*/
void PmergeMe::calculateJacobsthalSequence(vector &jacobsthalSequence, vector &pendElements)
{   
    unsigned int prevPrevNum = 0;
    unsigned int prevNum = 1;

    while (true)
    {
        unsigned int nextJtNum = prevNum + 2 * prevPrevNum;
        if (nextJtNum > static_cast<unsigned int>(pendElements.size())) 
            break;

        jacobsthalSequence.push_back(nextJtNum);

        prevPrevNum = prevNum;
        prevNum = nextJtNum;
    }
}

/*
- (1.       3, 2.     5, 4.     11, 10, 9, 8, 7, 6.)
- start at current Jt num, go backwards, until previous jacobsthal num -> for (int j = 5; j > 3; --j) add 4 (so 1 3 2 5 4)
- since jt only defines blocks (1, 2-3, 4-5, 6-11,...), it is still possible to have 8 elements
-   so insert everything thats missing depending on sequence size, ex. 1 3 2 5 4 8 7 6 (even tho next block would be at 11)
*/
void PmergeMe::generateJacobsthalInsertionOrder(vector &insertionOrder, vector &jacobsthalSequence, vector &pendElements)
{
    unsigned int previousJtNum = 1;

    if (!pendElements.empty())
        insertionOrder.push_back(1);

    for (size_t i = 0; i < jacobsthalSequence.size(); ++i)
    {
        unsigned int currentJtNum = jacobsthalSequence[i];

        for (unsigned int j = currentJtNum; j > previousJtNum; --j) 
            insertionOrder.push_back(j);

        previousJtNum = currentJtNum;
    }

    for (unsigned int j = static_cast<unsigned int>(pendElements.size()); j > previousJtNum; --j)
        insertionOrder.push_back(j);
}

/*
- the order that needs to be implemented (1, 3, 2, 5, 4,  ...)
- using jacobsthal and binary search together (less comparisons overall)

- the index in the pendElements is the same index in vec pairs for the same number
- look for position of largerPairPartner in mainChain
- loop goes through jacobsthal insertion order (1, 3, 2, 5, 4, ...)
*/
void PmergeMe::insertPendElementsIntoMainChain(vector &insertionOrder, vectorPair &pairs, vector &pendElements, vector &mainChain)
{
    for (int i = 0; i < static_cast<int>(insertionOrder.size()); i++)
    {
        int index = insertionOrder[i] - 1;
        unsigned int elementToInsert = pendElements[index]; 

        unsigned int largerPairPartner = pairs[index].second;
        
        auto positionLargerPairPartner = std::find(mainChain.begin(), mainChain.end(), largerPairPartner); 
        auto positionElementToInsert = std::lower_bound(mainChain.begin(), positionLargerPairPartner, elementToInsert);
        mainChain.insert(positionElementToInsert, elementToInsert);
    }
}

void PmergeMe::addLeftoverElement(unsigned int &leftoverElement, bool &leftoverFound, vector &mainChain)
{
    if (leftoverFound)
    {
        vector::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), leftoverElement);
        mainChain.insert(pos, leftoverElement);  
    }
}
