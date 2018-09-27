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
  int location[2];       //layer , number.
  double localGradient;     //delta from notes
  double localField;        //v_j(k) from notes
  double output;            //y_j(k) from notes
  double bias;              //Bias attached to the neuron
  double learningRate;      //The learning rate
  double momentumRate;      //The momentumRate
  vector<double> weights;   //Vector of all of the weights

  void randomizeWeights(); //Initialize the weight vector with random values

public:
  RosenblattPerceptron(int layer, int number);   //Initialize the neuron
  ~RosenblattPerceptron();
  int getLayer();        //Return the layer that the neuron is in
  int getNumber();       //Return the neuron's number in the layer
  double getLocalGradient();//Return the local gradient
  double getLocalField();   //Return the local field
  double getOutput();       //Return the output of the neuron
  vector<double> getWeights();//Return the weight vector
  double getWeight(int number);//Return a single specified weight
  double getBias();         //Return the bias for the neuron
  double getLearningRate(); //Return the learningRate
  double getMomentumRate();  //Return the momentumRate

  void setWeight(vector<double> inputWeights);
  void setBias(double inputBias);
  void setLearningRate(double lr);
  void setMomentumRate(double mr);

  void calculateLocalField(vector<double> inputData);
  void calculateOutput();
  void calculateLocalGradient_output(double error);
  void calculateLocalGradient_hidden(vector<double> previousLayerGradients);

};


class Network {
private:
  vector<int> inputs;       //Input vector
  vector<vector<double>> outputs;      //Output vector
  vector<double> error;
  int numberOfLayers;       //Number of layers in the network
  vector<int> layerInfo;//Vector that contains the number of neurons in a layer
  vector<vector<RosenblattPerceptron>> neurons;   //Vector of al the neurons in the network
  vector<vector<double>> neuronGradients;

  void addNeuron(RosenblattPerceptron neuron);
public:
  Network(vector<int> layerInfo);
  ~Network();
  vector<int> getInputs();
  vector<vector<double>> getOutputs();
  int getNumberOfLayers();
  vector<int> getLayerInfo();
  int getNeuronsInLayer(int number);
  vector<vector<RosenblattPerceptron>> getNeurons();

  void printWeights();
  void printBias();

  void setWeights(vector<vector<double>> inputWeights, int layer);
  void setBias(vector<double> inputBias, int layer);
  void setLearningRate(double learningRate);
  void setMomentumRate(double momentumRate);

  void forwardComputation(vector<double> inputTrainingData, vector<double> outputTrainingData);
  void backwardComputation();
  void calculateError(vector<double> outputTrainingData);

};

#endif // NEURONS_H_
