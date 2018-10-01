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
  //What is the outpu?
  double output;
  //What was the previous output?
  double previousOutput;
  //What is the bias?
  double bias;
  //What is the previous bias?
  double previousBias;
  //What is the learning rate?
  double learningRate;
  //What is the momentum rate?
  double momentumRate;
  //What are the weights?
  vector<double> weights;
  //What are the previous weights?
  vector<double> previousWeights;

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
  double getOutput();
  double getPreviousOutput();
  double getBias();
  double getPreviousBias();
  double getLearningRate();
  double getMomentumRate();
  vector<double> getWeights();
  double getSpecificWeight(int number);
  vector<double> getPreviousWeights();
  double getSpecificPreviousWeight(int number);

  //Setters for all of my members
  void setLayer(int layer);
  void setNumberInLayer(int number);
  void setLocalGradient(double gradient);
  void setLocalField(double field);
  void setOutput(double output);
  void setPreviousOutput(double prevOutput);
  void setBias(double bias);
  void setPreviousBias(double prevBias);
  void setLearningRate(double learningRate);
  void setMomentumRate(double momentumRate);
  void setWeights(vector<double> weights);
  void setSpecificWeight(int number, double value);
  void setPreviousWeights(vector<double> previousWeights);
  void setSpecificPreviousWeight(int number, double value);

  //Functional methods
  void calculateLocalField(vector<double> inputData);
  void calculateOutput();
  void calculateLocalGradient_output(double error);
  void calculateLocalGradient_hidden(vector<double> previousLayerGradients, vector<double> previousLayerWeights);
  void calculateWeight(vector<double> previousLayerOutput);
  void calculateBias();

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
  double sumSquaredError;
  //How many layers are in the network?
  int numberOfLayers;
  //How many neurons are in each layer?
  vector<int> layerInfo;
  //What neurons?
  vector<vector<RosenblattPerceptron>> allNeurons;

  //Private functional methods
  void addNeuron(RosenblattPerceptron neuron);
  void calculateError();
  void calculateSumSquaredError();

public:
  //How do we initialize/construct a network?
  Network(vector<int> layerInfo, vector<vector<double>> initialWeights);
  //How do we destruct a network?
  ~Network();

  //Getters for all the members
  vector<double> getInputs();
  vector<double> getOutputs();
  vector<double> getError();
  double getSumSquaredError();
  int getNumberOfLayers();
  vector<int> getLayerInfo();
  int getNeuronsInLayer(int layer);
  RosenblattPerceptron getNeuron(int layer, int number);
  vector<RosenblattPerceptron> getLayerOfNeurons(int layer);
  vector<vector<RosenblattPerceptron>> getAllNeurons();

  //Setters for all the members (I might need to change the variable names)
  void setInputs(vector<double> inputs);
  void setOutputs(vector<double> outputs);
  void setError(vector<double> errors);     //I don't think this will ever be used
  void setSumSquaredError(double sumSquaredError); //Probably never used
  void setNumberOfLayers(double numLayers);
  void setLayerInfo(vector<int> layerInfo);

  //Functional methods
  void train();
  void run(); //Same idea as train just with no backprop.
};

#endif // NEURONS_H_
