#include <stdbool.h>

#define MAX_REG_HOLES 5

// An array of register addresses defined as 'holes'.
// The values in this array should be the registers that are known to be holes.
const int REG_HOLES[MAX_REG_HOLES] = { /* Fill with known holey register values */ };

// Function to check if a register is a hole.
bool aw9523_is_reg_hole(int reg_address) {
    for (int i = 0; i < MAX_REG_HOLES; ++i) {
        if (REG_HOLES[i] == reg_address) {
            return true;
        }
    }
    return false;
}

// Usage example:
// if (aw9523_is_reg_hole(register_address)) {
//     // Handle non-readable register
// }


A key point to optimize might be the search through the `REG_HOLES` array. If the holes are very few and known at compile-time, this linear search is acceptable. However, for larger sets of holes or high-performance demands, a more efficient lookup method may be required, such as a binary search (if sorted), a hash table, or direct checking within ranges if the holes are contiguous or can be expressed in ranges.