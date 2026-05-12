/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:57:56 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/11 19:33:46 by pdrettas         ###   ########.fr       */
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

    
    std::vector<int> mainChain = fordJohnsonAlgorithm(this->vec);
    std::cout << "After [vec]: " << mainChain << std::endl;
    
    // -- --
    // 3.4: insert the smaller elements from smaller sequence (jacobsthal numbes -> to determine in which order to insert) (use lower_bound)
    // 3.5: handle leftover elements from step 3.1 (insert at end)
    
}

/*
The process of the below method is called Merge Insertion (The Art of Computer Programming).
This is due to some aspects of merging and some aspects of insertion.

This function starts with the entire original input number sequence
but returns only the resulting main chain (which is 50% the size of the original number sequence and filled with the largest elements)
*/

// --SORT THE MAIN CHAIN (LARGERELEMENTSEQUENCE)--
// CREATE PAIRS - SORT EACH PAIR INTERNALLY - ADD SMALLER/LARGER ELEMENT OF EACH PAIR TO SMALLERELEMENTSEQUENCE/LARGERELEMENTSEQUENCE
// CREATE PAIRS AGAIN (FROM LARGERELEMENTSEQUENCE ONLY) AND SO ON
// TODO: create helper functions for better readability
// largerElementSequence just refers to the larger elements of each pair (not the largest elements in total)
std::vector<int> PmergeMe::fordJohnsonAlgorithm(std::vector<int>& inputSequence) // TODO: potentially pass without reference 
{
    // *********************************step 3: MERGE INSERTION.************************  start the algo (group in pairs, etc.) (do seperate functions for each container) (all steps for one container)
    std::vector<int>::const_iterator it;
    std::vector<std::pair<int, int>> pairs;
    std::vector<int> smallerElementSequence;
    std::vector<int> largerElementSequence;
    
    // each level w recursion, the inputSequence becomes updated (after first recursive call the inputSequence is the largerElementSequnce as input of function)
    if (inputSequence.size() <= 1) // so the recursion doesnt call itself forever (starts unwinding phase)
    {
        std::cout << GREEN << "returned here - top" << RESET << std::endl;
        return inputSequence;
    }
    
    unsigned int leftoverElement;
    bool leftoverFound = false;
    if (inputSequence.size() % 2 != 0) // TODO: potentially put this in a different place (check sorted main chain before insertion)
    {
        leftoverFound = true;
        leftoverElement = inputSequence.back(); 
        // std::cout << "leftoverElement = " << leftoverElement << std::endl;  
        inputSequence.pop_back();
    }
    
    // -- sort input numbers into larger Elements and smaller Elements
    for (it = inputSequence.begin(); it != inputSequence.end(); it += 2)
    {
        std::cout << BLUE << "************** LOOP ITERATION [Pair Creation]  **************" << RESET << std::endl;
        // (make pairs from the current sequence, sort the pairs within for left is smaller, right is bigger. now we put them into a new small sequence, and new big sequence again. within the bigger one, create pairs again and so on....)
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
        std::cout << ORANGE << "$comparison$" << RESET << std::endl;
        
        // **** 3.2: "split up" each pair internally (create two sequences: larger elements sequence, smaller elements sequence)
        // put left num in A sequence, and right num in B sequence
        smallerElementSequence.push_back(pairs.back().first);
        std::cout << "smallerElementSequence = " << smallerElementSequence << std::endl;
        largerElementSequence.push_back(pairs.back().second);
        std::cout << "largerElementSequence = " << largerElementSequence << std::endl;
    }
    
    // enters reaching breaking point (<) at peak when only biggest num left 
    // AND then after if there is only one element (happens every time later when unwinding recursion since numbers get taken and previous level only has the biggest one left each time)
    std::cout << RED << "+++++ RECURSIVE CALL ++++++" << RESET << std::endl;
    largerElementSequence = fordJohnsonAlgorithm(largerElementSequence);















    // ** JACOBSTHAL INSERT SMALLER ELEMENTS INTO MAIN CHAIN WITH JACOBSTHAL (this needs to be in the loop thats up there when inserting smaller elements sequence stuff)
    // when this step happens, at that point the smallerElementSequence is filled w half the numbers from the original sequence


    





    // // ************************************************ jc done 


    // ********************BINARY INSERTION************************** (takes more comparisons) (page 185) (will be replaced by Jacobsthal)
    // insert stuff here from the smallerElementSequence to the largerElementSequence when UNWINDING 
    // for (size_t i = 0; i < smallerElementSequence.size(); i++) // r ? // here should the jacobsthal stuff be entered to optimize insertion order of the small elements
    // {
    //     std::vector<int>::iterator pos = std::lower_bound(largerElementSequence.begin(), largerElementSequence.end(), smallerElementSequence[i]);
    //     largerElementSequence.insert(pos, smallerElementSequence[i]); // inserted at the position that lower_bound found closest
    //     std::cout << "TEST - element of smallerElementSequence was added " << smallerElementSequence[i] << ", in loop iteration " << i << std::endl;
    // }
    // // ************************************************

















    // add leftover element
    if (leftoverFound) // TODO: recheck this, this should not be done in recursion?? only in beginning
    {
        std::vector<int>::iterator pos = std::lower_bound(largerElementSequence.begin(), largerElementSequence.end(), leftoverElement);
        largerElementSequence.insert(pos, leftoverElement); // inserted at the position that lower_bound found closest        
        std::cout << "leftoverElement = " << leftoverElement << std::endl;
    }

    std::cout << GREEN << "returned here - bottom" << RESET << std::endl;
    return largerElementSequence; // TODO: rename to main chain
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