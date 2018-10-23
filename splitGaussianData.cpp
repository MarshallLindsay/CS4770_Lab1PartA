#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <string.h>
using namespace std;
void readData(string filename);
void printData(vector<vector<double> > data);
void splitData(string firstClassFileName, string secondClassFileName);
void saveData(string filename, vector<vector<double>> data);
void fiveFoldSplit();

vector<vector<double> > inputData;
vector<vector<double>> classOneInputData;
vector<vector<double>> classTwoInputData;

int main(int argc, char** argv){
  string class1file = "gausclass1.dat";
  string class2file = "gausclass2.dat";
  string inputFile = "Two_Class_FourDGaussians500.txt";

  readData(inputFile);
  //printData(inputData);
  splitData(class1file, class2file);
  //printData(classTwoInputData);
  //printData(classOneInputData);
  saveData(class1file, classOneInputData);
  saveData(class2file, classTwoInputData);

  fiveFoldSplit();

}

void readData(string filename){

  string line;
  ifstream file(filename.c_str(), ifstream::in);
  if(!file.is_open()){
    cout<<"Could not open "<<filename<<endl;
    exit(1);
  }

  while(!file.eof()){

    getline(file, line);
    stringstream check1(line);
    string intermediate;
    vector<double> data;
    while(getline(check1, intermediate, ' ')){
      if(!atof(intermediate.c_str()) == 0)
      data.push_back(atof(intermediate.c_str()));
    }
    inputData.push_back(data);
  }

  file.close();
}

void printData(vector<vector<double> > data){
  for(int i = 0; i < data.size(); i++){
    for(int j = 0; j < data[i].size(); j++){
      cout<<data[i][j]<<" ";
    }
    cout<<endl;
  }
}

void splitData(string firstClassFileName, string secondClassFileName){
  ofstream outputfile;
  outputfile.open(firstClassFileName);
  if(!outputfile.is_open()){
    cout<<"Could not open "<<firstClassFileName<<endl;
    exit(1);
  }

  ofstream anotherOutputFile;
  anotherOutputFile.open(secondClassFileName);
  if(!anotherOutputFile.is_open()){
    cout<<"Could not open "<<secondClassFileName<<endl;
    exit(1);
  }
  vector<double> tempVector;
  for(int i = 0; i < inputData.size(); i++){
    for(int j = 0; j < inputData[i].size(); j++){
      tempVector.push_back(inputData[i][j]);
    }
    if(tempVector.back() == 1){
      classOneInputData.push_back(tempVector);
    }else{
      classTwoInputData.push_back(tempVector);
    }
    tempVector.clear();
  }

  outputfile.close();
  anotherOutputFile.close();
}

void saveData(string filename, vector<vector<double>> data){

  ofstream outputFile;
  outputFile.open(filename);
  if(!outputFile.is_open()){
    cout<<"Could not open "<<filename<<endl;
    exit(1);
  }

  for(int i = 0; i < data.size(); i++){
    for(int j = 0; j < data[i].size(); j++){
      outputFile << data[i][j] << " ";
    }
    outputFile<<endl;
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

void fiveFoldSplit(){
  string firstTesting = "firstTesting.dat";
  string secondTesting = "secondTesting.dat";
  string thirdTesting = "thirdTesting.dat";
  string fourthTesting = "fourthTesting.dat";
  string fithTesting = "fithTesting.dat";
  string firstTraining = "firstTraining.dat";
  string secondTraining = "secondTraining.dat";
  string thirdTraining = "thirdTraining.dat";
  string fourthTraining = "fourthTraining.dat";
  string fifthTraining = "fifthTraining.dat";
  ofstream outputFile;
  vector<string> filenames = {firstTesting,firstTraining,secondTesting,secondTraining,thirdTesting,thirdTraining,fourthTesting,fourthTraining,fithTesting,fifthTraining};

  vector<vector<double>> trainingData;
  vector<vector<double>> testingData;
  //cout<<classOneInputData.size() *(double(1)/double(5))<<endl;
  for(double i = 0; i < classOneInputData.size() *(double(1)/double(5))-1; i++){
    trainingData.push_back(classOneInputData[i]);
  }
  for(double i = 0; i < classTwoInputData.size() *(double(1)/double(5))-1; i++){
    trainingData.push_back(classTwoInputData[i]);
  }
  for(double i = classOneInputData.size() *(double(1)/double(5)); i < classOneInputData.size(); i++){
    testingData.push_back(classOneInputData[i]);
  }
  for(double i = classTwoInputData.size() *(double(1)/double(5)); i < classTwoInputData.size(); i++){
    testingData.push_back(classTwoInputData[i]);
  }

  outputFile.open(filenames[0], ios_base::out);
  if(!outputFile.is_open()){
    cout<<"Could not open the file : "<<filenames[1]<<endl;
    exit(1);
  }

  for(int i = 0; i < testingData.size(); i++){
    for(int k = 0; k < testingData[i].size(); k++){
      outputFile<<testingData[i][k];
      if(k < testingData[i].size() -1){
        outputFile<<",";
      }
    }
    outputFile<<endl;
  }
  outputFile.close();

  outputFile.open(filenames[1], ios_base::out );
  if(!outputFile.is_open()){
    cout<<"Could not open the file : "<<filenames[2]<<endl;
    exit(1);
  }

  for(int i = 0; i < trainingData.size(); i++){
    for(int k = 0; k < trainingData[i].size(); k++){
      outputFile<<trainingData[i][k];
      if(k < trainingData[i].size() -1){
        outputFile<<",";
      }
    }
    outputFile<<endl;
  }
  outputFile.close();
  trainingData.clear();
  testingData.clear();
////////////////////////////////////////////////////////////////////////////////
  for(double i = classOneInputData.size() *(double(1)/double(5)); i < classOneInputData.size() *(double(2)/double(5))-1; i++){
    trainingData.push_back(classOneInputData[i]);
  }
  for(double i = classTwoInputData.size() *(double(1)/double(5)); i < classTwoInputData.size() *(double(2)/double(5))-1; i++){
    trainingData.push_back(classTwoInputData[i]);
  }

  for(double i = 0; i < classOneInputData.size() *(double(1)/double(5)) -1; i++){
    testingData.push_back(classOneInputData[i]);
  }
  for(double i = classOneInputData.size() *(double(2)/double(5)); i < classTwoInputData.size(); i++){
    testingData.push_back(classOneInputData[i]);
  }

  for(double i = 0; i < classTwoInputData.size() *(double(1)/double(5)) -1; i++){
    testingData.push_back(classTwoInputData[i]);
  }
  for(double i = classTwoInputData.size() *(double(2)/double(5)); i < classTwoInputData.size(); i++){
    testingData.push_back(classTwoInputData[i]);
  }

  outputFile.open(filenames[2], ios_base::out);
  if(!outputFile.is_open()){
    cout<<"Could not open the file : "<<filenames[2]<<endl;
    exit(1);
  }

  for(int i = 0; i < testingData.size(); i++){
    for(int k = 0; k < testingData[i].size(); k++){
      outputFile<<testingData[i][k];
      if(k < testingData[i].size() -1){
        outputFile<<",";
      }
    }
    outputFile<<endl;
  }
  outputFile.close();

  outputFile.open(filenames[3], ios_base::out );
  if(!outputFile.is_open()){
    cout<<"Could not open the file : "<<filenames[3]<<endl;
    exit(1);
  }

  for(int i = 0; i < trainingData.size(); i++){
    for(int k = 0; k < trainingData[i].size(); k++){
      outputFile<<trainingData[i][k];
      if(k < trainingData[i].size() -1){
        outputFile<<",";
      }
    }
    outputFile<<endl;
  }
  outputFile.close();
  trainingData.clear();
  testingData.clear();

  ////////////////////////////////////////////////////////////////////////////////
    for(double i = classOneInputData.size() *(double(2)/double(5)); i < classOneInputData.size() *(double(3)/double(5))-1; i++){
      trainingData.push_back(classOneInputData[i]);
    }
    for(double i = classTwoInputData.size() *(double(2)/double(5)); i < classTwoInputData.size() *(double(3)/double(5))-1; i++){
      trainingData.push_back(classTwoInputData[i]);
    }

    for(double i = 0; i < classOneInputData.size() *(double(2)/double(5)) -1; i++){
      testingData.push_back(classOneInputData[i]);
    }
    for(double i = classOneInputData.size() *(double(3)/double(5)); i < classTwoInputData.size(); i++){
      testingData.push_back(classOneInputData[i]);
    }

    for(double i = 0; i < classTwoInputData.size() *(double(2)/double(5)) -1; i++){
      testingData.push_back(classTwoInputData[i]);
    }
    for(double i = classTwoInputData.size() *(double(3)/double(5)); i < classTwoInputData.size(); i++){
      testingData.push_back(classTwoInputData[i]);
    }

    outputFile.open(filenames[4], ios_base::out);
    if(!outputFile.is_open()){
      cout<<"Could not open the file : "<<filenames[4]<<endl;
      exit(1);
    }

    for(int i = 0; i < testingData.size(); i++){
      for(int k = 0; k < testingData[i].size(); k++){
        outputFile<<testingData[i][k];
        if(k < testingData[i].size() -1){
          outputFile<<",";
        }
      }
      outputFile<<endl;
    }
    outputFile.close();

    outputFile.open(filenames[5], ios_base::out );
    if(!outputFile.is_open()){
      cout<<"Could not open the file : "<<filenames[5]<<endl;
      exit(1);
    }

    for(int i = 0; i < trainingData.size(); i++){
      for(int k = 0; k < trainingData[i].size(); k++){
        outputFile<<trainingData[i][k];
        if(k < trainingData[i].size() -1){
          outputFile<<",";
        }
      }
      outputFile<<endl;
    }
    outputFile.close();
    trainingData.clear();
    testingData.clear();

    ////////////////////////////////////////////////////////////////////////////////
      for(double i = classOneInputData.size() *(double(3)/double(5)); i < classOneInputData.size() *(double(4)/double(5))-1; i++){
        trainingData.push_back(classOneInputData[i]);
      }
      for(double i = classTwoInputData.size() *(double(3)/double(5)); i < classTwoInputData.size() *(double(4)/double(5))-1; i++){
        trainingData.push_back(classTwoInputData[i]);
      }

      for(double i = 0; i < classOneInputData.size() *(double(3)/double(5)) -1; i++){
        testingData.push_back(classOneInputData[i]);
      }
      for(double i = classOneInputData.size() *(double(4)/double(5)); i < classTwoInputData.size(); i++){
        testingData.push_back(classOneInputData[i]);
      }

      for(double i = 0; i < classTwoInputData.size() *(double(3)/double(5)) -1; i++){
        testingData.push_back(classTwoInputData[i]);
      }
      for(double i = classTwoInputData.size() *(double(4)/double(5)); i < classTwoInputData.size(); i++){
        testingData.push_back(classTwoInputData[i]);
      }

      outputFile.open(filenames[6], ios_base::out);
      if(!outputFile.is_open()){
        cout<<"Could not open the file : "<<filenames[6]<<endl;
        exit(1);
      }

      for(int i = 0; i < testingData.size(); i++){
        for(int k = 0; k < testingData[i].size(); k++){
          outputFile<<testingData[i][k];
          if(k < testingData[i].size() -1){
            outputFile<<",";
          }
        }
        outputFile<<endl;
      }
      outputFile.close();

      outputFile.open(filenames[7], ios_base::out );
      if(!outputFile.is_open()){
        cout<<"Could not open the file : "<<filenames[7]<<endl;
        exit(1);
      }

      for(int i = 0; i < trainingData.size(); i++){
        for(int k = 0; k < trainingData[i].size(); k++){
          outputFile<<trainingData[i][k];
          if(k < trainingData[i].size() -1){
            outputFile<<",";
          }
        }
        outputFile<<endl;
      }
      outputFile.close();
      trainingData.clear();
      testingData.clear();
    ////////////////////////////////////////////////////////////////////////////////
      for(double i = classOneInputData.size() *(double(4)/double(5)); i < classOneInputData.size() *(double(5)/double(5))-1; i++){
        trainingData.push_back(classOneInputData[i]);
      }
      for(double i = classTwoInputData.size() *(double(4)/double(5)); i < classTwoInputData.size() *(double(5)/double(5))-1; i++){
        trainingData.push_back(classTwoInputData[i]);
      }

      for(double i = 0; i < classOneInputData.size() *(double(4)/double(5)) -1; i++){
        testingData.push_back(classOneInputData[i]);
      }
      for(double i = classOneInputData.size() *(double(5)/double(5)); i < classTwoInputData.size(); i++){
        testingData.push_back(classOneInputData[i]);
      }

      for(double i = 0; i < classTwoInputData.size() *(double(4)/double(5)) -1; i++){
        testingData.push_back(classTwoInputData[i]);
      }
      for(double i = classTwoInputData.size() *(double(5)/double(5)); i < classTwoInputData.size(); i++){
        testingData.push_back(classTwoInputData[i]);
      }

      outputFile.open(filenames[8], ios_base::out);
      if(!outputFile.is_open()){
        cout<<"Could not open the file : "<<filenames[8]<<endl;
        exit(1);
      }

      for(int i = 0; i < testingData.size(); i++){
        for(int k = 0; k < testingData[i].size(); k++){
          outputFile<<testingData[i][k];
          if(k < testingData[i].size() -1){
            outputFile<<",";
          }
        }
        outputFile<<endl;
      }
      outputFile.close();

      outputFile.open(filenames[9], ios_base::out );
      if(!outputFile.is_open()){
        cout<<"Could not open the file : "<<filenames[9]<<endl;
        exit(1);
      }

      for(int i = 0; i < trainingData.size(); i++){
        for(int k = 0; k < trainingData[i].size(); k++){
          outputFile<<trainingData[i][k];
          if(k < trainingData[i].size() -1){
            outputFile<<",";
          }
        }
        outputFile<<endl;
      }
      outputFile.close();
      trainingData.clear();
      testingData.clear();

}
/*
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
*/
