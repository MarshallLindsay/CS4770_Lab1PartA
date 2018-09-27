/*

Author: Marshall Lindsay
Email: mblgh6@mail.missouri.edu
Class Code: CS4770
Project Name: Lab1PartA

*/

#include "neurons.h"
#include <iostream>


using namespace std;

RosenblattPerceptron::RosenblattPerceptron(int layer, int number){
  //cout << "RosenblattPerceptron constructor" << endl;
  this->location[0] = layer;
  this->location[1] = number;
}

RosenblattPerceptron::~RosenblattPerceptron(){
  //cout << "RosenblattPerceptron destructor" << endl;
}

void RosenblattPerceptron::randomizeWeights(){

}

int RosenblattPerceptron::getLayer(){
  return(this->location[0]);
}

int RosenblattPerceptron::getNumber(){
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

void RosenblattPerceptron::setWeight(vector<double> inputWeights){
  this->weights = inputWeights;
}

void RosenblattPerceptron::setBias(double inputBias){
  this->bias = inputBias;
}


Network::Network(vector<int> layerInfo){
//  cout << "Network constructor" << endl;
  this->numberOfLayers = layerInfo.size();
  this->layerInfo = layerInfo;
  for(int i = 0; i < this->numberOfLayers; i++){
    vector<RosenblattPerceptron> temp;
    for(int j = 0; j < this->layerInfo[i]; j++){
      RosenblattPerceptron neuron(i,j);
      temp.push_back(neuron);
    }
    this->neurons.push_back(temp);
  }
}

Network::~Network(){
  //cout << "Network destructor" << endl;
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

vector<vector<RosenblattPerceptron>> Network::getNeurons(){
  return(this->neurons);
}

void Network::addNeuron(RosenblattPerceptron neuron){
  //this->neurons.push_back(neuron);
}


void Network::setWeights(vector<vector<double>> inputWeights, int layer){
  for(int i = 0; i < this->layerInfo[layer]; i++){
    this->neurons[layer][i].setWeight(inputWeights[i]);
  }
}

void Network::setBias(vector<double> inputBias){

}

void Network::printWeights(){

  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->layerInfo[i]; j++){
      for(int k = 0; k < this->neurons[i][j].getWeights().size(); k++){
        cout << this->neurons[i][j].getWeight(k) << endl;
      }
    }
  }

}
