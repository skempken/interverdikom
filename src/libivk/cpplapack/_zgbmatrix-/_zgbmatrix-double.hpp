//=============================================================================
/*! _zgbmatrix*double operator */
inline _zgbmatrix operator*(const _zgbmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgbmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_((mat.KL+mat.KU+1)*mat.N, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zgbmatrix/double operator */
inline _zgbmatrix operator/(const _zgbmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zgbmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_((mat.KL+mat.KU+1)*mat.N, 1./d, mat.Array, 1);
  return mat;
}
