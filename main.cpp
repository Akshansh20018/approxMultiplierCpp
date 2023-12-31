/*
 * main.cpp
 *
 *  Created on: 2017. 4. 11.
 *      Author: woobes
 */



// The file image_convolution.h has hardware implementation, not something needed as of now.
//#include "image_convolution.h"
#include <vector>
#include <numeric>
#include "lenet5/lenet5.h"
#include <sys/types.h>
#include <unistd.h>
#include "./MNIST_DATA/MNIST_DATA.h"
#include "LOG.h"

// load weights & biases
void load_model(string filename, float* weight, int size) {

	ifstream file(filename.c_str(), ios::in);
	if (file.is_open()) {
		for (int i = 0; i < size; i++) {
			float temp = 0.0;
			file >> temp;
			weight[i] = temp;
		}
	}else{
		cout<<"Loading model is failed : "<<filename<<endl;
	}
}

using namespace std;
int main(int argc, char *argv[]){
	int server_socket;
	// Calc execution time
	clock_t start_point, end_point, c1_start,c1_stop, c2_start,c2_stop,c3_start,c3_stop;
	vector<clock_t> v_c1,v_c2,v_c3;
	start_point = clock();

	cout<<"------------------------------------------------------------------\n"
		<<"                   LeNet-5 HW accelerator test\n"
		<<"                         version 0.2.1\n"
		<<"Original source : Acclerationg Lenet-5 (Base Version) for Default,\n"
		<<"implemented by Constant Park, HYU, ESoCLab[Version 1.0]\n"
		<<"HW implementated by CW Lee & JH Woo\n"
		<<"batch : "<<image_Batch<<" test img num : "<<image_Move<<"\n"
		<<"------------------------------------------------------------------"<<endl;

	float* MNIST_IMG;
	int* MNIST_LABEL;

		MNIST_IMG = (float*) malloc(image_Move*MNIST_PAD_SIZE*sizeof(float)); // MNIST TEST IMG
		MNIST_LABEL = (int*) malloc(image_Move*sizeof(int)); // MNIST TEST LABEL
		if(!MNIST_IMG || !MNIST_LABEL){
			cout<< "Memory allocation error(0)"<<endl;
			exit(1);
		}

		// read MNIST data & label
		READ_MNIST_DATA("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/MNIST_DATA/t10k-images.idx3-ubyte",MNIST_IMG,-1.0f, 1.0f, image_Move);
		READ_MNIST_LABEL("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/MNIST_DATA/t10k-labels.idx1-ubyte",MNIST_LABEL,image_Move,false);


	float* Wconv1= (float*) malloc(CONV_1_TYPE*CONV_1_SIZE*sizeof(float));
	float* bconv1=(float*)malloc(CONV_1_TYPE*sizeof(float));
	float* Wconv2=(float*)malloc(CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE*sizeof(float));
	float* bconv2=(float*)malloc(CONV_2_TYPE*sizeof(float));
	float* Wconv3=(float*)malloc(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE*sizeof(float));
	float* bconv3=(float*)malloc(CONV_3_TYPE*sizeof(float));
	
	float* Wpool1= (float*) malloc(POOL_1_TYPE*4*sizeof(float));
	float* Wpool2= (float*) malloc(POOL_2_TYPE*4*sizeof(float));
	float* bpool1= (float*) malloc(POOL_1_TYPE*sizeof(float));
	float* bpool2= (float*) malloc(POOL_2_TYPE*sizeof(float));

	float* Wfc1 = (float*) malloc(FILTER_NN_1_SIZE*sizeof(float));
	float* bfc1 = (float*) malloc(BIAS_NN_1_SIZE*sizeof(float));
	float* Wfc2 = (float*) malloc(FILTER_NN_2_SIZE*sizeof(float));
	float* bfc2 = (float*) malloc(BIAS_NN_2_SIZE*sizeof(float));
	
	if(!Wconv1||!Wconv2||!Wconv3||!bconv1||!bconv2||!bconv3||!Wpool1||!Wpool2||!bpool1||!bpool2||!Wfc1||!Wfc2||!bfc1||!bfc2){
		cout<<"mem alloc error(1)"<<endl;
		exit(1);
	}
	
	cout<<"Load models"<<endl;
	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/Wconv1.mdl",Wconv1,CONV_1_TYPE*CONV_1_SIZE);

	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/Wconv3.mdl",Wconv2,CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE);
	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/Wconv5.mdl",Wconv3,CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE);

	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/bconv1.mdl",bconv1,CONV_1_TYPE);
	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/bconv3.mdl",bconv2,CONV_2_TYPE);
	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/bconv5.mdl",bconv3,CONV_3_TYPE);

	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/Wpool1.mdl",Wpool1,POOL_1_TYPE*4);
	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/Wpool2.mdl",Wpool2,POOL_2_TYPE*4);

	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/bpool1.mdl",bpool1,POOL_1_TYPE);
	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/bpool2.mdl",bpool2,POOL_2_TYPE);

	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/Wfc1.mdl",Wfc1,FILTER_NN_1_SIZE);
	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/Wfc2.mdl",Wfc2,FILTER_NN_2_SIZE);

	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/bfc1.mdl",bfc1,BIAS_NN_1_SIZE);
	load_model("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/filter/bfc2.mdl",bfc2,BIAS_NN_2_SIZE);
	cout<<"model loaded"<<endl;
	// Memory allocation
	float* input_layer	= (float*) malloc(image_Batch *INPUT_WH * INPUT_WH*sizeof(float));
	float* hconv1 		= (float*) malloc(image_Batch * CONV_1_TYPE * CONV_1_OUTPUT_SIZE*sizeof(float));
	float* pool1 		= (float*) malloc(image_Batch * CONV_1_TYPE * POOL_1_OUTPUT_SIZE*sizeof(float));
	float* hconv2 		= (float*) malloc(image_Batch * CONV_2_TYPE * CONV_2_OUTPUT_SIZE*sizeof(float));
	float* pool2 		= (float*) malloc(image_Batch * CONV_2_TYPE * POOL_2_OUTPUT_SIZE*sizeof(float));
	float* hconv3 		= (float*) malloc(image_Batch * CONV_3_TYPE*sizeof(float));
	float* hfc1 		= (float*) malloc(image_Batch * OUTPUT_NN_1_SIZE*sizeof(float));
	float* output 		= (float*) malloc(image_Batch * OUTPUT_NN_2_SIZE*sizeof(float));
	if(!input_layer || !hconv1 || !pool1 || !hconv2 || !pool2 || !hconv3 || !hfc1 || !output){
		cout<<"Memory allocation error(2)"<<endl;
		exit(1);
	}

	// test number
	int test_num = image_Move/image_Batch;
	vector<double> result_sw;
	double accuracy_sw;
	// SW test
	cout<< "SW test start"<<endl;
	for(int i=0;i<test_num;i++){
		for(int batch=0;batch<image_Batch*INPUT_WH*INPUT_WH;batch++){
			input_layer[batch] = MNIST_IMG[i*MNIST_PAD_SIZE + batch];
		}
		c1_start=clock();
		CONVOLUTION_LAYER_1_SW(input_layer,Wconv1,bconv1,hconv1);
		c1_stop=clock();
		POOLING_LAYER_1_SW(hconv1,Wpool1,bpool1,pool1);
		//MAXPOOL_1_SW(hconv1,pool1);
		c2_start=clock();
		CONVOLUTION_LAYER_2_SW(pool1,Wconv2,bconv2,hconv2);
		c2_stop=clock();
		POOLING_LAYER_2_SW(hconv2,Wpool2,bpool2,pool2);
		//MAXPOOL_1_SW(hconv2, pool2);
		c3_start=clock();
		CONVOLUTION_LAYER_3_SW(pool2,Wconv3,bconv3,hconv3);
		c3_stop=clock();
		v_c1.push_back(c1_stop-c1_start);
		v_c2.push_back(c2_stop-c2_start);
		v_c3.push_back(c3_stop-c3_start);
		FULLY_CONNECTED_LAYER_1_SW(hconv3,Wfc1,bfc1,hfc1);
		FULLY_CONNECTED_LAYER_2_SW(hfc1,Wfc2,bfc2,output);
		result_sw.push_back(equal(MNIST_LABEL[i],argmax(output)));

#ifdef LOG
		stringstream ss;
		get_log(&ss,input_layer,hconv1,pool1,hconv2,pool2,hconv3,hfc1,output);
		//print_log("/home/iiitd/Desktop/Research/aspdac_2024/lenet5_hls copy/model_log/conv_steps_sw.log",&ss);
		print_log("conv_steps_sw.log",&ss);
#endif

	}
	accuracy_sw = accumulate(result_sw.begin(),result_sw.end(),0.0);
	cout<<"SW test completed"<<endl;
	cout<<"accuracy : "<<accuracy_sw<<"/"<<result_sw.size()<<endl;
//#endif
	free(input_layer);
	free(hconv1);
	free(hconv2);
	free(hconv3);
	free(pool1);
	free(pool2);
	free(hfc1);
	free(output);

	free(Wconv1);
	free(Wconv2);
	free(Wconv3);
	free(bconv1);
	free(bconv2);
	free(bconv3);
	free(Wpool1);
	free(bpool1);
	free(Wpool2);
	free(bpool2);
	free(Wfc1);
	free(bfc1);
	free(Wfc2);
	free(bfc2);

	free(MNIST_IMG);
	free(MNIST_LABEL);
	return 0;
}
