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
      this->weights[i] = this->getSpecificWeight(i) + (this->getMomentumRate() * (this->getSpecificWeight(i) - this->getSpecificPreviousWeight(i))) + (this->getLearningRate() * this->getLocalGradient() * previousLayerOutput[i]);
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
Network::Network(vector<int> layerInfo, vector<vector<double>> initialWeights){
  this->setNumberOfLayers(layerInfo.size());
  this->setLayerInfo(layerInfo);

  //Set up the framework
  //cout<<"Number of layers: "<<this->getNumberOfLayers()<<endl;
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    vector<RosenblattPerceptron> tempLayerOfNeurons;
    for(int number = 0; number < layerInfo[layer]; number++){
      tempLayerOfNeurons.push_back(RosenblattPerceptron(layer,number));
    }
    this->allNeurons.push_back(tempLayerOfNeurons);
  }
  //cout<<"Layer info 0 " << this->getNeuronsInLayer(0)<<endl;
  //cout<<"Layer info 1 " << this->getNeuronsInLayer(1)<<endl;

  //Set the weights

}

//Private METHODS
void Network::addNeuron(RosenblattPerceptron neuron){
  //this->allNeurons.push_back(neuron);
}

void Network::calculateError(){

}

void Network::calculateSumSquaredError(){

}

//End private METHODS

Network::~Network(){
  //cout << "Network destructor" << endl;
}

//Start Getters

vector<double> Network::getInputs(){
  return(this->inputs);
}

vector<double> Network::getOutputs(){
  return(this->outputs);
}

vector<double> Network::getError(){
  return(this->error);
}

double Network::getSumSquaredError(){
  return(this->sumSquaredError);
}

int Network::getNumberOfLayers(){
  return(this->numberOfLayers);
}

vector<int> Network::getLayerInfo(){
  return(this->layerInfo);
}

int Network::getNeuronsInLayer(int layer){
  return(this->layerInfo[layer]);
}

RosenblattPerceptron Network::getNeuron(int layer, int number){
  return(this->allNeurons[layer][number]);
}

vector<RosenblattPerceptron> Network::getLayerOfNeurons(int layer){
  return(this->allNeurons[layer]);
}

vector<vector<RosenblattPerceptron>> Network::getAllNeurons(){
  return(this->allNeurons);
}

//END GETTERS


//Start Setters
void Network::setInputs(vector<double> inputs){
  this->inputs = inputs;
}

void Network::setOutputs(vector<double> outputs){
  this->outputs = outputs;
}

void Network::setError(vector<double> errors){
  this->error = errors;
}

void Network::setSumSquaredError(double sumSquaredError){
  this->sumSquaredError = sumSquaredError;
}

void Network::setNumberOfLayers(double numLayers){
  this->numberOfLayers = numLayers;
}

void Network::setLayerInfo(vector<int> layerInfo){
  this->layerInfo = layerInfo;
}

//End SETTERS

//Start functional METHODS
void Network::train(){

}

void Network::run(){

}

//End funtional METHODS

/*
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
*/
