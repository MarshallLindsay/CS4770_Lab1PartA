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
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>


using namespace std;

vector<vector<double>> weightVector;
vector<double> biasVector;

void readWeights(string filename);

int main(int argc, char **argv){
  vector<int> hello = {11,2};
  Network net = Network(hello);

  //Read the weights for the first layer
  readWeights("w1.csv");
  //Set the weights for the first layer
  net.setWeights(weightVector, 0);

  //Clear the weight vector
  weightVector.clear();

  //Read the weights for the output layer
  readWeights("w2.csv");
  //Set the weights for the output layer
  net.setWeights(weightVector, 1);
  //Print the weights
  net.printWeights();

  return(0);
}





void readWeights(string filename){
  string line;
  ifstream weightFile (filename);
  if(weightFile.is_open()){

    while(! weightFile.eof()){
      getline(weightFile, line);
      //cout<<line<<endl;
      stringstream check1(line);
      string intermediate;
      vector<double> weight;
      while(getline(check1, intermediate, ',')){
        weight.push_back(atof(intermediate.c_str()));
      }
      weightVector.push_back(weight);
    }
  }else{
    cout << "Could not open the file!" << endl;
    exit(1);
  }
  weightFile.close();
}
