/**
Author: Nick McCarty
License: MIT

C implementation of a low pass filter
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const float CUTOFF = 100; //hz
const float SAMPLE_RATE = 20000; //hz

const uint32_t filter_length = 32;
float source_buffer[filter_length];
float filtered_buffer[filter_length];
uint32_t idx = 0;

float lpf(float input, float previous, float alpha) {
	return previous + (alpha * input - previous);
}

int main() {
	float RC = 1.0f / (CUTOFF * 2 * 3.14);
	float dt = 1.0f / SAMPLE_RATE;
	float alpha = dt / (RC + dt);
	filtered_buffer[0] = source_buffer[0];


	// Step response test
	filtered_buffer[0] = 1.0f;
	for (int i = 1; i < filter_length; i++) {
		filtered_buffer[i] = lpf(i, filtered_buffer[i-1], alpha);
		printf("filtered_val: %f\r\n", filtered_buffer[i]);
	}
	for (int i = 1; i < filter_length; i++){
		// generate a random number for source
		float val = (float)rand()/(float)RAND_MAX;
		source_buffer[i] = val;
		filtered_buffer[i] = filtered_buffer[i - 1] + (alpha * source_buffer[i] - filtered_buffer[i-1]);
	}
	for (int i = 0; i < filter_length; i++){
		printf("Real %f . Filtered %f\r\n", source_buffer[i], filtered_buffer[i]);
	}	
	return 0;
}