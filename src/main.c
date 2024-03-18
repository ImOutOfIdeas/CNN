#include <stdio.h>
#include "network.h"

int main (void) {
    int num_layers = 2;
    int neurons_per_layer[] = {2, 1}; // 2 inputs, 1 output

    Network* network = create_network(num_layers, neurons_per_layer);

    double inputs[] = {1.0, 0.0};

    calculate_forward_pass(network, inputs, 1); // Batch size of 1

    printf("Output: %.2f\n", network->layers[network->num_layers - 1].neurons[0].activation);

    // TODO: Free the allocated memory for the network

    return 0;
}
