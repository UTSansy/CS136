// This module provides a customizable alphabet in SOS format

#include "sos.h"

// build_custom_codebook() provides a customizable codebook
// effects: allocates memory (caller must call sos_destroy)
struct sos *build_custom_codebook(void);
