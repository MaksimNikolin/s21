# Recurrent Neural Nets

Summary: This project introduces recurrent neural networks (RNN) and their development into LSTM and GRU.

💡 [Нажми сюда](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624), **чтобы поделиться с нами обратной связью на этот проект**. Это анонимно и поможет нашей команде сделать обучение лучше. Рекомендуем заполнить опрос сразу после выполнения проекта.

## Contents

1. [Chapter I. Preamble](#chapter-i-preamble)
2. [Chapter II. Introduction](#chapter-ii-introduction) \
    2.1. [RNN block mechanism](#rnn-block-mechanism) \
    2.2. [Output of RNN](#output-of-rnn) \
    2.3. [Problems of vanilla RNN](#problems-of-vanilla-rnn) \
    2.4. [Embedding layer](#embedding-layer)
3. [Chapter III. Goal](#chapter-iii-goal)
4. [Chapter IV. Instructions](#chapter-iv-instructions)
5. [Chapter V. Task](#chapter-v-task)
6. [Chapter VI. Bonus part](#chapter-vi-bonus-part)

## Chapter I. Preamble

We have already studied some of the most important machine learning models, and in all cases we took as input an x-vector describing the characteristics of the observed data sample. But what if the observed sample is characterized by a sequence of events? For example, we want to predict an engine failure based on several sensors that produce readings every 10 seconds. The standard approach is to build the same vector x based on the different aggregations of the sequences, such as taking an average or looking at how many times a sensor's value was above the norm. But since we have neural networks, which are known for their flexibility, can we use them for this task?

## Chapter II. Introduction

### RNN block mechanism

When the data in the problem under study is represented as sequences, fully connected neural networks are poorly suited for learning because we feed vectors of fixed length to the input and output. The advantage of RNN is its ability to process sequences.

This is achieved by the following mechanisms:

- each element of the sequence $`x_t`$ is processed one by one by the so-called RNN block;
- the RNN block takes 2 vectors as input: the sequence element vector $`x_t`$ and the state vector $`h_(t-1)`$. This block returns 1 vector in total — the state vector $`h_t`$;
- the most important — the RNN output of the block $`h_t`$ is used as one of the inputs for the next element of the sequence (see figure below);
- for the first element input state vector $`h_0`$ initialized with zeros.

![RNN block](misc/images/rnn_block.png)

Thus, when processing an element of the sequence, the RNN stores the information it needs in the $`h_t`$ vector and passes it on. This allows the neural network to learn the connections between the elements of the sequence. For example, to learn the relationship between the gender of a noun and its adjective. And this is what is called the memory of RNN.

### Output of RNN

The output of the whole Recurrent Neural Network can be either a sequence or a single value. It depends on the problem we are solving. If we are translating text, we need to get a sequence of words in another language. And if we are classifying the letter as spam or not spam, we need to translate the input sequence into a probability. The possible variations are shown below:

![Output of RNN](misc/images/output_rnn.jpg)

### Problems of vanilla RNN

However, the classic RNN block has a number of drawbacks. It is difficult for a vanilla RNN to learn relationships between elements of a sequence that are far apart. Imagine that once a month you buy a water filter from a supermarket near your home. And in between those purchases, you go there once a week and fill bags with dozens of goods. If this sequence of goods is fed to the input of the RNN block, then at the time of the next purchase of the filter, the state vector h_t is unlikely to store any trace of the previous one.

The above problem is closely related to the vanishing gradient problem. If the loss function is computed based on the last element of the sequence, then the gradient can decay strongly with backward propagation and be close to zero for the first elements of the sequence. To understand why this happens, see the figure below. The key point for both problems is that we are multiplying on the same matrix many times during the forward and backward paths.

![Problem](misc/images/problem.png)

To avoid these problems, it has been proposed to modify the structure of the RNN block by adding a cell state inside, which is able to forget and update information within itself, using carefully regulated gated layers. From these considerations, several new architectures have been proposed, but the main ones are LSTM and GRU. Understanding how they work in detail and how they differ is part of your task. You can use [these materials](https://colah.github.io/posts/2015-08-Understanding-LSTMs/) to dive deeper if you wish.

### Embedding layer

Let's say we have a sequence of some fixed stock prices. If we want to solve the problem of predicting the price for the next day, it is not difficult to find an answer to the question "how to form a vector x". We can fill it with the previous day's open and close prices, moving averages, financial data, and more. And then, by combining these values into the vector for each day over the past year, we get the sequence we need.

But what if our sequence does not consist of continuous values, but of symbols or discrete values (for example, the identifier of a product purchased in a store)? In this case, an embedding layer is usually used, which simply assigns a vector of fixed size to each character/word/identifier/other. And the most important thing is that all these values inside the vector are trainable, i.e. during the training of the neural network they are updated using gradient descent, as well as the weights of the linear layers. If we manage to train our neural network well enough, the embeddings of the tokens (set of possible characters/words/identifiers, etc.) can inherit properties that are well known to us. A classic example of this principle is the inheritance of a 2-word relationship: the word "king" is related to the word "man" in the same way that the word "queen" is related to the word "woman". Nothing prevents us from writing this expression in vector form:

vector(King) - vector(Man) = vector(Queen) - vector(Woman)

![Vectors](misc/images/vectors.png)

## Chapter III. Goal

The goal of this task is to get a deep understanding of how to build models based on RNN, GRU, and LSTM architectures.

## Chapter IV. Instructions

- This project will be evaluated by humans only. You are free to organize and name your files as you wish.
- We use Python 3 as the only correct version of Python.
- For training deep learning algorithms you can try [Google Colab](https://colab.research.google.com/). It offers free kernels (runtime) with GPU, which is faster than CPU for such tasks.
- The standard does not apply to this project. However, you are asked to be clear and structured in your source code design.
- Store the datasets in the data subdirectory.

## Chapter V. Task

In this project, you will work with a dataset of names. We will represent each name as a sequence of letters and try to train different models for name generation and name classification.

You can use any framework you like: PyTorch, TensorFlow, Keras,
etc.

### Dataset

You will work with the open dataset of baby names — [https://data.world/alexandra/baby-names](https://data.world/alexandra/baby-names). The dataset consists of 6782 records. Each record contains the baby's name and gender.

### Task

1. Introduction \
    a. Describe the types of tasks for which recurrent neural networks are useful. \
    b. Give 2 examples of one-to-many, many-to-many, and many-to-one formulations of the problem. \
    c. Imagine you have an RNN that classifies the language of incoming words. Illustrate (in Paint, Drawio, etc.) with blocks how this model will process the word "Hello". Draw each input and output. Define each block with its parameters. Illustrate what the initial value of the hidden state will be. \
    d. Explain the main difference between vanilla RNN, LSTM, and GRU. Draw LSTM or GRU similar to RNN.

2. Data Analysis \
    a. Download the dataset from the link above or from the course files. \
    b. Plot a histogram of name lengths. \
    c. Check if the dataset is gender balanced or not. \
    d. Count the frequency of each letter.

3. Data preparation \
    a. Encode gender. \
    b. Convert names to lowercase. \
    c. Extend each name with 'start of name' prefix (e.g. `<SOS>`), 'end of name' postfix (e.g. `<EOS>`) and pad the name with 'space' (e.g. ' ') up to the maximum length. \
    d. Create the array of tokens (letters and special symbols) that will be used to encode each name. Create a mapping from token to integer id and vice versa. \
    e. Represent each name as a sequence of integers using the mapping from b. Each sequence should have the same length. \
    f. Split the dataset into training, valid, and test parts (take 80-10-10%). Be sure to use random_state.

4. Recurrent Neural Network \
    a. Implement a network that contains:

    - i. Embedding layer;
    - ii. Vanilla recurrent neural network block (do not use already implemented blocks from libraries, expect to implement this block from scratch); 
    - iii. Linear layer to transform the output of the RNN block into logits of the next token output; 
    - iv. Linear layer to transform the last token output of the RNN block to logit of gender; 
    - v. (You can also add a dropout layer if you want); 
    - vi. Sigmoid to transform the gender class logit to probability; 
    - vii. Don't forget to implement a method to initialize the hidden state.
    
    b. Train the network using only loss for next letter prediction:

    - i. Take the output of the softmax layer for each token in sequence except the last. 
    - ii. Take the next token as label. 
    - iii. Compute the cross-entropy loss and perform a backward step. 

    c. Implement a method to generate names from the trained model:

    - i. Method should be stochastic — i.e. next letter should be sampled using probabilities based on logit level. 
    - ii. Provide the parameter to control the beginning of the name. 
    - iii. Specify the parameter to control the stochasticity of the next letter. Usually this parameter is called temperature (from physics). Higher temperature produces more chaotic outputs, lower temperature converges to the single most likely output. 
    - probs = softmax(logits / temperature, dim=-1)

    d. Evaluation: 

    - i. Plot loss convergence on train and valid data.
    - ii. Sample 10 names. Are they realistic? (Remember to put the model in eval mode.)
    - iii. Predict the gender of the names from the test data and compute the ROC AUC score.

5. Gated Recurrent Unit 

    a. Repeat steps 4.a, 4.b, and 4.d, but with the GRU model as the recurrent neural network block.

6. LSTM

    a. Repeat steps 4.a, 4.b, and 4.d, but with the LSTM model as the recurrent network block.

7. Model comparison 

    a. Propose your own metric that can be used for name generator models. Please try to answer this question before reading the next one. \
    b. Explain what ytixelprep measures (name of metric is reversed to avoid spoilers). \
    c. Derive how this metric is related to cross entropy loss. \
    d. Implement 2 versions of this metric (with and without cross entropy loss). \
    e. Derive the value of this metric for a "random" model that returns the same probability for each letter. Calculate the value of this metric in notebook. \
    f. Compute the value of this metric for a "most popular letters" model that returns the frequency of letters (the frequency of all letters should sum to 1). \
    g. Compare the models.

8. Gender classification \
    a. Let's train RNN, GRU, and LSTM, but with a different loss function: 
    
    - i. Take the probability of the gender class.
    - ii. Take the name gender as label.
    - iii. Compute the loss and do a backward step.
    - iv. Try the Binary Cross Entropy loss and the Negative Log Likelihood loss.
    - v. Explain which loss is better and why.

    b. Evaluation: 

    - i. Plot loss convergence on training and valid data. 
    - ii. Sample 10 names. Are they realistic? (Remember to put the model in eval mode.) 
    - iii. Predict the gender of the names from the test data and compute the ROC AUC score.

9. Vanishing Gradient \
    a. Take a subset of the training data set where the length of the names is equal to their mode. \
    b. Implement the collection of gradients during model fitting for the embedding layer. The collected tensor should have the shape (n_epochs, max_name_length, n_tokens, embedding_size): 

    - i. in pytorch you can use register_backward_hook; 
    - ii. in tensorflow you can use tf.GradientTape() or a custom callback. 

    c. Debug the gradient collection with batch_size=1 and n_epochs=1: 

    - i. Compute the norm of each vector along the last dimension. You will get a tensor with shape (1, max_name_length, n_tokens). 
    - ii. Compare which tokens have non-zero gradient norm with the tokens of the names (note that register_backward_hook will collect the gradient from the last token to the first). 

    d. Compute the Frobenius norm of the gradient matrix for each epoch and token position. The resulting tensor should have the form (n_epochs, max_name_length). \
    e. Take the mean over the epochs. \
    f. Train models for the gender classification task. Plot and compare the distribution of mean gradient norm over token position for RNN, GRU, and LSTM architectures. \
    g. Repeat steps b-f when training the model for the next letter prediction task. What is the difference? \
    h. Explain why we used the subset of the training data with fixed-length names in step a. \

10. Multitask Learning \
    a. Train the GRU or LSTM model with 2 loss functions at the same time: the first is the loss from predicting the next letter, the second is the loss from gender classification. \
    b. Evaluate:

    - i. Plot loss convergence for both loss functions on training and valid data.
    - ii. Sample 10 names. Are they realistic? (Remember to put the model in eval mode.)
    - iii. Predict the gender of the names from the test data and calculate the ROC AUC score.

11. Visualizing embeddings \
    a. Get the embeddings of each letter from the model with multitask loss. \
    b. Use the TSNE model to compress vectors into 2 dimensions. \
    c. Use PCA model to compress vectors into 2 dimensions. \
    d. Split letters into vowels and consonants. \
    e. Use scatterplot to visualize letter position in 2 dimensions for both compressions. \
    f. What can you infer from the plots?

### Submission

Save your multitask learning model in pickle format. Your peer will load it and use it to make predictions again for the test dataset (remember to use the same random state). The predictions should be saved in a file named `test_predictions.csv`.

You must achieve a roc_auc_score of at least 0.85 on the test dataset.

Your repository should contain one or more notebooks with your solutions.

## Chapter VI. Bonus Part

- Try to achieve an even better gender classification performance on the test dataset — ROC AUC 0.92+.
- Propose the method to get the embedding of each name. Collect, compress, and plot them using the split by gender
- Train gradient boosting trees for the gender classification task. Which features will you use? Evaluate and compare performance on a test dataset.
- Train torch/tensorflow/keras/etc built-in RNN, LSTM, GRU models and compare their performance with your models.

>Please leave feedback on the project in the [feedback form.](https://forms.yandex.ru/cloud/646b47bce010db2a89f1f5e6/) 
