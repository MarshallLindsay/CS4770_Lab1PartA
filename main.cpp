/*

Author: Marshall Lindsay
Email: mblgh6@mail.missouri.edu
Class Code: CS4770
Project Name: Lab1PartA

*/
#include "neurons.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv){
  vector<int> hello = {3,10,4};
  Network *net = new Network(hello);

  cout << net->getNumberOfLayers() << endl;

  for(int i = 0; i < net->getNumberOfLayers(); i++){
    cout << net->getNeuronsInLayer(i) << endl;
  }

  delete(net);
  return(0);
}
