/*

Author: Marshall Lindsay
Email: mblgh6@mail.missouri.edu
Class Code: CS4770
Project Name: Lab1PartA

*/

#include "neurons.h"
#include <iostream>


using namespace std;

RosenblattPerceptron::RosenblattPerceptron(){
  cout << "RosenblattPerceptron constructor" << endl;
}

RosenblattPerceptron::~RosenblattPerceptron(){
  cout << "RosenblattPerceptron destructor" << endl;
}

void RosenblattPerceptron::randomizeWeights(){

}

int8_t RosenblattPerceptron::getLayer(){
  return(this->location[0]);
}

int8_t RosenblattPerceptron::getNumber(){
  return(this->location[1]);
}

double RosenblattPerceptron::getLocalGradient(){
  return(this->localGradient);
}

double RosenblattPerceptron::getLocalField(){
  return(this->localField);
}

double RosenblattPerceptron::getOutput(){
  return(this->output);
}

vector<double> RosenblattPerceptron::getWeights(){
  return(this->weights);
}

double RosenblattPerceptron::getWeight(int number){
  return(this->weights[number]);
}

double RosenblattPerceptron::getBias(){
  return(this->bias);
}

double RosenblattPerceptron::getLearningRate(){
  return(this->learningRate);
}

double RosenblattPerceptron::getMomentumRate(){
  return(this->momentumRate);
}


Network::Network(vector<int> layerInfo){
  cout << "Network constructor" << endl;
  this->numberOfLayers = layerInfo.size();
  this->layerInfo = layerInfo;
}

Network::~Network(){
  cout << "Network destructor" << endl;
}

vector<int> Network::getInputs(){
  return(this->inputs);
}

vector<int> Network::getOutputs(){
  return(this->outputs);
}

int Network::getNumberOfLayers(){
  return(this->numberOfLayers);
}

vector<int> Network::getLayerInfo(){
  return(this->layerInfo);
}

int Network::getNeuronsInLayer(int number){
  return(this->layerInfo[number]);
}

vector<RosenblattPerceptron> Network::getNeurons(){
  return(this->neurons);
}
