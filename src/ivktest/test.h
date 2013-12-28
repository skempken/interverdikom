#ifndef TEST_H_
#define TEST_H_

#include <rvector.hpp>
using cxsc::rvector;

// Helper functions
rvector frame2gop(rvector data, const int gopsize);

rvector loadData(const char* filename);

// test convolution
void test_subConv();

/// Some examples from Traczinski Dissertation
void test_cicircle();

// Gauss Approximation
void test_gauss();

// Roots
void test_roots();

// Roots of unity
void test_rootsofunity();

// Large GI/G/1 example
void test_GIG1();

// Large GI/G/1 example
void test_largeGIG1();

// Example from Chaudhry No. 4
void test_chaudhry4();

// SMP Example
void test_SMP3();

// Example from Chaudhry No. 4
void test_circular();

// straight comvolution
void test_conv();

// fast comvolution
void test_fft_conv();

// Fast autocorrelation
void test_fautocorrelation();

void test_matrix_solving();

// Interval fast convoliution
void test_Iconv();

// Test AutoSMPModeler
void test_ASMP();

// Matrix accumulator
void test_matrixaccu();

// Prony method
void test_Prony();

// More prony
void test_PM();

// Toeplitz solver
void test_Toeplitz();

// Vandermonde solver
void test_Vandermonde();

// Port of INTLAB function verifyeig()
void test_verifyeig_port();

void test_eig_wrapper();

void test_polyeig();

#endif /*TEST_H_*/
