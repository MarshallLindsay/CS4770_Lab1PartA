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

vector<vector<double> > inputData;

int main(int argc, char** argv){

  string class1file = "gausclass1.dat";
  string class2file = "gausclass2.dat";
  string firsttwenty = "firsttwenty.dat";
  string secondtwenty = "secondtwenty.dat";
  string thirdtwenty = "thirdtwenty.dat";
  string fourthtwenty = "fourthtwenty.dat";
  string fithtwenty = "fithtwenty.dat";

  string inputFile = "Two_Class_FourDGaussians500.txt";

  readData(inputFile);
  printData(inputData);

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
    while(getline(check1, intermediate, " ")){
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
