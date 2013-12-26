//=============================================================================
/*! double*_dssmatrix operator */
inline _dssmatrix operator*(const double& d, const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.VOL, d, mat.Array, 1);
  return mat;
}
