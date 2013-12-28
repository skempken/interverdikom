//=============================================================================
/*! +_dssmatrix operator */
inline const _dssmatrix& operator+(const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -_dssmatrix operator */
inline _dssmatrix operator-(const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.VOL; i++){
    mat.Array[i] =-mat.Array[i];
  }
  
  return mat;
}
