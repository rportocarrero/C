#include <gtest/gtest.h>

// Include the header file for the iirFirstOrder library
#include "iirFirstOrder.h"

// Define the first test
TEST(IirFirstOrderTest, Test1) {
  // Initialize variables for the filter coefficients and input/output values
  IIRFilter* filter = (IIRFilter*) malloc(sizeof(IIRFilter));
  float alpha = 1.0f;
  float beta = 0.1f;
  float result;
  float expected = 1.0f;
  int rounds = 1;

  // Create an instance of the iirFirstOrder filter
  init_iir_filter(filter, alpha, beta);

  // Apply the filter to the input value
  for(int i=0; i<rounds; i++){
    result = IIR_Filter_Update(filter, 1);
  }
  // Check that the output value matches the expected value
  EXPECT_NEAR(result, expected, 1e-3);

  free(filter);
}

// This test takes an input signal and compares it to an expected output signal for an inpulse response.
TEST(IirFirstOrderTest, testImpulseResponse){
  //Initialize test parameters
  IIRFilter* filter = (IIRFilter*) malloc(sizeof(IIRFilter));
  float alpha = 1.0f;
  float beta = 0.1f;
  float result1, result2;

  //Create filter instance
  init_iir_filter(filter, alpha, beta);

  // Apply the filter to the input value
  result1 = IIR_Filter_Update(filter, 1);
  result1 = IIR_Filter_Update(filter, 0);

  //Check Results
  EXPECT_NEAR(result1, 0.1, 1e-3);
  EXPECT_NEAR(result2, 0, 1e-3);

  free(filter);
}

// This test takes an input signal and compares it to an expected output signal for a step response.
TEST(IirFirstOrderTest, testStepResponse){
  //Initialize test parameters
  IIRFilter* filter = (IIRFilter*) malloc(sizeof(IIRFilter));
  float alpha = 1.0f;
  float beta = 0.1f;
  float result1, result2, result3;

  //Create filter instance
  init_iir_filter(filter, alpha, beta);

  // Apply the filter to the input value
  result1 = IIR_Filter_Update(filter, 1);
  result1 = IIR_Filter_Update(filter, 1);
  result3 = IIR_Filter_Update(filter, 1);

  //Check Results
  EXPECT_NEAR(result1, 1, 1e-3);
  EXPECT_NEAR(result2, 1, 1e-3);
  EXPECT_NEAR(result3, 1, 1e-3);
}


