//=============================================================================
/*! std::complex<double>*_zssmatrix operator */
inline _zssmatrix operator*(const std::complex<double>& d, const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(mat.VOL, d, mat.Array, 1);  
  return mat;
}
