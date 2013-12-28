//=============================================================================
/*! +zhematrix operator */
inline const zhematrix& operator+(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -zgematrix operator */
inline _zhematrix operator-(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zhematrix newmat(mat.N);
  for(long i=0; i<mat.N; i++){ for(long j=0; j<=i; j++){
    newmat(i,j) =-mat(i,j);
  }}
  
  return _(newmat);
}
