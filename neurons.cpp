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
  //  cout<<"Weight : " << weights[i] << endl;
  //  cout<<"Input " << inputData[i] << endl;
  }

  //cout<<"Bias : " << this->getBias() << endl;
  this->localField += this->getBias();
//  cout<<"Bias : " << this->getBias() << endl;
//  cout<<"Local field at "<< this->getLayer() << ","<< this->getNumberInLayer()<< " is " << this->getLocalField()<<endl;
  }

void RosenblattPerceptron::calculateOutput(){
  //Set the previous output equal to the current
  this->previousOutput = this->output;
//  cout<<"Local field " << this->getLocalField() <<endl;
  this->output = 1 / (1 + exp(-(this->getLocalField())));
  //cout<<"Output " << this->getOutput() << endl;
  //cout<< "Output at "<< this->getLayer() << ","<< this->getNumberInLayer()<< " is " << this->getOutput()<< endl;
}

void RosenblattPerceptron::calculateLocalGradient_output(double error){
  //cout<< "Error " << error << endl;
  //cout<< "Output " << this->getOutput() << endl;
  this->localGradient = (error) * (this->getOutput()) * (1 - this->getOutput());
//  cout<< "Local gradient output "<< this->getLayer() << ","<< this->getNumberInLayer()<< " is " << this->getLocalGradient()<< endl;

}

void RosenblattPerceptron::calculateLocalGradient_hidden(vector<double> previousLayerGradients, vector<double> previousLayerWeights){
  //Summation
  double summation = 0;
  for(int i = 0; i < previousLayerGradients.size(); i++){
    cout<<"Previous gradient " << i << ":" << previousLayerGradients[i]<<endl;
    cout<<"Previous weight " << i << ":" << previousLayerWeights[i]<<endl;
    summation += (previousLayerGradients[i] * previousLayerWeights[i]);

  }
//  cout<<"Summation " << summation << endl;
  //Gradient = Y(v)*(1 - Y(v))*(summation)
  //cout<<"Local gradient summation hidden is " << summation << endl;
  //cout<<"Local gradient output used is " << this->getOutput() << endl;
//  cout<<"Output " << this->getOutput() << endl;
  this->localGradient = (this->getOutput()) * (1 - this->getOutput()) * summation;
//  cout<<"Local Gradient " << this->getLocalGradient() <<endl;
  //cout<<"Local gradient hidden final is " << this->getLocalGradient() << endl;
}

void RosenblattPerceptron::calculateWeight(vector<double> previousLayerOutput){
  //cout<<"At Neuron " << this->getLayer() << "," << this->getNumberInLayer() << endl;
  for(int weightNumber = 0; weightNumber < this->getWeights().size(); weightNumber++){
    //Momentum term
    cout<<"Momentum rate " << this->getMomentumRate() <<endl;
    cout<<"Current weight " << this->getWeights()[weightNumber] <<endl;
    cout<<"Previous weight " << this->getPreviousWeights()[weightNumber] <<endl;
    double momentum = this->getMomentumRate() * (this->getWeights()[weightNumber] - this->getPreviousWeights()[weightNumber]);
    cout<<"Weight momentum term: " << momentum << endl;
    this->setSpecificPreviousWeight(weightNumber, this->getSpecificWeight(weightNumber));

    //Learning ter
    cout<<"Learning rate " << this->getLearningRate() << endl;
    cout<<"Local gradient " << this->getLocalGradient() << endl;
    cout<<"Previous layer output " << previousLayerOutput[weightNumber] <<endl;
    double learning = this->getLearningRate() * this->getLocalGradient() * previousLayerOutput[weightNumber];
    cout<<"Weight learning term: " << learning << endl;

    //Delta
    double deltaWeight = momentum + learning;
    cout<<"Delta weight " << deltaWeight << endl;

    this->setSpecificWeight(weightNumber, this->getSpecificWeight(weightNumber) + deltaWeight);
    cout<<"New weight: " << this->getSpecificWeight(weightNumber) << endl;
    cout<<"Old weight: " << this->getSpecificPreviousWeight(weightNumber) << endl;
  }
}

void RosenblattPerceptron::calculateBias(){
  //Delta bias:
  //Calculate the momentum term
  //cout<<"Current bias " << this->getBias() << endl;
  //cout<<"Previous bias " << this->getPreviousBias() << endl;
  double momentumTerm = this->getMomentumRate() * (this->getBias() - this->getPreviousBias());
  //cout<<"Bias momentumTerm: " << momentumTerm <<endl;

  //Save current bias to the previous bias
  this->setPreviousBias(this->getBias());

  //Calculate learning term
//  cout<<"Learning rate: " << this->getLearningRate() << endl;
//  cout<<"Local gradient " << this->getLocalGradient() << endl;
  double learningTerm = this->getLearningRate() * this->getLocalGradient();
  //cout<<"Bias learningTerm: " << learningTerm << endl;

  double deltaBias = momentumTerm + learningTerm;
//  cout<< "Delta bias " << deltaBias << endl;
  this->setBias(this->getBias() + deltaBias);
//  cout<<"New bias : " << this->getBias() << endl;
//  cout<<"Old bias : " << this->getPreviousBias() << endl;
}


/******************************************************************************
                END RosenblattPerceptron
******************************************************************************/
Network::Network(vector<int> layerInfo, vector<vector<double>> initialWeights, vector<double> biasVector, double learning, double momentum){
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
  int counter = 0;
  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->getNeuronsInLayer(i); j++){
      this->allNeurons[i][j].setWeights(initialWeights[counter]);
      this->allNeurons[i][j].setPreviousWeights(initialWeights[counter]);
      this->allNeurons[i][j].setBias(biasVector[counter]);
      this->allNeurons[i][j].setPreviousBias(biasVector[counter]);
      this->allNeurons[i][j].setLearningRate(learning);
      this->allNeurons[i][j].setMomentumRate(momentum);
      //cout<<"Bias at "<< i << "," <<j<<" : "<< biasVector[counter] <<endl;
      counter++;
    }
  }


}
//Private METHODS
void Network::addNeuron(RosenblattPerceptron neuron){
  //this->allNeurons.push_back(neuron);
}

void Network::calculateError(){

  int lastLayer = this->getNumberOfLayers() - 1;
  vector<double> tempError;
  for(int i = 0; i < this->getNeuronsInLayer(lastLayer); i++){
  //  cout<<"Expected Output : " << this->getOutputs()[i] << endl;
  //  cout<<"Output " << this->allNeurons[lastLayer][i].getOutput() << endl;
    tempError.push_back(this->getOutputs()[i] - this->allNeurons[lastLayer][i].getOutput());
  //  cout<<"Error " << tempError[i]<<endl;
  }
  this->error = tempError;

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
  //Forward computation
  //Calculate localField for the first layer
  for(int number = 0; number < this->getNeuronsInLayer(0); number++){
    this->allNeurons[0][number].calculateLocalField(this->getInputs());
  }

  //Calculate output of the first layer
  for(int number = 0; number < this->getNeuronsInLayer(0); number++){
    this->allNeurons[0][number].calculateOutput();
  }

  //Build a temp vector of the previous layers outpus
  vector<double> tempVector;
  for(int i = 0; i < this->getNeuronsInLayer(0); i++){
    tempVector.push_back(this->allNeurons[0][i].getOutput());
    //cout<<tempVector[i]<<endl;
  }

  //Calculate localField for the second layer
  for(int number = 0; number < this->getNeuronsInLayer(1); number++){
    this->allNeurons[1][number].calculateLocalField(tempVector);
  }
  tempVector.clear();

  //Calculate output of the second layer
  for(int number = 0; number < this->getNeuronsInLayer(1); number++){
    this->allNeurons[1][number].calculateOutput();
  }

  //Caclulate the errors
  this->calculateError();

  //Caclulate sum squared error
  //this->calculateSumSquaredError();

  //Back propagation

  //Calculate local gradients
  for(int layer = this->getNumberOfLayers() - 1; layer >=0; layer--){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      if(layer == this->getNumberOfLayers() -1){
        //cout<<"For neuron " << layer << " " << number << ":" << endl;
        this->allNeurons[layer][number].calculateLocalGradient_output(this->getError()[number]);
      }else{
        //Grab the previous gradients
        //cout<<"For neuron " << layer << " " << number << ":" << endl;
        vector<double> tempGradients;
        for(int i = 0; i < this->getNeuronsInLayer(layer+1); i++){
          tempGradients.push_back(this->allNeurons[layer+1][i].getLocalGradient());
        //  cout<<"tempGradient "<< tempGradients[i] << endl;
        }
        //Grab the previous weights
        vector<double> tempWeights;
        for(int i = 0; i < this->getNeuronsInLayer(layer+1); i++){
          tempWeights.push_back(this->allNeurons[layer+1][i].getWeights()[number]);
        //  cout<<"tempWeights " << tempWeights[i] << endl;
        }
        //Send to the calc function for a hidden neuron
        this->allNeurons[layer][number].calculateLocalGradient_hidden(tempGradients, tempWeights);
      }
    }
  }

  //Calculate new bias's
  for(int layer = this->getNumberOfLayers() -1; layer >=0; layer--){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      this->allNeurons[layer][number].calculateBias();
    }
  }

  //Calculate new weights
  for(int layer = this->getNumberOfLayers() -1; layer >=0; layer--){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      //Grab all the outputs from the previous layer and put in a vector
      vector<double> prevOutputs;

      if(layer == 0){
        prevOutputs = this->getInputs();
      }else{
        for(int i = 0; i < this->getNeuronsInLayer(layer -1); i++){
          prevOutputs.push_back(this->allNeurons[layer-1][i].getOutput());
        }
      }

      this->allNeurons[layer][number].calculateWeight(prevOutputs);
    }
  }


}

void Network::run(){

}

void Network::printWeights(){
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      cout<<"Neuron ("<<layer<<","<<number<<")"<<endl;
      for(int i = 0; i < this->allNeurons[layer][number].getWeights().size(); i++){
        cout<<"Weight: " << i << " = " << this->allNeurons[layer][number].getSpecificWeight(i)<<endl;
      }
    }
  }
}

//End funtional METHODS
