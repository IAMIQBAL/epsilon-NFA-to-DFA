#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <math.h>
#include <fstream>

class NFAtoDFA {
private:
    std::map<int, std::map<int, std::string>> DFA;
    int states, transitions;
    std::string *newStates;
    std::map<std::string, int> dfaNewStates;
    std::vector<char> indStates;

public:
    NFAtoDFA(int states, int transitions){
        this->states = states;
        this->transitions = transitions;
        int aloc = pow(2, this->states);
        newStates = new std::string[aloc];
    }

    void convert(char ***matrix, std::map<char, int> mapToTransitions, std::map<int, std::string> NFA){

        dfaNewStates[NFA[0]] = 1;
        newStates[0] = NFA[0];
        int first = 0;
        int last = 1;
        while (first < last){
            for(int i = 0; i < transitions - 1; i++){
                for(int j = 0; j< newStates[first].length(); j++){
                    if(matrix[mapToTransitions[newStates[first][j]]][i][0] != '0'){
                        for(int k = 0; k < states; k++){
                            if(matrix[mapToTransitions[newStates[first][j]]][i][k] != '0'){
                                indStates.push_back(matrix[mapToTransitions[newStates[first][j]]][i][k]);
                            } else {
                                break;
                            }
                        }
                    }
                }
                
                for(int l = 0; l < indStates.size(); l++){
                    for(int k = 0; k < NFA[mapToTransitions[indStates[l]]].length(); k++){
                        if(DFA[first][i].find(NFA[mapToTransitions[indStates[l]]][k]) == std::string::npos){
                            DFA[first][i] += NFA[mapToTransitions[indStates[l]]][k];
                        }
                    }
                }

                indStates.clear();
                if(dfaNewStates[DFA[first][i]] != 1){
                    newStates[last] = DFA[first][i];
                    last++;
                }
               
                dfaNewStates[DFA[first][i]] = 1;
            }
            first++;
        }
    }

    void getDFA(){
        for (int i = 0; i < dfaNewStates.size(); i++){
            std::cout << newStates[i] << " ---> ";
            for (int j = 0; j < transitions - 1; j++){
                std::cout << DFA[i][j] << " | ";
            }
            std::cout << std::endl;
        }
    }

    void writeToDotFile(){
        int flag = 0;
        std::ofstream file;
        file.open("fa2.dot", std::ios::out);
        file << "digraph finite_state_machine {\nrankdir=LR; \nsize=\"8,5\" \nnode [shape = doublecircle]; \nnode [shape = circle];\n";

        for (int i = 0; i < dfaNewStates.size(); i++){
            for (int j = 0; j < transitions - 1; j++){
                file << newStates[i] << "->";
                file << DFA[i][j] << "[label = " << flag << "];\n";
                flag = 1;
            }
            flag = 0;
        }
        
        file << "}";
        file.close();
    }
};