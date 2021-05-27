#include <iostream>
#include <vector>
#include "eps-NFA-to-DFA.h"
#include "NFA-to-DFA.h"
using namespace std;

int main(){

    int states, transitions;

    cout << "Enter No of States: ";
    cin >> states;
    cout << "Enter No of Transitions: ";
    cin >> transitions;

    eNFAtoNFA n1(states, transitions);

    cout << "Enter Transition Matrix: ";
    n1.setENFA();
    n1.getENFA();

    cout << "-------------------" << endl;

    n1.getStates();
    n1.getTransition();

    cout << "NFA: " << endl;
    n1.convert();
    n1.printNFA();

    NFAtoDFA d1(states, transitions);
    d1.convert(n1.getTransitionsMatrix(), n1.getMapToTransitions(), n1.getNFA());
    cout << "\nDFA" << endl;
    d1.getDFA();

    return 0;
}