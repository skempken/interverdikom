//=============================================================================
/*! std::complex<double>*zssmatrix operator */
inline _zssmatrix operator*(const std::complex<double>& d, const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zssmatrix newmat(mat.M, mat.N, mat.CAP);
  for(long i=0; i<mat.VOL; i++){ newmat.Array[i] =d*mat.Array[i]; }
  
  return _(newmat);
}
