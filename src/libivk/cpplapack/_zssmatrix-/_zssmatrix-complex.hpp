//=============================================================================
/*! _zssmatrix*std::complex<double> operator */
inline _zssmatrix operator*(const _zssmatrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zssmatrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(mat.VOL, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zssmatrix/std::complex<double> operator */
inline _zssmatrix operator/(const _zssmatrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zssmatrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(mat.VOL, 1./d, mat.Array, 1);
  return mat;
}
