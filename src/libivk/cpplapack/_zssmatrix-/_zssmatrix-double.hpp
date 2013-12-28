//=============================================================================
/*! _zssmatrix*double operator */
inline _zssmatrix operator*(const _zssmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zssmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.VOL, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zssmatrix/double operator */
inline _zssmatrix operator/(const _zssmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zssmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.VOL, 1./d, mat.Array, 1);
  return mat;
}
