/*

Author: Marshall Lindsay
Email: mblgh6@mail.missouri.edu
Class Code: CS4770
Project Name: Lab1PartA

*/

#include "neurons.h"

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
  this->setCurrentOutput(0);
  this->setPreviousOutput(0);
  this->setNextOutput(0);
  this->setCurrentBias(0);
  this->setPreviousBias(0);
  this->setNextBias(0);
  this->setLearningRate(0);
  this->setMomentumRate(0);
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

double RosenblattPerceptron::getCurrentOutput(){
  return(this->currentOutput);
}

double RosenblattPerceptron::getPreviousOutput(){
  return(this->previousOutput);
}

double RosenblattPerceptron::getNextOutput(){
  return(this->nextOutput);
}

double RosenblattPerceptron::getCurrentBias(){
  return(this->currentBias);
}

double RosenblattPerceptron::getPreviousBias(){
  return(this->previousBias);
}

double RosenblattPerceptron::getNextBias(){
  return(this->nextBias);
}

double RosenblattPerceptron::getLearningRate(){
  return(this->learningRate);
}

double RosenblattPerceptron::getMomentumRate(){
  return(this->momentumRate);
}

vector<double> RosenblattPerceptron::getCurrentWeights(){
  return(this->currentWeights);
}

double RosenblattPerceptron::getSpecificCurrentWeight(int number){
  return(this->currentWeights[number]);
}

vector<double> RosenblattPerceptron::getPreviousWeights(){
  return(this->previousWeights);
}

double RosenblattPerceptron::getSpecificPreviousWeight(int number){
  return(this->previousWeights[number]);
}

vector<double> RosenblattPerceptron::getNextWeights(){
  return(this->nextWeights);
}

double RosenblattPerceptron::getSpecificNextWeight(int number){
  return(this->nextWeights[number]);
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

void RosenblattPerceptron::setCurrentOutput(double currentOutput){
  this->currentOutput = currentOutput;
}

void RosenblattPerceptron::setPreviousOutput(double previousOutput){
  this->previousOutput = previousOutput;
}

void RosenblattPerceptron::setNextOutput(double nextOutput){
  this->nextOutput = nextOutput;
}

void RosenblattPerceptron::setCurrentBias(double currentBias){
  this->currentBias = currentBias;
}

void RosenblattPerceptron::setPreviousBias(double previousBias){
  this->previousBias = previousBias;
}

void RosenblattPerceptron::setNextBias(double nextBias){
  this->nextBias = nextBias;
}

void RosenblattPerceptron::setLearningRate(double learningRate){
  this->learningRate = learningRate;
}

void RosenblattPerceptron::setMomentumRate(double momentumRate){
  this->momentumRate = momentumRate;
}

void RosenblattPerceptron::setCurrentWeights(vector<double> currentWeights){
  this->currentWeights = currentWeights;
}

void RosenblattPerceptron::setSpecificCurrentWeight(int number, double value){
  this->currentWeights[number] = value;
}

void RosenblattPerceptron::setPreviousWeights(vector<double> previousWeights){
  this->previousWeights = previousWeights;
}

void RosenblattPerceptron::setSpecificPreviousWeight(int number, double value){
  this->previousWeights[number] = value;
}

void RosenblattPerceptron::setNextWeights(vector<double> nextWeights){
  this->nextWeights = nextWeights;
}

void RosenblattPerceptron::setSpecificNextWeight(int number, double value){
  this->nextWeights[number] = value;
}
/******************END SETTERS************************************/

/**************START FUNCTIONAL METHODS***************************/

/*


*/

//Fixed GOOD
void RosenblattPerceptron::calculateLocalField(vector<double> inputData){
  if(inputData.size() != this->currentWeights.size()){
    cout<<"You dun goofed... calculateLocalField"<<endl;
    exit(1);
  }
  this->localField = 0;
  for(int i = 0; i < inputData.size(); i++){
    this->localField += (this->currentWeights[i])*(inputData[i]);
  }
  this->localField += this->getCurrentBias();
}


//Fixed GOOD
void RosenblattPerceptron::calculateCurrentOutput(){
  this->currentOutput = 1 / (1 + exp(-(this->getLocalField())));
}

//Fixed GOOD
void RosenblattPerceptron::calculateLocalGradient_output(double error){
  //cout<<"Error "<<error<<endl;
  //cout<<"Output " << this->getCurrentOutput()<<endl;
  this->localGradient = (error) * (this->getCurrentOutput()) * (1 - this->getCurrentOutput());
  //cout<<"Output Local Gradient" <<this->localGradient<<endl;
}

//Fixed - MIght need to fix again
void RosenblattPerceptron::calculateLocalGradient_hidden(vector<double> nextLayerGradients, vector<double> nextLayerWeights){
  //Summation
  double summation = 0;
  for(int i = 0; i < nextLayerGradients.size(); i++){
    summation += (nextLayerGradients[i] * nextLayerWeights[i]);
  }
  //Derivative portion
  this->localGradient = (this->getCurrentOutput()) * (1 - this->getCurrentOutput()) * summation; //Derivative of the phi(v(k)) * summation
}

//Fixed
void RosenblattPerceptron::calculateNextWeight(vector<double> previousLayerOutput){
  for(int weightNumber = 0; weightNumber < this->getCurrentWeights().size(); weightNumber++){
    //Momentum term
    double momentum = this->getMomentumRate() * (this->getSpecificCurrentWeight(weightNumber) - this->getSpecificPreviousWeight(weightNumber));
    //Learning term
    double learning = this->getLearningRate() * this->getLocalGradient() * previousLayerOutput[weightNumber];
    //Delta
    double deltaWeight = momentum + learning;
    //Set valu
    this->setSpecificNextWeight(weightNumber, this->getSpecificCurrentWeight(weightNumber) + deltaWeight);
  }
}

//Fixed
void RosenblattPerceptron::calculateNextBias(){
  //Momentum term
  double momentumTerm = this->getMomentumRate() * (this->getCurrentBias() - this->getPreviousBias());
  //Learning term
  double learningTerm = this->getLearningRate() * this->getLocalGradient();
  //Delta
  double deltaBias = momentumTerm + learningTerm;
  //Set value
  this->setNextBias(this->getCurrentBias() + deltaBias);
}


/******************************************************************************
                END RosenblattPerceptron
******************************************************************************/

/******************************************************************************
                START Network
******************************************************************************/
Network::Network(vector<int> layerInfo, vector<vector<double>> initialWeights, vector<double> biasVector, double learning, double momentum){
  this->setNumberOfLayers(layerInfo.size());
  this->setLayerInfo(layerInfo);
  this->deltaMSE = 0.0;
  //Set up the framework
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    vector<RosenblattPerceptron> tempLayerOfNeurons;
    for(int number = 0; number < layerInfo[layer]; number++){
      tempLayerOfNeurons.push_back(RosenblattPerceptron(layer,number));
    }
    this->allNeurons.push_back(tempLayerOfNeurons);
  }

  //Set the weights
  int counter = 0;
  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->getNeuronsInLayer(i); j++){
      this->allNeurons[i][j].setCurrentWeights(initialWeights[counter]);
      this->allNeurons[i][j].setPreviousWeights(initialWeights[counter]);
      this->allNeurons[i][j].setNextWeights(initialWeights[counter]);
      this->allNeurons[i][j].setCurrentBias(biasVector[counter]);
      this->allNeurons[i][j].setPreviousBias(biasVector[counter]);
      this->allNeurons[i][j].setNextBias(biasVector[counter]);
      this->allNeurons[i][j].setLearningRate(learning);
      this->allNeurons[i][j].setMomentumRate(momentum);
      counter++;
    }
  }


}

Network::Network(vector<int> layerInfo, double learning, double momentum, int inputs){
  this->setNumberOfLayers(layerInfo.size());
  this->setLayerInfo(layerInfo);
  this->deltaMSE = 0.0;

  //Set up the framework
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    vector<RosenblattPerceptron> tempLayerOfNeurons;
    for(int number = 0; number < layerInfo[layer]; number++){
      tempLayerOfNeurons.push_back(RosenblattPerceptron(layer,number));
    }
    this->allNeurons.push_back(tempLayerOfNeurons);
  }
  for(int i = 0; i < this->getNumberOfLayers(); i++){
    for(int j = 0; j < this->getNeuronsInLayer(i); j++){
      this->allNeurons[i][j].setLearningRate(learning);
      this->allNeurons[i][j].setMomentumRate(momentum);
    }
  this->numberOfInputs = inputs;
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
    tempError.push_back(this->getOutputs()[i] - this->allNeurons[lastLayer][i].getCurrentOutput());
  }
  this->error = tempError;
}

void Network::calculateSumSquaredError(){
    //Summation
    double summation = 0;
    for(int i = 0; i < this->error.size(); i++){
        summation += pow((this->error[i]),2);
    }
    this->sumSquaredError.push_back(summation);
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

vector<double> Network::getSumSquaredError(){
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

double Network::getMSE(){
  return(this->MSE);
}

double Network::getDeltaMSE(){
  return(this->deltaMSE);
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

void Network::setSumSquaredError(vector<double> sumSquaredError){
  this->sumSquaredError = sumSquaredError;
}

void Network::setNumberOfLayers(double numLayers){
  this->numberOfLayers = numLayers;
}

void Network::setLayerInfo(vector<int> layerInfo){
  this->layerInfo = layerInfo;
}

void Network::setMSE(double value){
  this->MSE = value;
}

void Network::setDeltaMSE(double value){
  this->deltaMSE = value;
}

//End SETTERS

//Start functional METHODS

void Network::train(){
  //Forward computation
  vector<double> inputVector;
  inputVector = this->getInputs();

  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    //Calculate localField for the first layer
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      this->allNeurons[layer][number].calculateLocalField(inputVector);
      //cout<<this->allNeurons[layer][number].getLocalField()<<endl;
    }

    //Calculate output of the first layer
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      this->allNeurons[layer][number].calculateCurrentOutput();
    }

    //Clear first.
    inputVector.clear();
    for(int i = 0; i < this->getNeuronsInLayer(layer); i++){
      inputVector.push_back(this->allNeurons[layer][i].getCurrentOutput());
    }
  }

  //Caclulate the errors
  this->calculateError();

  this->calculateSumSquaredError();

  //Back propagation
  //Calculate local gradients
  for(int layer = this->getNumberOfLayers() - 1; layer >=0; layer--){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      if(layer == this->getNumberOfLayers() -1){ //output layer
        //cout<<"For neuron " << layer << " " << number << ":" << endl;
        this->allNeurons[layer][number].calculateLocalGradient_output(this->getError()[number]);
      }else{
        //Grab the next layer gradients
        //cout<<"For neuron " << layer << " " << number << ":" << endl;
        vector<double> tempGradients;
        for(int i = 0; i < this->getNeuronsInLayer(layer+1); i++){
          tempGradients.push_back(this->allNeurons[layer+1][i].getLocalGradient());
        //  cout<<"tempGradient "<< tempGradients[i] << endl;
        }
        //Grab the next weights
        vector<double> tempWeights;
        for(int i = 0; i < this->getNeuronsInLayer(layer+1); i++){
          tempWeights.push_back(this->allNeurons[layer+1][i].getCurrentWeights()[number]);
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
      this->allNeurons[layer][number].calculateNextBias();
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
          prevOutputs.push_back(this->allNeurons[layer-1][i].getCurrentOutput());
        }
      }

      this->allNeurons[layer][number].calculateNextWeight(prevOutputs);
    }
  }

  //Update the network with the calculated values
  this->update();

}

void Network::run(){
  //Forward computation
  vector<double> inputVector;
  inputVector = this->getInputs();

  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    //Calculate localField for the first layer
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      this->allNeurons[layer][number].calculateLocalField(inputVector);
    }

    //Calculate output of the first layer
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      this->allNeurons[layer][number].calculateCurrentOutput();
    }

    //Clear first.
    inputVector.clear();
    for(int i = 0; i < this->getNeuronsInLayer(layer); i++){
      inputVector.push_back(this->allNeurons[layer][i].getCurrentOutput());
    }
  }
  this->outputs.clear();
  vector<double> tempVector;
  for(int i = 0; i < this->getLayerInfo()[this->getNumberOfLayers()-1]; i++){
    tempVector.push_back(this->allNeurons[this->getNumberOfLayers()-1][i].getCurrentOutput());
  }
  this->setOutputs(tempVector);
}

void Network::printWeights(){
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      cout<<"Neuron ("<<layer<<","<<number<<")"<<endl;
      for(int i = 0; i < this->allNeurons[layer][number].getCurrentWeights().size(); i++){
        cout<<"Weight: " << i << " = " << this->allNeurons[layer][number].getSpecificCurrentWeight(i)<<endl;
      }
    }
  }
}
void Network::printBias(){
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      cout<<"Neuron ("<<layer<<","<<number<<")"<<endl;
      cout<<"Bias: "<<this->allNeurons[layer][number].getCurrentBias()<<endl;
    }
  }
}

void Network::update(){
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      this->allNeurons[layer][number].setPreviousWeights(this->allNeurons[layer][number].getCurrentWeights());

      this->allNeurons[layer][number].setCurrentWeights(this->allNeurons[layer][number].getNextWeights());

      this->allNeurons[layer][number].setPreviousBias(this->allNeurons[layer][number].getCurrentBias());

      this->allNeurons[layer][number].setCurrentBias(this->allNeurons[layer][number].getNextBias());
    }
  }
}

void Network::printOutputs(){
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      cout<<"Neuron ("<<layer<<","<<number<<")"<<endl;
      cout<<"Output: "<<this->allNeurons[layer][number].getCurrentOutput()<<endl;
    }
  }
}

void Network::printErrors(){
  for(int number = 0; number < this->getError().size(); number++){
      cout<<"Error: "<<this->getError()[number]<<endl;
  }
}

void Network::printMSE(){

  cout<<"MSE : "<< this->getMSE() <<endl;

}

void Network::calculateMSE(){

  double summation = 0;

  for(int i = 0; i < this->sumSquaredError.size(); i++){
    summation += this->sumSquaredError[i];
  }
  this->setDeltaMSE(this->getMSE() - (summation / (2*this->sumSquaredError.size())));
  this->setDeltaMSE(abs(this->getDeltaMSE()));
  this->setMSE(summation / (2*this->sumSquaredError.size()));
}

void Network::printOutputOutputs(){
  //cout<<this->getNumberOfLayers() - 1<<endl;
  for(int number = 0; number < this->getNeuronsInLayer(this->getNumberOfLayers() -1); number++){
    cout<<"Neuron ("<<this->getNumberOfLayers() -1<<","<<number<<")"<<endl;
    cout<<"Output: "<<this->allNeurons[this->getNumberOfLayers()-1][number].getCurrentOutput()<<endl;
  }
}

void Network::randomizeWeights(){
  srand(time(NULL));
  vector<double> randomWeights;

  double value;
  for(int layer = 0; layer < this->getNumberOfLayers(); layer++){
    for(int number = 0; number < this->getNeuronsInLayer(layer); number++){
      double value = (double)(((double)(rand() % 4000) - 2000) / 1000);
      this->allNeurons[layer][number].setCurrentBias(value);
      this->allNeurons[layer][number].setPreviousBias(value);
      this->allNeurons[layer][number].setNextBias(value);


      if(layer == 0){
        for(int i = 0; i < this->numberOfInputs; i++){
          value = (double)(((double)(rand() % 4000) - 2000) / 1000);
          randomWeights.push_back(value);
        }
        this->allNeurons[layer][number].setCurrentWeights(randomWeights);
        this->allNeurons[layer][number].setPreviousWeights(randomWeights);
        this->allNeurons[layer][number].setNextWeights(randomWeights);
        randomWeights.clear();
      }else{
        for(int i = 0; i < this->getNeuronsInLayer(layer-1); i++){
          value = (double)(((double)(rand() % 4000) - 2000) / 1000);
          randomWeights.push_back(value);
        }
        this->allNeurons[layer][number].setCurrentWeights(randomWeights);
        this->allNeurons[layer][number].setPreviousWeights(randomWeights);
        this->allNeurons[layer][number].setNextWeights(randomWeights);
        randomWeights.clear();
      }
    }
  }
}
//End funtional METHODS
