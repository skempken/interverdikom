//=============================================================================
/*! +dgematrix operator */
inline const dgematrix& operator+(const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -dgematrix operator */
inline _dgematrix operator-(const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgematrix newmat(mat.M,mat.N);
  for(long i=0; i<newmat.M*newmat.N; i++){ newmat.Array[i]=-mat.Array[i]; }
  return _(newmat);
}
