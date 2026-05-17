/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:57:56 by pdrettas          #+#    #+#             */
/*   Updated: 2026/05/17 19:36:44 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

/*
Your program must be able to use a positive integer sequence as an argument
*/
// TODO: start w vector for everthing, do deque later
// TODO: add time measurement (start in vec function and in deque function)
// TODO: fix stoul error when entering a too large number
PmergeMe::PmergeMe(char **elementSequence)
{
    // PARSE AND FILL BOTH CONTAINERS
    fillContainers(elementSequence);

    std::vector<int> mainChain = fordJohnsonAlgorithm(this->vec);
    std::cout << "After [vec]: " << mainChain << std::endl;
    
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
    std::cout << RED << "+++++ RECURSIVE CALL +++++" << RESET << std::endl;
    largerElementSequence = fordJohnsonAlgorithm(largerElementSequence);



    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // ** JACOBSTHAL INSERT SMALLER ELEMENTS INTO MAIN CHAIN WITH JACOBSTHAL (this needs to be in the loop thats up there when inserting smaller elements sequence stuff)
    // when this step happens, at that point the smallerElementSequence is filled w half the numbers from the original sequence
    // need to remember pairs (which number from pend chain was paired up in beginning)

    
    // @@@@ part ONE [decide order of insertion]
    // generate the amount of jacobsthal numbers needed
    std::vector<int> jacobsthalSequence; 
    
    int prevPrevNum = 0; // jt formula needs those two numbers (0, 1) as base to calculate next numbers in following loop
    int prevNum = 1;

    // building the sequence number by number (0, 1, 1, 3, 5, 11, ...) (without 0, 1) (basically defining ranges (each num is a starting point))
    while (true)
    {
        int nextJtNum = prevNum + 2 * prevPrevNum; // b -> previous number, a -> previous previous number
        if (nextJtNum > static_cast<int>(smallerElementSequence.size())) // .
            break;

        jacobsthalSequence.push_back(nextJtNum); // add next number to JT sequence

        prevPrevNum = prevNum;
        prevNum = nextJtNum;
    }
    std::cout << LIGHT_GREEN << "jacobsthalSequence: " << jacobsthalSequence << RESET << std::endl;

    // take numbers from above and with that insert each range in reverse (1.       3, 2.     5, 4.     11, 10, 9, 8, 7, 6.)
    std::vector<int> insertionOrder;
    int previousJtNum = 1;

    for (size_t i = 0; i < jacobsthalSequence.size(); ++i)
    {
        int currentJtNum = jacobsthalSequence[i];

        for (int j = currentJtNum; j > previousJtNum; --j) // start at current Jt num, go backwards, until previous jacobsthal num -> for (int j = 5; j > 3; --j) add 4 (so 1 3 2 5 4)
            insertionOrder.push_back(j);

        if (currentJtNum == 1)
            insertionOrder.push_back(1);

        previousJtNum = currentJtNum;
    }

    for (int j = static_cast<int>(smallerElementSequence.size()); j > previousJtNum; --j) // since jt only defines blocks (1, 2-3, 4-5, 6-11,...) but possible to have 8 elements so insert everything thats missing depending on sequence size // ex. 1 3 2 5 4 8 7 6 (even tho next block would be at 11)
        insertionOrder.push_back(j);
    
    std::cout << LIGHT_GREEN << "insertionOrder: " << insertionOrder << RESET << std::endl;

    
    // @@@@ part TWO [do actual sorting & insertion]
    // --NOW: that i got the order that needs to be implemented (1, 3, 2, 5, 4,  ...) ,
    //  match them w the index + 1 from the smallerElementSequence!
    for (int i = 0; i < static_cast<int>(insertionOrder.size()); i++)
    {
        int findIndex = insertionOrder[i];
        int valueToInsert = smallerElementSequence[findIndex - 1]; // this needs to be inserted in he largerElemenSequence/mainChain (with .insert)
        // (-1) bc ex. looking for third element in smallerElementSequence which has index 2
        std::cout << "next Element to be inserted into mainChain: " << valueToInsert << std::endl;

        // find the pair partner of the smallerElementSequence Number in the LargerElementSequence (still preserved when recursion unwinding happens)
        // TODO: fix pair look up -> currently broken
        int pairLargerPartner = pairs[valueToInsert].second; // TODO: doesnt work when there are duplicate numbers! (subject error handling)
        std::cout << "pairLargerPartner: " << pairLargerPartner << std::endl;

        // --THEN: insert it w upper/lower_bound using the range w partner
        // do i need to figure out the position that the one is in largeElemebtSequence to see where do i start)
        // FIND larger Element in mian chani
        // TODO: check if int or unsigned long or whatever the main starts with
        auto posLargerPartner = std::find(largerElementSequence.begin(), largerElementSequence.end(), pairLargerPartner);
        // LOWER_BOUND begin of main chain until position of larger Element in main chain, smallerElemetSequence[findIndex - 1]
        auto it = std::upper_bound(largerElementSequence.begin(), posLargerPartner, valueToInsert); // finds the proper place within that range
        
        largerElementSequence.insert(it, valueToInsert);


        
    }






    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
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