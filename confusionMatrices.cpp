


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

void buildMatrices(vector<string> fileNames);
void printMatrices(vector<vector<vector<int>>> matrices);
void saveMatrices(vector<string> fileNames);

void combineMatrices(vector<vector<vector<int>>> matrices);

vector<vector<vector<int>>> matrices;
vector<vector<vector<int>>> combinedMatrices;


int main(int argc, char** argv){

  vector<string> fileNames;

  for(int i = 1; i < argc; i++){
    fileNames.push_back(argv[i]);
  }

  buildMatrices(fileNames);
  printMatrices(matrices);
  combineMatrices(matrices);
  printMatrices(combinedMatrices);
  saveMatrices(fileNames);

  return(0);
}


void buildMatrices(vector<string> fileNames){

  ifstream inputFile;
  string line;
  //cout<<fileNames.size()<<endl;
  for(int i = 0; i < fileNames.size(); i++){
  //  cout<<"start"<<endl;

    inputFile.open(fileNames[i]);
    if(!inputFile.is_open()){
      cout<<"Could not open "<<fileNames[i]<<endl;
      exit(1);
    }
    //while(not eof)
      //get a line
      //break it down
      //compare the values
      //increment locations in the matrix
    //eof
    //push the matrix
    int one_one = 0;
    int one_two = 0;
    int two_one = 0;
    int two_two = 0;
    while(!inputFile.eof()){
      //get line
      getline(inputFile, line);
      //break it down
      stringstream check1(line);
      string intermediate;
      vector<int> tempVector;
      while(getline(check1, intermediate, ',')){
        tempVector.push_back(atof(intermediate.c_str()));
        //cout<<intermediate<< " ";
      }
      // row_column

      //compare the values
      if(tempVector.empty())
        break;

      if(tempVector[0] == 1){
        if(tempVector[1] == 1){
          one_one++;
        }else{
          one_two++;
        }
      }else if(tempVector[0] == 2){
        if(tempVector[1] == 1){
          two_one++;
        }else{
          two_two++;
        }
      }
      tempVector.clear();

    }
    vector<vector<int>> matrix;
    vector<int> tempVector;
    tempVector.push_back(one_one);
    tempVector.push_back(one_two);
    matrix.push_back(tempVector);
    tempVector.clear();
    tempVector.push_back(two_one);
    tempVector.push_back(two_two);
    matrix.push_back(tempVector);
    tempVector.clear();
    matrices.push_back(matrix);
    matrix.clear();

    inputFile.close();
  }
}


void printMatrices(vector<vector<vector<int>>> matrices){

  for(int i = 0; i < matrices.size(); i++){
    cout<<setw(40)<<"Reference"<<endl;
    cout<<setw(20)<<"1"<<setw(30)<<"2"<<endl;
    cout<<endl;
    for(int row = 0; row < matrices[i].size(); row++){
      cout<<setw(8)<<"Prediction"<<setw(10)<<row +1;
      for(int column = 0; column < matrices[i][row].size(); column++){
        cout<<setw(10)<<matrices[i][row][column];
        if(column != matrices[i][row].size() -1){
          cout<<setw(10)<<"  |  ";
        }
      }
      cout<<endl;
    }
    cout<<"\n\n\n\n\n";
  }
}

void saveMatrices(vector<string> fileNames){
  ofstream outputFile;
  outputFile.open("matrices.txt", ios::out);
  if(!outputFile.is_open()){
    cout<<"Could not open matrices.txt"<<endl;
    exit(1);
  }

  for(int i = 0; i < matrices.size(); i++){
    outputFile<<fileNames[i]<<endl;
    outputFile<<setw(40)<<"Reference"<<endl;
    outputFile<<setw(20)<<"1"<<setw(30)<<"2"<<endl;
    outputFile<<endl;
    for(int row = 0; row < matrices[i].size(); row++){
      outputFile<<setw(8)<<"Prediction"<<setw(10)<<row +1;
      for(int column = 0; column < matrices[i][row].size(); column++){
        outputFile<<setw(10)<<matrices[i][row][column];
        if(column != matrices[i][row].size() -1){
          outputFile<<setw(10)<<"  |  ";
        }
      }
      outputFile<<endl;
    }
    outputFile<<"\n\n\n\n\n";
    if(i == 4 || i == 9 || i == 14){
      //save the combined
      outputFile<<setw(40)<<"Combined"<<endl;
      outputFile<<endl;
      outputFile<<setw(40)<<"Reference"<<endl;
      outputFile<<setw(20)<<"1"<<setw(30)<<"2"<<endl;
      outputFile<<endl;
      for(int row = 0; row < combinedMatrices[i%4].size(); row++){
        outputFile<<setw(8)<<"Prediction"<<setw(10)<<row +1;
        for(int column = 0; column < combinedMatrices[i%4][row].size(); column++){
          outputFile<<setw(10)<<combinedMatrices[i%4][row][column];
          if(column != combinedMatrices[i%4][row].size() -1){
            outputFile<<setw(10)<<"  |  ";
          }
        }
        outputFile<<endl;
      }
        outputFile<<"\n\n\n\n\n";
    }


  }
  outputFile.close();
}

void combineMatrices(vector<vector<vector<int>>> matrices){
  vector<vector<int>> tempCombine;
  vector<int> temp;

  int j = 0;
  temp.push_back(j);
  temp.push_back(j);
  tempCombine.push_back(temp);
  tempCombine.push_back(temp);
  for(int i = 0; i < matrices.size(); i++){
  //  cout<<i<<endl;
    for(int row = 0; row < matrices[i].size(); row++){
      for(int column = 0; column < matrices[i][row].size(); column++){

          tempCombine[row][column] += matrices[i][row][column];

      }
    }
    if(i == 4 || i == 9 || i == 14){
    //  cout<<i<<endl;
      combinedMatrices.push_back(tempCombine);
      tempCombine.clear();
      temp.clear();
      temp.push_back(j);
      temp.push_back(j);
      tempCombine.push_back(temp);
      tempCombine.push_back(temp);
    }
  }
}
