//=============================================================================
/*! std::complex<double>*_zgbmatrix operator */
inline _zgbmatrix operator*(const std::complex<double>& d, const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_((mat.KL+mat.KU+1)*mat.N, d, mat.Array, 1);
  return mat;
}
