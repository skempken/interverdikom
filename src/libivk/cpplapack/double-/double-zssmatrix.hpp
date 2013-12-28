//=============================================================================
/*! double*zssmatrix operator */
inline _zssmatrix operator*(const double& d, const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zssmatrix newmat(mat.M, mat.N, mat.CAP);  
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Indx[c], mat.Jndx[c], d*mat.Array[c]);
  }
  return _(newmat);
}
