=============== README ===============

Artificial Neural Network Playground

=============== README ===============

Compiler: MSVC
External files: STBI

======================================

structure setup steps:
 - in NeuralNetworkCLS you can to write a custom scoring function.
 - in every layer class you can change the activationFunc().
 - in every layer class you can change the mutate() function.
 - for some layers you NEED to give more settings, mainly in the form of structs.

 -! don't add an input layer; create the first layer with the input data size as backLayerSize parameter.

======================================
