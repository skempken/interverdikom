//=============================================================================
/*! +zgematrix operator */
inline const zgematrix& operator+(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -zgematrix operator */
inline _zgematrix operator-(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.M,mat.N);
  for(long i=0; i<newmat.m*newmat.n; i++){ newmat.array[i]=-mat.Array[i]; }
  
  return _(newmat);
}
