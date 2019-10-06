# SagemakerCpp

Tools and code to integrate C++ into AWS Sagemaker Machine Learning Platform

**INFERENCE SERVER IS CURRENTLY NOT AVAILABLE**

# Examples

## Toy example

A toy example of a fully functional algorithm container. The code does not execute any machine learning algorithm, but demonstrates that the container generated is fully functional within the Sagemaker training infrastructure.

The toy example does the following:

* Prints out the contents of several resource files passed to the algorithm by the platform (as specified in http://docs.aws.amazon.com/sagemaker/latest/dg/your-algorithms-training-algo.html)
* Loads the hyperparameters and prints out their values
* It generates a dummy model file, which in this case is just a text file
* Completes succesfully

## MxNet based Multilayer Perceptron (MLP)

TODO

# Images

This project uses and/or generates 4 types of base images

* amazonlinux : To be used as the base for runtime images that do not require MxNet
* amazonlinux + mxnet dependencies : To be used as the base for runtime images that require MxNet
* amazonlinux + build tools : To be used as the build image for algorithms that do not require MxNet
* amazonlinux + build tools + mxnet code and dependencies : To be used as the build image for algorithms that require MxNet

## Generating build images

This project is able to create 2 different build images. One is a base AmazonLinux with GCC, the other includes:

* openblas
* lapack
* opencv
* MxNet

To generate the AmazonLinux build image execute:

```bash
./generate-build-image.sh al
```

To generate the AmazonLinux + MxNet build image execute:

```bash
./generate-build-image.sh al-mxnet
```

## Generating base runtime images

For amazonlinux nothing needs to be done. To build the amazonlinux + mxnet dependencies image, execute the following commands:

```bash
./generate-build-image.sh al-mxnet
./generate-runtime-mxnet-image.sh
```

# Building the example containers

## Toy example

First build the amazonlinux build image

```bash
./generate-build-image.sh al
```

and then simply execute **build_rt_images.sh** passing as arguments the build image, the directory containing the algoritm code, and the name of the algorithm image that will be generated:

```bash
./build_rt_images.sh ak_build ./example_algo 1234123456.dkr.ecr.us-west-2.amazonaws.com/development
```

This generated runtime image is the one you should push to ECR. To push to ECR using the aws cli execute the following:

```bash
$(aws ecr get-login --no-include-email --region us-west-2)
docker push 1234123456.dkr.ecr.us-west-2.amazonaws.com/development
```

Now you can go to the Sagemaker console and create a training job. Upon completion you'll find the following:

* Cloudwatch logs with printouts of resource files and a list of files in the S3 bucket passed as train
* An S3 model file containing a text file

## MLP

TODO

## Creating a new algorithm

The easiest way is to clone this repository and develop your c++ code inside the example_algo folder. Your algorithm must provide"

* build.sh: script that drives the compilation of your algoritm and invokes docker build
* Dockerfile: that specify where to copies the artifacts of you algorithm, and the entrypoint
