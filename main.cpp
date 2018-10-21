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


using namespace std;
int inputs = 0;
int outputs = 0;
vector<vector<double>> weightVector;
vector<double> biasVector;
vector<vector<double>> inputTrainingData;
vector<vector<double>> outputTrainingData;


void readWeights(string filename);
void readBias(string filename);
void readTrainingData(string filename);
void printTrainingData();
void printErrors();
void printOutputs();

int main(int argc, char **argv){
  cout<<fixed;
  cout<<setprecision(4);
  inputs = atoi(argv[1]);
  outputs = atoi(argv[2]);

  //Read the training data
  readTrainingData("cross_data.csv");
  inputTrainingData.pop_back();
  outputTrainingData.pop_back();
  //printTrainingData();
  //Set up the network
  vector<int> layerInfo;
  for(int i = 3; i < argc; i++){
    //cout<<argv[i]<<endl;
    layerInfo.push_back(atoi(argv[i]));
  }

  readWeights("w1.csv");
  weightVector.pop_back();
  readWeights("w2.csv");
  weightVector.pop_back();
  readBias("b1.csv");
  biasVector.pop_back();
  readBias("b2.csv");
  biasVector.pop_back();
  int userinput;
  Network net = Network(layerInfo, weightVector, biasVector, LEARNING_RATE, MOMENTUM_RATE);
  int count = 0;
  do{
    cout<<"Training number : " << count<< endl;
    net.setInputs(inputTrainingData[count]);
    net.setOutputs(outputTrainingData[count]);
    //printTrainingData();
    net.train();
    net.update();
    count++;
  //  net.printOutputs();
  //  net.printErrors();

  }while(count < 314);

  net.printWeights();
  net.printBias();
  net.printErrors();
  net.calculateMSE();
  net.printMSE();


  return(0);
}


void readWeights(string filename){
  string line;
  ifstream weightFile (filename);
  if(weightFile.is_open()){

    while(! weightFile.eof()){
      getline(weightFile, line);
    //  cout<<line<<endl;
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

void readTrainingData(string filename){
  string line;
  string::size_type sz;
  ifstream trainingFile (filename);
  if(trainingFile.is_open()){

    while(! trainingFile.eof()){
      getline(trainingFile, line);
    //  cout<<line<<endl;
      stringstream check1(line);

      string intermediate;
      //Grab the inputs from the line
      vector<double> tempVector;
    //  cout<<inputs<<endl;
      for(int i = 0; i < inputs; i++){
        getline(check1,intermediate,',');
      //  cout<<intermediate<<endl;
        tempVector.push_back(atof(intermediate.c_str()));
      }
      inputTrainingData.push_back(tempVector);
      //Grab the outputs from the line
      tempVector.clear();
      for(int i = 0; i < outputs; i++){
        getline(check1, intermediate, ',');
      //  cout<<intermediate<<endl;;
        tempVector.push_back(atof(intermediate.c_str()));
      }
      outputTrainingData.push_back(tempVector);

    }
  }else{
    cout << "Could not open the file!" << endl;
    exit(1);
  }
  trainingFile.close();
}

void printTrainingData(){

  for(int i = 0; i < inputTrainingData.size(); i++){
    cout<<"Input data: (";
    for(int j = 0; j < inputs; j++){
      cout<<inputTrainingData[i][j];
      if(j < inputs - 1){
        cout<<",";
      }
    }
    cout<<")   Output data: (";
    for(int j = 0; j < outputs; j++){
      cout<<outputTrainingData[i][j];
      if(j < outputs - 1){
        cout<<",";
      }
    }
    cout<<")"<<endl;
  }

}
