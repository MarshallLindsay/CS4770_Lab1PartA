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

#define LEARNING_RATE 0.7
#define MOMENTUM_RATE 0.3
#define INPUTS 3
#define OUTPUTS 2

using namespace std;

vector<vector<double>> weightVector;
vector<double> biasVector;

void readWeights(string filename);
void readBias(string filename);
void readTrainingData(string filename);

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

  //Clear the weight vector
  weightVector.clear();

  //Print the weights (DEBUGG)
  net.printWeights();

  //Read the bias for the first layer
  readBias("b1.csv");

  //Set the bias for the first layer
  net.setBias(biasVector, 0);

  //Clear the biasVector
  biasVector.clear();

  //Read the bias for the second layer
  readBias("b2.csv");

  //Set the bias for the second layer
  net.setBias(biasVector, 1);

  //Clear the bias vector
  biasVector.clear();

  //Print the bias' (DEBUGG)
  net.printBias();

  //Set the learning rates
  net.setLearningRate(LEARNING_RATE);

  //Set the momentum rates
  net.setMomentumRate(MOMENTUM_RATE);

  //Read the training data
  readTrainingData("cross_data.csv");


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

void readBias(string filename){
  string line;
  ifstream biasFile (filename);
  if(biasFile.is_open()){

    while(! biasFile.eof()){
      getline(biasFile, line);
      //cout<<line<<endl;
      biasVector.push_back(atof(line.c_str()));
    }
  }else{
    cout << "Could not open the file!" << endl;
    exit(1);
  }
  biasFile.close();
}
