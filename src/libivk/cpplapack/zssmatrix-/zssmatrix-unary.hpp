//=============================================================================
/*! +zssmatrix operator */
inline const zssmatrix& operator+(const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -zssmatrix operator */
inline _zssmatrix operator-(const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zssmatrix newmat(mat.M,mat.N,mat.CAP);
  
  newmat.VOL=mat.VOL;
  for(long i=0; i<mat.VOL; i++){
    newmat.Array[i] =-mat.Array[i];
    newmat.Indx[i] =mat.Indx[i];
    newmat.Jndx[i] =mat.Jndx[i];
  }
  
  return _(newmat);
}
