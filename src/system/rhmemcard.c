/* Memory-card helper (RhMemCard_*). */

#include "common.h"

/* Starts the memory card system (nothing to do here). */
s32 RhMemCard_Init(void) {
    func_00193808();
    return 1;
}

/* Ends the memory card system. */
s32 RhMemCard_Term(void) {
    return 1;
}

/* The memory card system's per-frame work. */
s32 RhMemCard_Act(void) {
    return 1;
}
