/* Metrowerks C++ run-time start-up. */

#include "common.h"

/* The compiler's C++ run-time start-up (runs the static constructors between `start` and `endIn`). */
void __initialize_cpp_rts(void *start, void *endIn) {
    Callback_00286910 *current = start;
    Callback_00286910 *end = endIn;

    if (current < end) {
        do {
            (*current)();
            current++;
        } while (current < end);
    }
}
