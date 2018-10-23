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
#include <ctime>
#include <algorithm>

#define LEARNING_RATE 0.01
#define MOMENTUM_RATE 0.3
#define CONVERGENCE_VALUE 0.001

#define MSE_FILENAME "fifthFiveFold_8_mse.dat"

using namespace std;
int inputs = 0;
int outputs = 0;
vector<vector<double>> weightVector;
vector<double> biasVector;
vector<vector<double>> trainingData;
vector<vector<double>> testingData;
vector<vector<double>> inputTrainingData;
vector<vector<double>> outputTrainingData;
vector<vector<double>> inputTestingData;
vector<vector<double>> outputTestingData;
vector<double> mseData;


void readWeights(string filename);
void readBias(string filename);
void readTrainingData(string filename);
void readTestData(string filename);
void printTrainingData();
void printNewTrainingData();
void printErrors();
void printOutputs();
void shuffleData();
void separateTrainingData();
void separateTestingData();
void save_mse();
void printTestData();
void fixOutputData();
void fixTestingOutputData();
void saveTestResults(string filename, vector<double> inputData, vector<double> outputData);
void compareTestResults(string filename, vector<double> actualOutput, vector<double> predictedOutput);

int main(int argc, char **argv){
  cout<<fixed;
  cout<<setprecision(4);
  inputs = atoi(argv[1]);
  outputs = atoi(argv[2]);
  //cout<<inputs<<endl;
  //cout<<outputs<<endl;

  vector<int> layerInfo;
  for(int i = 3 ; i < argc; i ++){
    layerInfo.push_back(atoi(argv[i]));
  }

  Network net = Network(layerInfo, LEARNING_RATE, MOMENTUM_RATE, inputs);
  net.randomizeWeights();

  string fileName = "fifthTesting.dat";
  readTrainingData(fileName);
  trainingData.pop_back();

  do{
      separateTrainingData();
      fixOutputData();
      //train for an epoc
      for(int number = 0; number < trainingData.size(); number++){
        net.setInputs(inputTrainingData[number]);
        net.setOutputs(outputTrainingData[number]);
        //printTrainingData();
        net.train();
      }
      net.calculateMSE();
      mseData.push_back(net.getMSE());
      cout<<"DeltaMSE: "<<net.getDeltaMSE()<<endl;
      shuffleData();
    }while(net.getDeltaMSE() > CONVERGENCE_VALUE);

    net.printMSE();
    save_mse();

    int run;

    cout<<"Would you like to run the neuralnet on some data?"<<endl;
    cin >> run;
    while(run){
      //open the save file
      string outputfileName;
      cout<<"Testing data save file name: "<<endl;
      cin>>outputfileName;

      //Get the test data
      string filename;
      cout<<"Please enter the filename for the test data"<<endl;
      cin >>filename;

      readTestData(filename);
      testingData.pop_back();
      separateTestingData();
      fixTestingOutputData();
      //Run the network
      //printTestData();
      for(int i = 0; i < testingData.size(); i++){
        net.setInputs(inputTestingData[i]);
        net.run();
        compareTestResults(outputfileName,outputTestingData[i],net.getOutputs());
      }


      cout<<"Would you like to run again"<<endl;
      cin>>run;
    }

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
    int count = 0;
    while(! trainingFile.eof()){
      getline(trainingFile, line);
    //  cout<<line<<endl;
      stringstream check1(line);

      string intermediate;
      //Grab the inputs from the line
      vector<double> tempVector;
      trainingData.push_back(tempVector);
    //  cout<<inputs<<endl;
      for(int i = 0; i < inputs; i++){
        getline(check1,intermediate,',');
      //  cout<<intermediate<<endl;
        trainingData[count].push_back(atof(intermediate.c_str()));
      }
      //Grab the outputs from the line
      tempVector.clear();
      for(int i = 0; i < outputs; i++){
        getline(check1, intermediate, ',');
      //  cout<<intermediate<<endl;;
        trainingData[count].push_back(atof(intermediate.c_str()));
      }
      count++;
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

void printNewTrainingData(){
  for(int i = 0; i < trainingData.size(); i++){
    for(int j = 0; j < trainingData[i].size(); j++){
      cout<<trainingData[i][j] << " ";
    }
    cout<<endl;
  }

}

void separateTrainingData(){
  inputTrainingData.clear();
  outputTrainingData.clear();
  vector<double> tempVector;
  for(int i = 0; i < trainingData.size(); i++){
    for(int number = 0; number < inputs; number++){
      tempVector.push_back(trainingData[i][number]);
    }
    inputTrainingData.push_back(tempVector);
    tempVector.clear();
    for(int number = 0; number < outputs; number++){
      tempVector.push_back(trainingData[i][number+inputs]);
    }
    outputTrainingData.push_back(tempVector);
    tempVector.clear();
  }
}

void separateTestingData(){
  inputTestingData.clear();
  outputTestingData.clear();
  vector<double> tempVector;
  for(int i = 0; i < testingData.size(); i++){
    for(int number = 0; number < inputs; number++){
      tempVector.push_back(testingData[i][number]);
    }
    inputTestingData.push_back(tempVector);
    tempVector.clear();
    for(int number = 0; number < outputs; number++){
      tempVector.push_back(testingData[i][number+inputs]);
    }
    outputTestingData.push_back(tempVector);
    tempVector.clear();
  }
}

void save_mse(){

  ofstream outputFile;
  outputFile.open (MSE_FILENAME);
  for(int i = 0; i < mseData.size(); i++){
    outputFile << i << " " << mseData[i] << endl;
  }
  outputFile.close();
}


void shuffleData(){

  random_shuffle(trainingData.begin(), trainingData.end());
}

void readTestData(string filename){
  string line;
  string::size_type sz;
  ifstream testingFile (filename);
  if(testingFile.is_open()){
    int count = 0;
    while(! testingFile.eof()){
      getline(testingFile, line);
    //  cout<<line<<endl;
      stringstream check1(line);

      string intermediate;
      //Grab the inputs from the line
      vector<double> tempVector;
      testingData.push_back(tempVector);
    //  cout<<inputs<<endl;
      for(int i = 0; i < inputs; i++){
        getline(check1,intermediate,',');
      //  cout<<intermediate<<endl;
        testingData[count].push_back(atof(intermediate.c_str()));
      }
      tempVector.clear();
      for(int i = 0; i < outputs; i++){
        getline(check1, intermediate, ',');
      //  cout<<intermediate<<endl;;
        testingData[count].push_back(atof(intermediate.c_str()));
      }
      count++;
    }
  }else{
    cout << "Could not open the file!" << endl;
    exit(1);
  }
  testingFile.close();
}

void printTestData(){

  for(int i = 0 ; i < testingData.size(); i++){
    for(int j = 0; j < testingData[i].size(); j++){
      cout<<testingData[i][j]<<" ";
    }
    cout<<endl;
  }
}

void saveTestResults(string filename, vector<double> inputData, vector<double>outputData){
  ofstream outputFile;
  outputFile.open(filename, ios_base::app);
  if(!outputFile.is_open()){
    cout<<"Could not open the output file " << filename << endl;
    exit(1);
  }
  double label;
  if(outputData[0] > outputData[1]){
    label = 0;
  }else{
    label = 1;
  }

  outputFile << inputData[0] << " " << inputData[1] << " " << label <<endl;

  outputFile.close();
}

void fixOutputData(){
  //cout<<outputTrainingData[0].size()<<endl;
  for(int i = 0; i < outputTrainingData.size(); i++){
    if(outputTrainingData[i][0] == 1){
      outputTrainingData[i][0] = 1;
      outputTrainingData[i][1] = 0;
    }else if(outputTrainingData[i][0] == 2){
      outputTrainingData[i][0] = 0;
      outputTrainingData[i][1] = 1;
    }else{
      cout<<"Error in fixOutputData"<<endl;
    }
  }
}

void compareTestResults(string filename, vector<double> actualOutput, vector<double> predictedOutput){
  int actualLabel;
  int predictedLabel;
  ofstream outputFile;
  outputFile.open(filename, ios_base::app);
  if(!outputFile.is_open()){
    cout<<"Could not open "<<filename<<endl;
    exit(1);
  }

  if(predictedOutput[0] > predictedOutput[1]){
    predictedLabel = 1;
  }else{
    predictedLabel = 2;
  }
  if(actualOutput[0] > actualOutput[1]){
    actualLabel = 1;
  }else{
    actualLabel = 2;
  }

  outputFile<<predictedLabel<<","<<actualLabel<<endl;
  outputFile.close();
}

void fixTestingOutputData(){
  //cout<<outputTrainingData[0].size()<<endl;
  for(int i = 0; i < outputTestingData.size(); i++){
    if(outputTestingData[i][0] == 1){
      outputTestingData[i][0] = 1;
      outputTestingData[i][1] = 0;
    }else if(outputTestingData[i][0] == 2){
      outputTestingData[i][0] = 0;
      outputTestingData[i][1] = 1;
    }else{
      cout<<"Error in fixOutputData"<<endl;
    }
  }
}
