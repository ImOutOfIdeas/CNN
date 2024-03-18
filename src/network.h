#ifndef NETWORK_H
#define NETWORK_H

#include <stdlib.h>
#include <time.h>

double relu(double x);
double relu_derivative(double x);

typedef double (*activation_func_t)(double);
#define RELU_ACTIVATION relu

// Define struct for a Node in the network
typedef struct Node {
  double activation;
  double* weights;  // Array to store weights for connections to next layer neurons
  double bias;
  double delta;     // Used for backpropagation
  int num_weights;
} Node;

// Define struct for a Layer in the network
typedef struct Layer {
  Node* neurons;
  int num_neurons;
  activation_func_t activation_func;
} Layer;

// Define struct for the Network itself
typedef struct Network {
  Layer* layers;
  int num_layers;
  double learning_rate;
} Network;

Network* create_network(int num_layers, int* neurons_per_layer);
void calculate_forward_pass(Network* network, double* inputs, int batch_size);
void free_network(Network* network); // Function to free allocated memory

#endif
