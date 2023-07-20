#ifndef SRC_LENET5_COMMON_H_
#define SRC_LENET5_COMMON_H_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<float.h>

// Environment Option
// ===============================================

//////////////////////// Options ///////////////////////

//#define LOG			// print layer result logs

/////////////////////// Layer config ///////////////////
#define image_Move 10000
#define image_Batch 1

#define label_type int
// 100(1310),
#define MNIST_SIZE 784
#define MNIST_PAD_SIZE 1024
#define MNIST_WH 28
#define MNIST_LABEL_SIZE 10
#define INPUT_SIZE 1024
#define INPUT_WH 32
#define INPUT_DEPTH 1

#define CONV_1_INPUT_SIZE 150528
#define CONV_1_INPUT_WH 224
#define CONV_1_OUTPUT_SIZE 50176
#define CONV_1_OUTPUT_WH 224
#define CONV_1_TYPE 64
#define CONV_1_SIZE 9
#define CONV_1_WH 3 //x2

#define POOL_1_INPUT_WH 224
#define POOL_1_INPUT_SIZE 3211264
#define POOL_1_OUTPUT_WH 112
#define POOL_1_OUTPUT_SIZE 12544
#define POOL_1_TYPE 128
#define POOL_1_SIZE 4 //1st Phase Done

#define CONV_2_INPUT_SIZE 1605632
#define CONV_2_INPUT_WH 112
#define CONV_2_OUTPUT_SIZE 12544
#define CONV_2_OUTPUT_WH 112
#define CONV_2_TYPE 128
#define CONV_2_SIZE 9
#define CONV_2_WH 3 //x2

#define POOL_2_INPUT_WH 112
#define POOL_2_INPUT_SIZE 1605632
#define POOL_2_OUTPUT_WH 56
#define POOL_2_OUTPUT_SIZE 3136
#define POOL_2_TYPE 256
#define POOL_2_SIZE 4

#define CONV_3_INPUT_SIZE 802816
#define CONV_3_INPUT_WH 56
#define CONV_3_OUTPUT_SIZE 3136
#define CONV_3_OUTPUT_WH 56
#define CONV_3_TYPE 256
#define CONV_3_SIZE 9
#define CONV_3_WH 3 //x3

#define POOL_3_INPUT_WH 56
#define POOL_3_INPUT_SIZE 802816
#define POOL_3_OUTPUT_WH 28
#define POOL_3_OUTPUT_SIZE 784
#define POOL_3_TYPE 512
#define POOL_3_SIZE 4

#define CONV_4_INPUT_SIZE 401408
#define CONV_4_INPUT_WH 28
#define CONV_4_OUTPUT_SIZE 784
#define CONV_4_OUTPUT_WH 28
#define CONV_4_TYPE 512
#define CONV_4_SIZE 9
#define CONV_4_WH 3 //x3

#define POOL_4_INPUT_WH 28
#define POOL_4_INPUT_SIZE 401408
#define POOL_4_OUTPUT_WH 14
#define POOL_4_OUTPUT_SIZE 196
#define POOL_4_TYPE 512
#define POOL_4_SIZE 4

#define CONV_5_INPUT_SIZE 100352
#define CONV_5_INPUT_WH 14
#define CONV_5_OUTPUT_SIZE 196
#define CONV_5_OUTPUT_WH 14
#define CONV_5_TYPE 512
#define CONV_5_SIZE 9
#define CONV_5_WH 3 //x3

#define POOL_5_INPUT_WH 14
#define POOL_5_INPUT_SIZE 100352
#define POOL_5_OUTPUT_WH 7
#define POOL_5_OUTPUT_SIZE 49
#define POOL_5_TYPE 512
#define POOL_5_SIZE 4

static const int tbl[] = {
			O, X, X, X, O, O, O, X, X, O, O, O, O, X, O, O,
			O, O, X, X, X, O, O, O, X, X, O, O, O, O, X, O,
			O, O, O, X, X, X, O, O, O, X, X, O, X, O, O, O,
			X, O, O, O, X, X, O, O, O, O, X, X, O, X, O, O,
			X, X, O, O, O, X, X, O, O, O, O, X, O, O, X, O,
			X, X, X, O, O, O, X, X, O, O, O, O, X, O, O, O
		};

#define NN_INPUT_N 25088

#define INPUT_NN_1_SIZE 25088
#define FILTER_NN_1_SIZE 25088 * 4096
#define BIAS_NN_1_SIZE 4096
#define OUTPUT_NN_1_SIZE 4096

#define INPUT_NN_2_SIZE 4096
#define FILTER_NN_2_SIZE 4096 * 4096
#define OUTPUT_NN_2_SIZE 4096
#define BIAS_NN_2_SIZE 4096

#define INPUT_NN_3_SIZE 4096
#define FILTER_NN_3_SIZE 4096 * 1000
#define OUTPUT_NN_3_SIZE 1000
#define BIAS_NN_3_SIZE 1000

#define IMAGE_FILE "./MNIST_DATA/t10k-images.idx3-ubyte"//"./train/image.txt"
#define LABEL_FILE "./MNIST_DATA/t10k-labels.idx1-ubyte"//"./train/label.txt"
#endif
