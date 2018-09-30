/*

Author: Marshall Lindsay
Email: mblgh6@mail.missouri.edu
Class Code: CS4770
Project Name: Lab1PartA

*/

#include "neurons.h"
#include <iostream>


using namespace std;


/******************************************************************************
                START RosenblattPerceptron
******************************************************************************/

RosenblattPerceptron::RosenblattPerceptron(int layer, int number){
  //cout << "RosenblattPerceptron constructor" << endl;
  this->setLayer(layer);
  this->setNumberInLayer(number);
  this->setLocalField(0);
  this->setLocalGradient(0);
  this->setOutput(0);
  this->setBias(0);
  this->setLearningRate(0);
  this->setMomentumRate(0);
  this->setPreviousBias(0);
}

RosenblattPerceptron::~RosenblattPerceptron(){
  //cout << "RosenblattPerceptron destructor" << endl;
}

void RosenblattPerceptron::randomizeWeights(){
  //Not used in this lab.. Write later..
}

/*****************START GETTERS**************************/

int RosenblattPerceptron::getLayer(){
  return(this->layer);
}

int RosenblattPerceptron::getNumberInLayer(){
  return(this->numberInLayer);
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

double RosenblattPerceptron::getPreviousOutput(){
  return(this->previousOutput);
}

double RosenblattPerceptron::getBias(){
  return(this->bias);
}

double RosenblattPerceptron::getPreviousBias(){
  return(this->previousBias);
}

double RosenblattPerceptron::getLearningRate(){
  return(this->learningRate);
}

double RosenblattPerceptron::getMomentumRate(){
  return(this->momentumRate);
}

vector<double> RosenblattPerceptron::getWeights(){
  return(this->weights);
}

double RosenblattPerceptron::getSpecificWeight(int number){
  return(this->weights[number]);
}

vector<double> RosenblattPerceptron::getPreviousWeights(){
  return(this->previousWeights);
}

double RosenblattPerceptron::getSpecificPreviousWeight(int number){
  return(this->previousWeights[number]);
}

/**************END GETTERS*****************************************/

/**************START SETTERS**************************************/

void RosenblattPerceptron::setLayer(int layer){
  this->layer = layer;
}

void RosenblattPerceptron::setNumberInLayer(int number){
  this->numberInLayer = number;
}

void RosenblattPerceptron::setLocalGradient(double gradient){
  this->localGradient = gradient;
}

void RosenblattPerceptron::setLocalField(double field){
  this->localField = field;
}

void RosenblattPerceptron::setOutput(double output){
  this->output = output;
}

void RosenblattPerceptron::setPreviousOutput(double prevOutput){
  this->previousOutput = prevOutput;
}

void RosenblattPerceptron::setBias(double bias){
  this->bias = bias;
}

void RosenblattPerceptron::setPreviousBias(double prevBias){
  this->previousBias = prevBias;
}

void RosenblattPerceptron::setLearningRate(double learningRate){
  this->learningRate = learningRate;
}

void RosenblattPerceptron::setMomentumRate(double momentumRate){
  this->momentumRate = momentumRate;
}

void RosenblattPerceptron::setWeights(vector<double> weights){
  this->weights = weights;
}

void RosenblattPerceptron::setSpecificWeight(int number, double value){
  this->weights[number] = value;
}

void RosenblattPerceptron::setPreviousWeights(vector<double> previousWeights){
  this->previousWeights = previousWeights;
}

void RosenblattPerceptron::setSpecificPreviousWeight(int number, double value){
  this->previousWeights[number] = value;
}
/******************END SETTERS************************************/

/**************START FUNCTIONAL METHODS***************************/

/*


*/
void RosenblattPerceptron::calculateLocalField(vector<double> inputData){

  if(inputData.size() != this->weights.size()){
    cout<<"You dun goofed... calculateLocalField"<<endl;
    exit(1);
  }

  for(int i = 0; i < inputData.size(); i++){
    //cout<<"Weight : " << weights[i] << " Input: " << inputData[i] << endl;
    this->localField += (weights[i])*(inputData[i]);
  }

  //cout<<"Bias : " << this->getBias() << endl;
  this->localField += this->getBias();
  //cout<<"Local field at "<< this->getLayer() << ","<< this->getNumber()<< " is " << this->getLocalField()<<endl;
  }

void RosenblattPerceptron::calculateOutput(){
  //Set the previous output equal to the current
  this->previousOutput = this->output;

  this->output = 1 / (1 + exp(-(this->getLocalField())));
  //cout<< "Output at "<< this->getLayer() << ","<< this->getNumber()<< " is " << this->getOutput()<< endl;
}

void RosenblattPerceptron::calculateLocalGradient_output(double error){
  this->localGradient = (error) * (this->getOutput()) * (1 - this->getOutput());
}

void RosenblattPerceptron::calculateLocalGradient_hidden(vector<double> previousLayerGradients, vector<double> previousLayerWeights){
  //Summation
  double summation = 0;
  for(int i = 0; i < previousLayerGradients.size(); i++){
    summation += (previousLayerGradients[i] * previousLayerWeights[i]);
  }
  //Gradient = Y(v)*(1 - Y(v))*(summation)
  this->localGradient = (this->getOutput()) * (1 - this->getOutput()) * summation;
}

void RosenblattPerceptron::calculateWeight(vector<double> previousLayerOutput){
  //For all of the weights of the neuron

  for(int i = 0; i < this->getWeights().size() - 1; i++){
    double previousWeightsTemp;
    previousWeightsTemp = this->getSpecificWeight(i);
  //  cout<<"Previous weight : "<<previousWeightsTemp<<endl;
    //Save the previous weight
    //Is this the first time saving previous weights?
    if(this->previousWeights.size() < this->weights.size()){
  //    cout<<"First time updating weights"<<endl;
      //Update the current
      this->weights[i] = this->getSpecificWeight(i) + (this->getLearningRate() * this->getLocalGradient() * previousLayerOutput[i]);
    //  cout<<"Updated weight : "<< this->getWeight(i)<<endl;
      //Update the previous
      this->previousWeights.push_back(previousWeightsTemp);
    }else{
      //Update the current
      this->weights[i] = this->getSpecificWeight(i) + (this->getMomentumRate() * (this->getSpecificWeight(i) - this->getSpeciPreviousWeight(i))) + (this->getLearningRate() * this->getLocalGradient() * previousLayerOutput[i]);
  //    cout<<"Updated weight : "<< this->bias<<endl;
      //Update the previous
      this->previousWeights[i] = previousWeightsTemp;
    }
  }
}

void RosenblattPerceptron::calculateBias(){
  double temp = this->getBias();
  if(this->previousBias == 0){
    //cout<<"First time updating bias"<<endl;
    this->bias = this->getBias() + (this->getLearningRate() * this->getLocalGradient());
    //cout<<"Updated bias : "<< this->bias<<endl;
  }else{
    this->bias = this->getBias() + (this->getMomentumRate() * (this->getBias() - this->getPreviousBias())) + (this->getLearningRate() * this->getLocalGradient());
  //  cout<<"Updated bias : "<< this->bias<<endl;
  }

  this->previousBias = temp;
}


/******************************************************************************
                END RosenblattPerceptron
******************************************************************************/
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

vector<double> Network::getInputs(){
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
  //Set the input data
  this->inputs = inputTrainingData;
  cout<<"inputTrainingData : " << inputTrainingData[0]<< endl;
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
  for(int i = this->getNumberOfLayers() - 1; i >= 0; i--){
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
        //Calculate the local gradient given the gradients and weights of the layer before
        //Collect the weights of the layer above and put them in a vector.
        vector<double> prevWeights;
        for(int k = 0; k < this->getNeuronsInLayer(i+1); k++){
          prevWeights.push_back(this->neurons[i+1][k].getWeight(j));
        }

        vector<double> tempGradients;
        for(int k = 0; k < this->getNeuronsInLayer(i+1); k++){
          tempGradients.push_back(this->neurons[i+1][k].getLocalGradient());
        }

        this->neurons[i][j].calculateLocalGradient_hidden(tempGradients, prevWeights);

        //Add that gradient to the temp vector
        temp.push_back(this->neurons[i][j].getLocalGradient());
      }
    }
    //Record those gradients in the network
    this->neuronGradients.push_back(temp);

    //Clear the temp vector
    temp.clear();

  }
    //Calculate change in weights and bias//

    //For each layer in the network starting with the output
    for(int i = this->getNumberOfLayers() -1; i >=0; i--){
      //For each neuron in that layer
      for(int j = 0; j < this->getNeuronsInLayer(i); j++){
        //Update bias

        this->neurons[i][j].updateBias();
        //Update weight
        if(i == 0){
          vector<double> temp = this->inputs;

        //  cout<<"pre "<<temp.size()<<endl;
          this->neurons[i][j].updateWeight(temp);

        }else{
          this->neurons[i][j].updateWeight(this->getOutputs()[i-1]);
        }
      }
    }

}

void Network::calculateError(vector<double> outputTrainingData){
  for(int i = 0; i < outputTrainingData.size(); i++){
    this->error.push_back(outputTrainingData[i] - this->outputs[this->numberOfLayers - 1][i]);
    //cout<<"Error is " << this->error[i] << endl;
  }
}


void Network::printGradients(){
  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->layerInfo[i]; j++){
      cout << "Gradient "<<i<<","<<j<<": "<< this->neurons[i][j].getLocalGradient() << endl;
    }
  }
}

vector<double> Network::getGradients(int layer){
  return(this->neuronGradients[layer]);
}
