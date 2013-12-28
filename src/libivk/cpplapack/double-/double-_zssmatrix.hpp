//=============================================================================
/*! double*_zssmatrix operator */
inline _zssmatrix operator*(const double& d, const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.VOL, d, mat.Array, 1);
  return mat;
}
