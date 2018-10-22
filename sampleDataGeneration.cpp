

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLE_DATA_FILENAME "sampling.csv"
#define GRANULARITY 0.01

using namespace std;


int main(int argc, char ** argv){
  srand (time(NULL));
  ofstream outputFile;
  outputFile.open(SAMPLE_DATA_FILENAME);

  if(!outputFile.is_open()){
    cout<<"Could not open the file: "<<SAMPLE_DATA_FILENAME<<endl;
    exit(1);
  }

  double zValue = 0;
  for(double xValue = -2.1 ;xValue < 2.1;xValue += GRANULARITY){
    for(double yValue = -2.1;yValue < 2.1;yValue += GRANULARITY){
      zValue = (double)((double)(rand() % 5) / 100);
      outputFile << xValue << ","<<yValue<<","<<zValue<<endl;
    }

  };

  outputFile.close();
}
