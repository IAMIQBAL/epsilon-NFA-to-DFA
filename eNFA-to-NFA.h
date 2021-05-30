#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <math.h>

class eNFAtoNFA {
private:
    int states, transitions;
    char ***matrix;
    std::map<int, std::string> mapToStates;
    std::map<char, int> mapToTransitions;
    std::map<int, std::string> result;
    std::vector<char> finalStates;

public:
    eNFAtoNFA(int states, int transitions){
        this->states = states;
        this->transitions = transitions;
        matrix = new char**[states];
        for (int i = 0; i < states; i++){
            matrix[i] = new char*[transitions];
            for (int j = 0; j < transitions; j++){
                matrix[i][j] = new char[states];
                for (int k = 0; k < states; k++){
                    matrix[i][j][k] = 0;
                }
            }
        }

        for (int i = 0; i < states; i++){
            mapToStates[i] = 'A' + i;
            mapToTransitions['A' + i] = i;
        }
    }

    char*** getTransitionsMatrix(){
        return matrix;
    }

    void setENFA(){
        for (int i = 0; i < states; i++){
            for (int j = 0; j < transitions; j++){
                for (int k = 0; k < states; k++){
                    std::cin >> matrix[i][j][k];
                }
            }
        }
    }

    void getENFA(){
        for (int i = 0; i < states; i++){
            std::cout << "< ";
            for (int j = 0; j < transitions; j++){
                for (int k = 0; k < states; k++){
                    std::cout << matrix[i][j][k] << " ";
                }
                std::cout << "> <";
            }
            std::cout << " >";
            std::cout << std::endl;
        }
    }

    void setFinalStates(){
        char fSt;
        std::cin >> fSt;
        while (fSt != 'q'){
            finalStates.push_back(fSt);
            std::cin >> fSt;
        }
    }

    std::vector<char> getFinalStates(){
        return finalStates;
    }

    void convert(){
        std::string tmp;
        for (int i = 0; i < states; i++){
            result[i] = mapToStates[i];
            for (int j = 0; j < states; j++){
                if (matrix[i][transitions - 1][j] != '0'
                    && result[i] != std::to_string(matrix[i][transitions - 1][j])){
                        result[i] += matrix[i][transitions - 1][j];
                    }
            }
        }

        for (int i = 0; i < states; i++){
            for (int j = 1; j < result[i].length(); j++){
                if (result[mapToTransitions[result[i][j]]].length() > 1){
                    for (int k = 1; k < result[mapToTransitions[result[i][j]]].length(); k++){
                        if (result[i].find(result[mapToTransitions[result[i][j]]][k]) == std::string::npos){
                            result[i] += result[mapToTransitions[result[i][j]]][k];
                        }
                    }
                }
            }
        }
    }

    void printNFA(){
        for (int i = 0; i < states; i++){
            std::cout << mapToStates[i] << " <---> " << "< " << result[i] << " >" << std::endl;
        }
    }

    std::map<int, std::string> getNFA(){
        return result;
    }

    std::map<char, int> getMapToTransitions(){
        return mapToTransitions;
    }

    void getStates(){
        std::map<int, std::string>::iterator iter;
        std::cout << "Key\t" << "Value" << std::endl;
        for (iter = mapToStates.begin(); iter != mapToStates.end(); ++iter){
            std::cout << iter->first << "\t" << iter->second << std::endl;
        }
    }

    void getTransition(){
        std::map<char, int>::iterator iter;
        std::cout << "Key\t" << "Value" << std::endl;
        for (iter = mapToTransitions.begin(); iter != mapToTransitions.end(); ++iter){
            std::cout << iter->first << "\t" << iter->second << std::endl;
        }
    }

};