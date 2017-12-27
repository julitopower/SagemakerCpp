# SagemakerCpp

Tools and code to integrate C++ into AWS Sagemaker Machine Learning Platform

# Toy example

This project contains a toy example of a fully functional algorithm container. The code does not execute any machine learning algorithm, but demonstrates that the container generated is fully functional within the Sagemaker training infrastructure.

The toy example does the following:

* Prints out the contents of several resource files passed to the algorithm by the platform (as specified in http://docs.aws.amazon.com/sagemaker/latest/dg/your-algorithms-training-algo.html)
* Loads the hyperparameters and prints out their values
* It generates a dummy model file, which in this case is just a text file
* Completes succesfully

## Building the example container

Simply execute **build_rt_images.sh** passing as an argument the name of the algorithm image that will be generated. For example:

```bash
./build_rt_images.sh ./example_algo 1234123456.dkr.ecr.us-west-2.amazonaws.com/development
```

This will generate two images. One is simply called build_image, and it is not meant to be pushed to ECR. The second one is the runtime one, and will be named with the argument passed to the command. The runtime image is the one you should push to ECR. To push to ECR using the aws cli execute the following:

```bash
$(aws ecr get-login --no-include-email --region us-west-2)
docker push 1234123456.dkr.ecr.us-west-2.amazonaws.com/development
```

Now you can go to the Sagemaker console and create a training job. Upon completion you'll find the following:

* Cloudwatch logs with printouts of resource files and a list of files in the S3 bucket passed as train
* An S3 model file containing a text file

## Creating a new algorithm

The easiest way is to clone this repository and develop your c++ code inside the example_algo folder. Your algorithm must provide"

* build.sh: script that drives the compilation of your algoritm and invokes docker build
* Dockerfile: that specify where to copies the artifacts of you algorithm, and the entrypoint