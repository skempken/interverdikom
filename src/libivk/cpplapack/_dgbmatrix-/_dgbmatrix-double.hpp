//=============================================================================
/*! _dgbmatrix*double operator */
inline _dgbmatrix operator*(const _dgbmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dgbmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_((mat.KL+mat.KU+1)*mat.N, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _dgbmatrix/double operator */
inline _dgbmatrix operator/(const _dgbmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _dgbmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_((mat.KL+mat.KU+1)*mat.N, 1./d, mat.Array, 1);
  return mat;
}
