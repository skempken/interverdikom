//=============================================================================
/*! +dssmatrix operator */
inline const dssmatrix& operator+(const dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -dssmatrix operator */
inline _dssmatrix operator-(const dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dssmatrix newmat(mat.M,mat.N,mat.CAP);
  
  newmat.VOL=mat.VOL;
  for(long i=0; i<mat.VOL; i++){
    newmat.Array[i] =-mat.Array[i];
    newmat.Indx[i] =mat.Indx[i];
    newmat.Jndx[i] =mat.Jndx[i];
  }
  
  return _(newmat);
}
