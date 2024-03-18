#include "network.h"

double relu(double x) {
    return (x > 0.0) ? x : 0.0;
}

double relu_derivative(double x) {
    return (x > 0.0) ? 1.0 : 0.0;
}

double random_weight_initializer(void) {
    srand(time(NULL));

    return ((double)rand()) / (RAND_MAX) * 2.0 - 1.0;
}

Layer* create_layer(int num_neurons, int num_weights) {
    Layer* layer = (Layer*)malloc(sizeof(Layer));
    layer->neurons = (Node*)malloc(sizeof(Node) * num_neurons);
    layer->num_neurons = num_neurons;

    for (int i = 0; i < num_neurons; ++i) {
        layer->neurons[i].weights = (double*)malloc(sizeof(double) * num_weights);
        layer->neurons[i].activation = 0.0;
        layer->neurons[i].bias = 0.0;
        layer->neurons[i].delta = 0.0;
        layer->neurons[i].num_weights = num_weights;

        for (int j = 0; j < num_weights; ++j) {
            layer->neurons[i].weights[j] = random_weight_initializer();
        }
    }

    layer->activation_func = RELU_ACTIVATION;

    return layer;
}

Network* create_network(int num_layers, int* neurons_per_layer) {
    Network* network = (Network*)malloc(sizeof(Network));
    network->layers = (Layer*)malloc(sizeof(Layer) * num_layers);
    network->num_layers = num_layers;

    for (int i = 0; i < num_layers; ++i) {
        int num_weights = (i == 0) ? 0 : neurons_per_layer[i-1]; // No weights for input layer
        network->layers[i] = *create_layer(neurons_per_layer[i], num_weights);
    }

    network->learning_rate = 0.1;

    return network;
}

void calculate_forward_pass(Network* network, double* inputs, int batch_size) {
    int num_layers = network->num_layers;

    // Set input layer activations
    for (int i = 0; i < batch_size; ++i) {
        for (int j = 0; j < network->layers[0].num_neurons; ++j) {
            network->layers[0].neurons[j].activation = inputs[i * network->layers[0].num_neurons + j];
        }
    }

    // Forward pass through hidden layers
    for (int layer_index = 1; layer_index < num_layers; ++layer_index) {
        Layer* current_layer = &network->layers[layer_index];
        Layer* previous_layer = &network->layers[layer_index - 1];

        for (int i = 0; i < batch_size; ++i) {
            for (int j = 0; j < current_layer->num_neurons; ++j) {
                double weighted_sum = 0.0;
                // Calculate weighted sum of activations from previous layer
                for (int k = 0; k < previous_layer->num_neurons; ++k) {
                    weighted_sum += previous_layer->neurons[k].activation * current_layer->neurons[j].weights[k];
                }
                weighted_sum += current_layer->neurons[j].bias; // Add bias term

                // Apply activation function (replace with your chosen function)
                current_layer->neurons[j].activation = relu(weighted_sum);
            }
        }
    }
}

