//=============================================================================
/*! std::complex<double>*_zgematrix operator */
inline _zgematrix operator*(const std::complex<double>& d, const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(mat.M*mat.N, d, mat.Array, 1);  
  return mat;
}
