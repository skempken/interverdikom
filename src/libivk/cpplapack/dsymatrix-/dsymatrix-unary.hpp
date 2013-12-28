//=============================================================================
/*! +dsymatrix operator */
inline const dsymatrix& operator+(const dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -dsymatrix operator */
inline _dsymatrix operator-(const dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dsymatrix newmat(mat.N);
  for(long i=0; i<newmat.N*newmat.N; i++){ newmat.Array[i]=-mat.Array[i]; }
  
  return _(newmat);
}
