#include <stdint.h>
#include <stdio.h>

#include "bitwise.h"
#include "buffers.h"
#include "vector.hpp"

// Buffers test
const uint32_t buffer_size = 16;
uint32_t buffer[buffer_size];

int main()
{
    const uint16_t val = 0xAABB;
    uint16_t tmp = val;
    uint16_t actual = val;

    // Bitwise Tests
    actual = 0xBBAA;
    tmp = UINT16_FLIP_LH_BYTE(tmp);
    if (tmp != actual)
    {
        printf("Failed TC1: Actual = 0x%x, Result = 0x%x\r\n", actual, tmp);
    }

    tmp = val;
    actual = 0xAA00;
    tmp = UINT16_MASK_L_BYTE(tmp);
    if (tmp != actual)
    {
        printf("Failed TC2: Expected = 0x%x, Result = 0x%x\r\n", actual, tmp);
    }
    buffer_ buffer_s;
    buffer_init(&buffer_s, buffer, buffer_size);
    // Run a for-loop overfilling
    for (int i = 0; i < 2 * buffer_size; i++)
    {
        buffer_add_sample(&buffer_s, (uint32_t)i);
    }
    // Circular fill operation test
    for (int i = 0; i < buffer_size; i++)
    {
        if (buffer[i] != (0x10 + i))
        {
            printf("Failed TC3: Expected = 0x%x, Result = 0x%x\r\n", (0x10 + i), buffer[i]);
            break;
        }
    }

    // Write and Read operation test
    for (int i = 0; i < buffer_size; i++)
    {
        uint32_t sample = (uint32_t)i;
        buffer_add_sample(&buffer_s, sample);
        uint32_t read_sample = buffer_read_sample(&buffer_s);
        if (sample != read_sample)
        {
            printf("Failed TC4: Expected = 0x%x, Result = 0x%x\r\n", sample, read_sample);
            break;
        }
    }

    // Vector test
    // Vector
    uint32_t vector_tmp = 0;
    nuVector<uint32_t> v(vector_tmp);
    vector_tmp++;
    v.add(vector_tmp);
    vector_tmp++;
    v.add(vector_tmp);
    for (int i = 0; i < v.getSize(); i++) {
        if (v[i] != i) {
            printf("Failed TC5: Expected %i, Result %u\r\n", i, v[i]);
            break;
        }
    }

    return 0;
}
