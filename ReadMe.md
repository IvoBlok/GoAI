=============== README ===============

Artificial Neural Network Playground

=============== README ===============

Compiler: MSVC
External dependencies: STBI

=====================================

This is a learning project for the implementation of more complex neural network structures.
All of it, except STBI for image loading and the C++ STD, is made from scratch.
It currently supports:
 - 'normal' layers/nodes
 - convolutional layers
 - 3D convolutional structures
 - full stride and padding support
 - interconnectivity between different types of layers
 - semi-simple interface for defining network structures

=====================================

structure setup steps:
 - in NeuralNetworkCLS you can to write a custom scoring function.
 - in every layer class you can change the activationFunc().
 - in every layer class you can change the mutate() function.
 - for some layers you NEED to give more settings, mainly in the form of structs.

 -! don't add an input layer; create the first layer with the input data size as backLayerSize parameter.

======================================
