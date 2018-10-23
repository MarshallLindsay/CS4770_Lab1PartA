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
#include <cstdlib>

#define LEARNING_RATE 0.7
#define MOMENTUM_RATE 0.3
#define CONVERGENCE_VALUE 0.001

#define MSE_FILENAME "fiveFold1_MSE.dat"

using namespace std;
int inputs = 0;
int outputs = 0;
vector<vector<double>> weightVector;
vector<double> biasVector;
vector<vector<double>> trainingData;
vector<vector<double>> testingData;
vector<vector<double>> inputTestingData;
vector<vector<double>> outputTestingData;
vector<vector<double>> inputTrainingData;
vector<vector<double>> outputTrainingData;
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
void save_mse();
void printTestData();
void saveTestResults(string filename, vector<double> inputData, vector<double> outputData);
void separateTestingData();
void compareTestResults(string filename, vector<double> actualOutput, vector<double> predictedOutput);

int main(int argc, char **argv){
  cout<<fixed;
  cout<<setprecision(4);
  inputs = atoi(argv[1]);
  outputs = atoi(argv[2]);

  //Read the training data
  readTrainingData("firstTesting.dat");
  trainingData.pop_back();

  //Set up the network
  vector<int> layerInfo;
  for(int i = 3; i < argc; i++){
    //cout<<argv[i]<<endl;
    layerInfo.push_back(atoi(argv[i]));
  }

  int userinput;
  Network net = Network(layerInfo, LEARNING_RATE, MOMENTUM_RATE, inputs);
  net.randomizeWeights();
  int count = 0;

do{
    separateTrainingData();
    //train for an epoc
    for(int number = 0; number < trainingData.size(); number++){
    //  cout<<number<<endl;
      net.setInputs(inputTrainingData[number]);
      net.setOutputs(outputTrainingData[number]);
      //printTrainingData();
      //net.printWeights();
      net.train();
      //net.printWeights();

      //cin >> run;
    }
    net.printOutputs();
    net.calculateMSE();
    mseData.push_back(net.getMSE());
    cout<<"MSE: "<<net.getMSE()<<endl;
    shuffleData();
  }while(net.getMSE() > CONVERGENCE_VALUE);
  //  net.printWeights();
  //  net.printBias();
  //  net.printErrors();
  //  net.printMSE();
    save_mse();

  int run;
  string outputfileName;
  cout<<"Would you like to run the neuralnet on some data?"<<endl;
  cin >> run;
  cout<<"What filename to save test results?"<<endl;
  cin>>outputfileName;
  while(run){
    //open the save file

    //Get the test data
    string filename;
    cout<<"Please enter the filename for the test data"<<endl;
    cin >>filename;

    readTestData(filename);
    testingData.pop_back();
    separateTestingData();
    //Run the network
    //printTestData();
    for(int i = 0; i < testingData.size(); i++){
      net.setInputs(inputTestingData[i]);
      net.setOutputs(outputTestingData[i]);
      net.run();
      net.printOutputs();
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
      for(int i = 0; i < 1; i++){ //adjusted for gaussian
        getline(check1, intermediate, ',');
        //cout<<intermediate<<endl;;
        //adjustment for the gaussian part
      //  cout<<intermediate<<endl;
      //  cout<<atof(intermediate.c_str())<<endl;
        if(atof(intermediate.c_str()) == 1){
          trainingData[count].push_back(1);
          trainingData[count].push_back(0);
        }else if(atof(intermediate.c_str()) == 2){
          trainingData[count].push_back(0);
          trainingData[count].push_back(1);
        }else{

        }
        //trainingData[count].push_back(atof(intermediate.c_str()));
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
      for(int i = 0; i < 1; i++){ //adjusted for gaussian
        getline(check1, intermediate, ',');
        //cout<<intermediate<<endl;;
        //adjustment for the gaussian part
        if(atof(intermediate.c_str()) == 1){
          testingData[count].push_back(1);
          testingData[count].push_back(0);
        }else if(atof(intermediate.c_str()) == 2){
          testingData[count].push_back(0);
          testingData[count].push_back(1);
        }else{

        }
        tempVector.clear();
        count++;
      }
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
