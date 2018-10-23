/*

Author: Marshall Lindsay
Email: mblgh6@mail.missouri.edu
Class Code: CS4770
Project Name: Lab1PartA

*/

#ifndef NEURONS_H_
#define NEURONS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;
/*
Brief: The rosenblattPerceptron class is used to describe the features
associated with, you guess it, the rosenblatt perceptron.
*/

class RosenblattPerceptron{
private:
  //Where is the neuron in the network?
  int layer;
  int numberInLayer;

  //What is the local gradient?
  double localGradient;
  //What is the local field?
  double localField;
  //What is the current outpu?
  double currentOutput;
  //What was the previous output?
  double previousOutput;
  //What is the next output?
  double nextOutput;
  //What is the current bias?
  double currentBias;
  //What is the previous bias?
  double previousBias;
  //What is the next bias?
  double nextBias;
  //What is the learning rate?
  double learningRate;
  //What is the momentum rate?
  double momentumRate;
  //What are the current weights?
  vector<double> currentWeights;
  //What are the previous weights?
  vector<double> previousWeights;
  //What are the next weights?
  vector<double> nextWeights;

  void randomizeWeights(); //Initialize the weight vector with random values.. Not used for this lab

public:

  //How do we initialize.contstruct a neuron?
  RosenblattPerceptron(int layer, int number);
  //How do we destruct a neuron?
  ~RosenblattPerceptron();

  //Getters for all the members
  int getLayer();
  int getNumberInLayer();
  double getLocalGradient();
  double getLocalField();
  double getCurrentOutput();
  double getPreviousOutput();
  double getNextOutput();
  double getCurrentBias();
  double getPreviousBias();
  double getNextBias();
  double getLearningRate();
  double getMomentumRate();
  vector<double> getCurrentWeights();
  double getSpecificCurrentWeight(int number);
  vector<double> getPreviousWeights();
  double getSpecificPreviousWeight(int number);
  vector<double> getNextWeights();
  double getSpecificNextWeight(int number);

  //Setters for all of my members
  void setLayer(int layer);
  void setNumberInLayer(int number);
  void setLocalGradient(double gradient);
  void setLocalField(double field);
  void setCurrentOutput(double currentOutput);
  void setPreviousOutput(double previousOutput);
  void setNextOutput(double nextOutput);
  void setCurrentBias(double currentBias);
  void setPreviousBias(double previousBias);
  void setNextBias(double nextBias);
  void setLearningRate(double learningRate);
  void setMomentumRate(double momentumRate);
  void setCurrentWeights(vector<double> currentWeights);
  void setSpecificCurrentWeight(int number, double value);
  void setPreviousWeights(vector<double> previousWeights);
  void setSpecificPreviousWeight(int number, double value);
  void setNextWeights(vector<double> nextWeights);
  void setSpecificNextWeight(int number, double value);

  //Functional methods
  void calculateLocalField(vector<double> inputData);
  void calculateCurrentOutput();
  void calculateLocalGradient_output(double error);
  void calculateLocalGradient_hidden(vector<double> nextLayerGradients, vector<double> nextLayerWeights);
  void calculateNextWeight(vector<double> previousLayerOutput);
  void calculateNextBias();

};


class Network {
private:
  //What are my inputs for a single run?
  vector<double> inputs;
  //What are my outputs for a single run?
  vector<double> outputs;
  //What are the errors for a single run?
  vector<double> error;
  //What is the summed squared errors for the run?
  vector<double> sumSquaredError;
  //What is the MSE?
  double MSE;
  //How much is the MSE changing
  double deltaMSE;
  //How many layers are in the network?
  int numberOfLayers;
  //How many neurons are in each layer?
  vector<int> layerInfo;

  int numberOfInputs;
  //What neurons?
  vector<vector<RosenblattPerceptron>> allNeurons;

  //Private functional methods
  void addNeuron(RosenblattPerceptron neuron);
  void calculateError();
  void calculateSumSquaredError();

public:
  //How do we initialize/construct a network?
  Network(vector<int> layerInfo, vector<vector<double>> initialWeights, vector<double> biasVector, double learning, double momentum);
  Network(vector<int> layerInfo, double learning, double momentum, int inputs);

  //How do we destruct a network?
  ~Network();

  //Getters for all the members
  vector<double> getInputs();
  vector<double> getOutputs();
  vector<double> getError();
  vector<double> getSumSquaredError();
  int getNumberOfLayers();
  vector<int> getLayerInfo();
  int getNeuronsInLayer(int layer);
  RosenblattPerceptron getNeuron(int layer, int number);
  vector<RosenblattPerceptron> getLayerOfNeurons(int layer);
  vector<vector<RosenblattPerceptron>> getAllNeurons();
  double getMSE();
  double getDeltaMSE();

  //Setters for all the members (I might need to change the variable names)
  void setInputs(vector<double> inputs);
  void setOutputs(vector<double> outputs);
  void setError(vector<double> errors);     //I don't think this will ever be used
  void setSumSquaredError(vector<double> sumSquaredError); //Probably never used
  void setNumberOfLayers(double numLayers);
  void setLayerInfo(vector<int> layerInfo);
  void setMSE(double value);
  void setDeltaMSE(double value);

  //Functional methods
  void randomizeWeights();
  void train();
  void run(); //Same idea as train just with no backprop.
  void printWeights();
  void printBias();
  void printErrors();
  void printOutputs();
  void update();
  void printMSE();
  void calculateMSE();
  void printOutputOutputs();
  void randomizeWeights();
};

#endif // NEURONS_H_
