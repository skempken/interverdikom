//=============================================================================
/*! +_zhematrix operator */
inline const _zhematrix& operator+(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -_zhematrix operator */
inline _zhematrix operator-(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.N; i++){ for(long j=0; j<=i; j++){
    mat.Array[i+mat.N*j]=-mat.Array[i+mat.N*j];
  }}
  
  return mat;
}
