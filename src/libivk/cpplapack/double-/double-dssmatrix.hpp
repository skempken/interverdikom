//=============================================================================
/*! double*dssmatrix operator */
inline _dssmatrix operator*(const double& d, const dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dssmatrix newmat(mat.M, mat.N, mat.CAP);  
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Indx[c], mat.Jndx[c], d*mat.Array[c]);
  }
  return _(newmat);
}
