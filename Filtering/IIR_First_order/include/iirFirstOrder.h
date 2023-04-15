#ifndef IIR_FIRST_ORDER_H
#define IIR_FIRST_ORDER_H

#ifdef __cplusplus
extern "C" {
#endif

// structure that defines the filter. 
typedef struct{
    float alpha;
    float beta;
    float output;
} IIRFilter;
void init_iir_filter(IIRFilter *filter, float alpha, float beta);
float IIR_Filter_Update(IIRFilter* filter, float sample);

#endif

#ifdef __cplusplus
}
#endif