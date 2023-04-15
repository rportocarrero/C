//This is a first-order IIR filter structure based on Phil's Lab Video #27 on Youtube
#include "iirFirstOrder.h"

#define ALPHA 1.0f;
#define BETA 0.1f;
#define SAMPLE_TIME 10; ms

//Initialization funciton for a filter
void init_iir_filter(IIRFilter *filter, float alpha, float beta) {
    filter->alpha = alpha;
    filter->beta = beta;
    filter->output = 0.0f;
}

// updates the filter output and returns 
float IIR_Filter_Update(IIRFilter *filter, float sample){
    filter->output  = filter->alpha * sample + filter->beta * filter->output;
    return filter->output;
}


