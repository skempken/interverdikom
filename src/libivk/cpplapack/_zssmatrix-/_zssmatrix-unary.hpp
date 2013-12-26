//=============================================================================
/*! +_zssmatrix operator */
inline const _zssmatrix& operator+(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -_zssmatrix operator */
inline _zssmatrix operator-(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.VOL; i++){
    mat.Array[i] =-mat.Array[i];
  }  
  return mat;
}
