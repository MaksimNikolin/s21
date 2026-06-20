# Convolutional Neural Networks

Summary: this project is an introduction to convolutional neural networks and image classification problems.

💡 [Tap here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) **to leave your feedback on the project**. It's anonymous and will help our team make your educational experience better. We recommend completing the survey immediately after the project.

## Contents

1. [Chapter I. Preamble](#chapter-i-preamble)
2. [Chapter II. Introduction](#chapter-ii-introduction) \
    2.1. [Convolution operation](#convolution-operation) \
    2.2. [Pooling operation](#pooling-operation) \
    2.3. [First CNN architecture: LeNet](#first-cnn-architecture-lenet) \
    2.4. [CNN usage examples](#cnn-usage-examples) \
    2.5. [Modern CNN architectures](#modern-cnn-architectures) \
    2.6. [Augmentations](#augmentations) \
    2.7. [MixUp & CutMix](#mixup--cutmix) \
    2.8. [Test-Time-Augmentations](#test-time-augmentations)
3. [Chapter III. Goal](#chapter-iii-goal)
4. [Chapter IV. Instructions](#chapter-iv-instructions)
5. [Chapter V. Task](#chapter-v-task)
6. [Chapter VI. Bonus part](#chapter-vi-bonus-part)

## Chapter I. Preamble

We have already discussed various algorithms for solving regression or classification problems with tabular data as input. But for several AI problems (such as image or text classification), using such algorithms is suboptimal or even impossible. Now we will learn the first type of algorithms dedicated to working with spatial data: Convolutional Neural Networks (CNN).

## Chapter II. Introduction

The models we have discussed so far remain appropriate options when we are solving tabular problems. A tabular data instance is represented by a vector **x** and a corresponding label **y** (scalar or vector), where the components of **x** don't have any structure: we can permute the components of **x** and it would not break any interactions between features and target. Training on a dataset with permuted features will produce the same model (the same up to the random seed of the algorithm) as learning with features in the original order.

Sometimes we need more flexible tools to handle data with internal structure. One such example of data is images: a pixel contains a small amount of information, but pixel values are correlated and form composite objects. In cat/dog image classification tasks, cat or dog can be in any part of the input.

![Cat](misc/images/cat.png)

[Source](https://aiplanet.com/learn/getting-started-with-deep-learning/convolutional-neural-networks/267/cnn-transfer-learning-data-augmentation)

WIn this case, you can't use a traditional "tabular" approach, because shuffling the (input) features will break the model. Another way — to introduce complex hand-crafted features and use any tabular classifier. For different input data (cats/dogs, medical data, space images, etc.) you need to design a different set of hand-crafted features. This is an option, but we remember from previous lessons that neural networks excel at guided feature creation: inputs are transformed via learnable functions into representations suitable for classification/regression problems. So it makes sense to design special neural networks dedicated to working effectively with such types of data: invariant to translations of inputs.

We call such networks Convolutional Neural Networks or CNNs. This [source](http://d2l.ai/chapter_convolutional-neural-networks/why-conv.html) contains more motivations for using CNN.

### Convolution operation

Imagine we use image pixels as input for MLP. The usual dense layer of the neural network will treat each pixel with its own weight.

![Convolution operation](misc/images/convolution_operation.png)

Objects of interest (e.g. cats) can appear anywhere in the image. It makes sense to design modules that respond similarly to the same patch, regardless of where it appears in the image. We want the neurons to "fire" at any location that contains a cat.

![Convolution operation](misc/images/convolution_operation_2.png)

On the image below, we apply a 3x3 convolution layer: multiply the image patches by the corresponding weights in a 3x3 window, add a bias term, then move the window by 1 pixel (the number of pixels to move the window is called **stride**). This convolution has 10 trainable parameters.

Using a linear layer for the whole image will result in using 82 parameters: 8 times more learnable parameters. This [resource](http://d2l.ai/chapter_convolutional-neural-networks/why-conv.html#constraining-the-mlp) shows that convolutions are basically constrained MLP layers: we use fewer parameters and have a better resulting model quality. This is called **parameter sharing**. Convolutional layers are good examples of parameter sharing: different parts of the input interact with the same set of parameters. It can also be shown that convolutions are equivalent to linear layers with matrices of a special form ([Toeplitz matrices](https://en.wikipedia.org/wiki/Toeplitz_matrix)). Parameter sharing is used in several NN architectures, we will see more examples later.

We can use different weights for different channels of the input image: separate parameters for red, green, blue channels.

![Multiple Maps](misc/images/multiple_maps.png)

The output of the convolution layer is something that resembles an image: 3D object with height, width and number of channels as dimensions. Stacking multiple layers of convolutions allows to capture longer range features of the image (similar to higher level vision in nature).

![io tensor](misc/images/io_tensor.png)

### Pooling operation

The first (or earliest) slices of the NN are focused on local regions (slices don't pay attention to image content in distant regions). This is called **the locality principle**. Learned local representations are aggregated to make predictions for the whole image. For aggregation, we use different kinds of layers, called **pooling layers**. Pooling layers consist of a window of fixed shape (e.g., 3x3) that slides over the image (according to its step) and computes a single output for each location. Most of the time we use **max** (take the max of the elements in the window) or **average** (take the average of the elements in the window) pooling.

![pooling](misc/images/pooling.png)

Pooling layer has no learnable parameters.

### First CNN architecture: LeNet

At the end of our neural network, we flatten the resulting tensor and apply one or more dense layers. The first convolutional network in history, LeNet (1998), follows this approach:

![LeNet](misc/images/lenet.png)

The history of LeNet is described in this [source](https://en.wikipedia.org/wiki/LeNet).

We learn the optimal weights of the convolutional and dense layers using the standard backpropagation algorithm. We end up with an NN model with learnable (convolutional) feature extractors from the image and an MLP classifier.

Convolutional and pooling layers can also be adapted to 1D (time series, text) and 3D objects (brain scans, videos). The next figure shows a typical 1D CNN model.

![2D and 1D](misc/images/2d_and_1d.png)

In summary, **Convolutional Neural Networks (CNNs)** can be defined as any neural network that contains convolutional-pooling layers.

### Transfer Learning

Like any neural network, CNNs are prone to overfitting and require a large amount of training data. For many applications, the large amount of training data is expensive and unavailable. **Transfer learning** is a technique to train the network on a larger data set from a related (or sometimes even unrelated) domain. Once the network parameters have converged, an additional training step is performed using the in-domain training data to fine-tune the network weights. This approach allows CNN models to be applied to almost any problem with a small training set.

The most commonly used dataset for pre-training CNNs is [ImageNet](https://en.wikipedia.org/wiki/ImageNet).

### CNN usage examples

CNNs are so flexible that we can use them to solve a wide variety of problems. Convolutional networks excel at problems based on grid-like structures: image/video classification, time series prediction, audio classification, etc.

For example, audio classification is "solved" by transforming audio into an image-like structure.

![Audio classification](misc/images/audio_classification.png)

Convolutions were used to win an NFL contest on Kaggle: contestants were asked to predict the yardage gained on a play in an American football game.

![football](misc/images/football.png)

CNNs are considered to be most effective for problems with strong local patterns.

### Modern CNN architectures

This [guide](http://d2l.ai/chapter_convolutional-modern/index.html) gives a comprehensive overview of modern CNN design approaches.

Many ideas for improving the performance of CNN consist of ways to make the learning process easier.

One of the breakthrough ideas is skip connection (or residual connection). Residual connection helps CNN to better propagate gradients when using backprop.

![Residual connection](misc/images/residual_connection.png)

This trick allows us to build networks with tens and hundreds of layers: and more layers generally mean better accuracy. Residual connections are used not only in CNNs, but also in other architectures.

Another way to propagate information from previous layers is to use dense blocks: instead of adding, we concatenate the output of the current layer and the outputs of all previous layers, and use this as the input for the next convolutional layer. Thus, convolutional layer 5 takes as input concatenated results from layer 3, layer 2, and so on.

![Dense blocks](misc/images/dense_blocks.png)

### Augmentations

To increase the generalization ability of the CNN, we sometimes transform training examples in a way that doesn't corrupt the original target signal. This transformation is called **augmentation**.

Common options for augmentation are:

- Flipping (horizontal or vertical);
- Cropping (random, centered, etc.);
- Blur;
- Cut-out (zero out a rectangular area of the image);
- Changing the contrast of the image.

For example, in the bird classification task, we can use the following augmentations

![Bird classification](misc/images/bird_classification.png)

Training with augmentations reduces overfitting of the CNN model.

This [source](http://d2l.ai/chapter_computer-vision/image-augmentation.html#image-augmentation) gives a good overview of augmentations for image problems.

### MixUp & CutMix

There are augmentation approaches that involve mixing different samples. The most popular are MixUp and CutMix.

MixUp is basically a way to force neural networks to learn how to interpolate "between" training instances. To perform MixUp, we need to compute a convex combination on 2 different samples and corresponding targets:

```math
\begin {align*}
    \tilde{x} &= \lambda x_i + (1 - \lambda) x_j, \quad \text {where } x_i, x_j \text { are raw input vectors} \\
    \tilde{y} &= \lambda y_i + (1 - \lambda) y_j, \quad \text {where } y_i, y_j \text { are one-hot label encodings}
\end {align*}
```

We can use MixUp with any type of data that allows straightforward computation of convex combinations with instances. The following image illustrates the effect of MixUp on a toy problem.

![Toy problem](misc/images/toy_problem.png)

Blue shading indicates $`p(y=1|x)`$, green means class 0 and orange means class 1.

CutMix essentially proposes the following augmentation strategy: cut and paste patches between training images, where the ground truth labels are also mixed proportionally to the area of the patches.

![CutMix](misc/images/CutMix.png)

### Test-Time-Augmentations

It is possible to apply augmentations (that make sense in real-world problems) to inference samples and average predictions. For example, in cat/dog classification, we can crop, flip, or slightly rotate our image, predict, and average to compute the final prediction for a given sample.

![Augmentations](misc/images/augmentations.png)

## Chapter III. Goal

The goal of this task is to get a deep understanding of the basic image classification models (CNN modules, LeNet, ResNet, DenseNet, etc.).

## Chapter IV. Instructions

This project will be evaluated by humans only. You are free to organize and name your files as you wish.

- We use Python 3 as the only correct version of Python.
- For training deep learning algorithms you can try Google Colab. It offers free kernels (Runtime) with GPU, which is faster than CPU for such tasks.
- The standard is not applied to this project. However, you are asked to be clear and structured in your source code design.
- Store the datasets in the data subfolder.

## Chapter V. Task

1. Download the [Zindi gesture data](https://zindi.africa/competitions/kenyan-sign-language-classification-challenge/data). Examine the data for some time. Make sure you get rid of duplicate examples. Are there any mislabeled examples? Think about which extensions would be optimal for the current task. Design a training and validation split. Use a random 33% of the total data as the validation set.

2. Write a custom pytorch dataset class for image and goal retrieval: read images using OpenCV2, extract targets using pandas. Make sure the dataset class has the correct API for sample retrieval. Create a pytorch DataLoader for your datasets.

3. Rebuild the LeNet architecture. Use predefined layers from the pytorch library: Conv2d, Pooling, Linear. You can use the Dropout layer to improve the quality of your model.

4. Design a basic train-validation loop: iterate over the training dataset, batch by batch, update the parameters of the network, and check the quality of the model using the validation set. [Here](https://github.com/pytorch/examples/blob/main/mnist/main.py) you can find a comprehensive example of a basic training-validation pipeline (you can copy-paste it first, then modify it). As loss for your model use Binary Cross Entropy, as metric use ROC AUC score. Get ROC AUC higher than 0.75.

5. Pick any vision model or backbone (resnet18 is recommended as a baseline) from this [library](https://github.com/rwightman/pytorch-image-models). Change the head of your model to a linear layer with one output. Train the model for 2-4 epochs (iterations, traversals over the entire training dataset). You must be able to obtain a ROC AUC greater than 0.9. You are also advised to play with other backbones to get better results.

6. Apply different augmentations from the [albumentations](https://albumentations.ai/) library and check if they improve the validation score.

7. Implement MixUp and CutMix augmentations and test them in your pipeline; check if they improve the validation score.

## Chapter VI. Bonus part

1. Add Test-Time-Augmentation (TTA) option to your code. For example, try averaging the predictions of horizontally flipped and original images. What is your gain in terms of ROC AUC score?

>Please leave feedback on the project in the [feedback form.](https://forms.yandex.ru/cloud/646b47abc09c022a752404b0/) 
