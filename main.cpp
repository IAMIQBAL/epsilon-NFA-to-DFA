#include <iostream>
#include <vector>

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "eNFA-to-NFA.h"
#include "NFA-to-DFA.h"

int main(){

    int states, transitions;

    std::cout << "Enter No of States: ";
    std::cin >> states;
    std::cout << "Enter No of Transitions: ";
    std::cin >> transitions;

    eNFAtoNFA n1(states, transitions);

    std::cout << "Enter Transition Matrix: ";
    n1.setENFA();
    n1.getENFA();

    std::cout << "Enter Final States: ";
    n1.setFinalStates();

    std::cout << "-------------------" << std::endl;

    n1.getStates();
    n1.getTransition();

    std::cout << "NFA: " << std::endl;
    n1.convert();
    n1.printNFA();

    NFAtoDFA d1(states, transitions);
    d1.convert(n1.getTransitionsMatrix(), n1.getMapToTransitions(), n1.getNFA());
    std::cout << "\nDFA" << std::endl;
    d1.getDFA();
    d1.writeToDotFile(n1.getFinalStates());

    if (!fork()){
        execlp("dot", "dot", "-Tpng", "tests/fa.dot", "-o", "tests/dp.png", (char *)NULL);
        exit(0);
    }

    return 0;
}