//=============================================================================
/*! _dssmatrix*double operator */
inline _dssmatrix operator*(const _dssmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dssmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.VOL, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _dssmatrix/double operator */
inline _dssmatrix operator/(const _dssmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _dssmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.VOL, 1./d, mat.Array, 1);
  return mat;
}
