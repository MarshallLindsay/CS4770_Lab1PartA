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
  int8_t location[2];       //layer , number.
  double localGradient;     //delta from notes
  double localField;        //v_j(k) from notes
  double output;            //y_j(k) from notes
  double bias;              //Bias attached to the neuron
  double learningRate;      //The learning rate
  double momentumRate;      //The momentumRate
  vector<double> weights;   //Vector of all of the weights

  void randomizeWeights(); //Initialize the weight vector with random values

public:
  RosenblattPerceptron();   //Initialize the neuron
  ~RosenblattPerceptron();
  int8_t getLayer();        //Return the layer that the neuron is in
  int8_t getNumber();       //Return the neuron's number in the layer
  double getLocalGradient();//Return the local gradient
  double getLocalField();   //Return the local field
  double getOutput();       //Return the output of the neuron
  vector<double> getWeights();//Return the weight vector
  double getWeight(int number);//Return a single specified weight
  double getBias();         //Return the bias for the neuron
  double getLearningRate(); //Return the learningRate
  double getMomentumRate();  //Return the momentumRate

};


class Network {
private:
  vector<int> inputs;       //Input vector
  vector<int> outputs;      //Output vector
  int numberOfLayers;       //Number of layers in the network
  vector<int> layerInfo;//Vector that contains the number of neurons in a layer
  vector<RosenblattPerceptron> neurons;   //Vector of al the neurons in the network

public:
  Network(vector<int> layerInfo);
  ~Network();
  vector<int> getInputs();
  vector<int> getOutputs();
  int getNumberOfLayers();
  vector<int> getLayerInfo();
  int getNeuronsInLayer(int number);
  vector<RosenblattPerceptron> getNeurons();

};

#endif // NEURONS_H_
