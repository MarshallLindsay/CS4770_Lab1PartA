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

vector<vector<double> > inputData;
vector<vector<double>> classOneInputData;
vector<vector<double>> classTwoInputData;

int main(int argc, char** argv){

  string class1file = "gausclass1.dat";
  string class2file = "gausclass2.dat";
  string firsttwenty = "firsttraining.dat";
  string secondtwenty = "secondTraining.dat";
  string thirdtwenty = "thirdTraining.dat";
  string fourthtwenty = "fourthTraining.dat";
  string fithtwenty = "fithTraining.dat";
  string firsttraining = "firstTesting.dat";
  string secondtraining = "secondTesting.dat";
  string thirdtraining = "thirdTesting.dat";
  string fourthtraining = "fourthTesting.dat";
  string fifthtraining = "fifthTestin.dat";

  string inputFile = "Two_Class_FourDGaussians500.txt";

  readData(inputFile);
  printData(inputData);
  splitData(class1file, class2file);
  printData(classTwoInputData);
  printData(classOneInputData);
  saveData(class1file, classOneInputData);
  saveData(class2file, classTwoInputData);






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
