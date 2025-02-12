#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdlib>
#include <stdexcept>

using namespace std;

template <typename T>
class nuVector
{
public:
    nuVector(T value)
    {
        vector_size = 1;
        memory_base_pntr = (uint32_t *)malloc(vector_size * sizeof(T));
        *memory_base_pntr = value;
    };
    ~nuVector()
    {
        free(memory_base_pntr);
    }
    void add(T value)
    {
        // Allocate new chunk of memory
        uint32_t new_vector_size = vector_size + 1;
        uint32_t *new_base = (uint32_t *)malloc(new_vector_size * sizeof(T));
        // Copy old to new
        for (int i = 0; i < vector_size; i++)
        {
            *(new_base + i) = *(memory_base_pntr + i);
        }
        // Free old memory
        free(memory_base_pntr);
        // Update pointers
        memory_base_pntr = new_base;
        vector_size = new_vector_size;
        // Add new value
        *(memory_base_pntr + (vector_size - 1)) = value;
    }
    T operator[](int index){
        if (index >= 0 && index < vector_size) {
            return *(memory_base_pntr + index);
        } else {
            // Handle out-of-bounds access (e.g., throw an exception)
            throw std::out_of_range("Index out of bounds");
        }
    }
    uint32_t getSize(void)
    {
        return vector_size;
    }
    void print()
    {
        for (int i = 0; i < vector_size; i++)
        {
            printf("%x\r\n", *(memory_base_pntr + i));
        }
    }

private:
    uint32_t vector_size;
    uint32_t *memory_base_pntr;
};

#endif // VECTOR_H