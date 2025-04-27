#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& result,
    size_t index);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    set<string> result;
    size_t index = 0;
    std::string curr = in;
    set<char> originalFloating(floating.begin(), floating.end());
    wordleHelper(curr,floating, dict, result, index);

    return result;


}

// Define any helper functions here


void wordleHelper(
    std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& result,
    size_t index)
    {
        

        if(index==in.length()){
            if(floating.empty() && dict.find(in) != dict.end()){
                result.insert(in);
            }
            return;
        }

        if(in[index] != '-'){
            wordleHelper(in,floating,dict,result,index+1);
        }
        else{

            size_t dashesLeft = 0;
            for(size_t i = index; i < in.length(); i++){
                if(in[i] == '-'){
                    ++dashesLeft;
                }
            }
            set<char> used;
            for(size_t i=0;i<floating.length();i++){
                char curr = floating[i];
                if(used.find(curr)== used.end()){
                    used.insert(curr);
                    in[index] = curr;
                    string newFloating = floating;
                    newFloating.erase(i,1);
                    wordleHelper(in,newFloating,dict,result,index+1);
                    in[index] = '-';

                }
                
            }
            if(dashesLeft > floating.length()){
                set<char> remainingFloating(floating.begin(),floating.end());
                for(size_t i=0;i<26;i++){
                    char letter = 'a' + i;
                    if(used.find(letter)==used.end() && remainingFloating.find(letter)==remainingFloating.end()){
                        in[index] = letter;
                        wordleHelper(in,floating,dict,result,index+1);
                        in[index] = '-';
                    }
                    
                }
            }
            
        }
        
        
    }
