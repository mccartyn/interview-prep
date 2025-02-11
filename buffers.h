#ifndef BUFFERS_H
#define BUFFERS_H
/** 
Author: Nick McCarty
License: MIT

C Implementation of a circular buffer. Buffer fills in a first in, first out 
fashion. When buffer is full the sample will be added to the front of the 
buffer, overwritting the oldest sample. The buffer read pointer always points
to the most recent data.

**/

typedef struct {
	uint32_t *base_address_ptr;
	uint32_t max_samples;
        uint32_t *write_ptr;
	uint32_t *read_ptr;
} buffer_;

// Methods

// Initialize buffer

void buffer_init(buffer_ *buffer, uint32_t* buffer_memory, uint32_t buffer_size) {
	buffer->base_address_ptr = buffer_memory;
	buffer->max_samples = buffer_size;
	buffer->write_ptr = buffer->base_address_ptr;
	buffer->read_ptr = buffer->base_address_ptr;
}

// Add sample
void buffer_add_sample(buffer_ *buffer, uint32_t sample){	
	if (buffer->write_ptr >= (buffer->base_address_ptr + buffer->max_samples)) {
		buffer->write_ptr = buffer->base_address_ptr;
	}
	*(buffer->write_ptr) = sample;
	buffer->write_ptr++;
} 

// Read sample
uint32_t buffer_read_sample(buffer_ *buffer) {
	uint32_t sample_value = *(buffer->read_ptr);
	buffer->read_ptr++;
	if (buffer->read_ptr > (buffer->base_address_ptr + buffer->max_samples)) {
		 buffer->read_ptr = buffer->base_address_ptr;
	}
	return sample_value;
}

#endif // BUFFERS_H
