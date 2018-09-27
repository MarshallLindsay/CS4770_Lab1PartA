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
  this->localField = 0;
  this->localGradient = 0;
  this->output = 0;
  this-> bias = 0;
  this-> learningRate = 0;
  this-> momentumRate = 0;
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

void RosenblattPerceptron::setLearningRate(double lr){
  this->learningRate = lr;
}

void RosenblattPerceptron::setMomentumRate(double mr){
  this->momentumRate = mr;
}

void RosenblattPerceptron::calculateLocalField(vector<double> inputData){

  if(inputData.size() != this->weights.size()){
    cout<<"You dun goofed... calculateLocalField"<<endl;
  }


  for(int i = 0; i < inputData.size(); i++){
    cout<<"Weight : " << weights[i] << " Input: " << inputData[i] << endl;
    this->localField += (weights[i])*(inputData[i]);
  }
  cout<<"Bias : " << this->getBias() << endl;
  this->localField += this->getBias();
  cout<<"Local field at "<< this->getLayer() << ","<< this->getNumber()<< " is " << this->getLocalField()<<endl;
}

void RosenblattPerceptron::calculateOutput(){
  this->output = 1 / (1 + exp(-(this->getLocalField())));
  cout<< "Output at "<< this->getLayer() << ","<< this->getNumber()<< " is " << this->getOutput()<< endl;
}

void RosenblattPerceptron::calculateLocalGradient_hidden(vector<double> previousLayerGradients){

}

void RosenblattPerceptron::calculateLocalGradient_output(double error){

}

/***********************************************************************/


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

vector<vector<double>> Network::getOutputs(){
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

void Network::setBias(vector<double> inputBias, int layer){
  for(int i = 0; i < this->layerInfo[layer]; i++){
    this->neurons[layer][i].setBias(inputBias[i]);
  }
}

void Network::printWeights(){

  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->layerInfo[i]; j++){
      for(int k = 0; k < this->neurons[i][j].getWeights().size(); k++){
        cout << "Weight "<<i<<","<<j<<","<<k<<": "<<this->neurons[i][j].getWeight(k) << endl;
      }
    }
  }

}

void Network::printBias(){
  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->layerInfo[i]; j++){
      cout << "Bias "<<i<<","<<j<<": "<< this->neurons[i][j].getBias() << endl;
    }
  }
}

void Network::setLearningRate(double learningRate){
  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->layerInfo[i]; j++){
      this->neurons[i][j].setLearningRate(learningRate);
    }
  }
}

void Network::setMomentumRate(double momentumRate){
  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->layerInfo[i]; j++){
      this->neurons[i][j].setMomentumRate(momentumRate);
    }
  }

}

void Network::forwardComputation(vector<double> inputTrainingData, vector<double> outputTrainingData){
  //Caclulate local field for first layer
  for(int i = 0; i < this->getNeuronsInLayer(0); i++){
    this->neurons[0][i].calculateLocalField(inputTrainingData);
  }

  //Calculate the output for the first layer
  for(int i = 0; i < this->getNeuronsInLayer(0); i++){
    this->neurons[0][i].calculateOutput();
  }

  //Update the networks output vector
  vector<double> temp;
  for(int i = 0; i < this->getNeuronsInLayer(0); i++){
    temp.push_back(this->neurons[0][i].getOutput());
  }
  this->outputs.push_back(temp);
  temp.clear();

  //Calculate the local field for the seceond layer
  for(int i = 0; i < this->getNeuronsInLayer(1); i++){
    this->neurons[1][i].calculateLocalField(this->outputs[0]);
  }

  //Calculate the output for the second layer
  for(int i = 0; i < this->getNeuronsInLayer(1); i++){
    this->neurons[1][i].calculateOutput();
  }

  //Update the networks output vector
  for(int i = 0; i < this->getNeuronsInLayer(1); i++){
    temp.push_back(this->neurons[1][i].getOutput());
  }
  this->outputs.push_back(temp);
  temp.clear();

  //Calculate the error
  this->calculateError(outputTrainingData);
}

void Network::backwardComputation(){
  //Calculate local gradients//
  vector<double> temp;
   //For each layer starting with the output
  for(int i = this->getNumberOfLayers() - 1 ; i > 0; i--){
    //If this is the output layer
    if(i == this->getNumberOfLayers() - 1 ){
      //For each neuron in the output layer
      for(int j = 0; j < this->getNeuronsInLayer(i); j++){
        //Calculate the local gradient given its error
        this->neurons[i][j].calculateLocalGradient_output(this->error[j]);
        //Add that gradient to the temp vector
        temp.push_back(this->neurons[i][j].getLocalGradient());
      }
    }else{ //If this is a hidden layer

      //For each neuron in the hidden layer
      for(int j = 0; j < this->getNeuronsInLayer(i); j++){
        //Calculate the local gradient given the gradients of the layer before
        this->neurons[i][j].calculateLocalGradient_hidden(this->neuronGradients[i+1]);

        //Add that gradient to the temp vector
        temp.push_back(this->neurons[i][j].getLocalGradient());
      }
    }
    //Record those gradients in the network
    this->neuronGradients.push_back(temp);

    //Clear the temp vector
    temp.clear();
  }


}

void Network::calculateError(vector<double> outputTrainingData){
  for(int i = 0; i < outputTrainingData.size(); i++){
    this->error.push_back(outputTrainingData[i] - this->outputs[this->numberOfLayers - 1][i]);
    //cout<<"Error is " << this->error[i] << endl;
  }
}
