//=============================================================================
/*! std::complex<double>*_zhematrix operator */
inline _zgematrix operator*(const std::complex<double>& d, const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat);
  zscal_(mat.N*mat.N, d, newmat.array, 1);
  
  mat.destroy();
  return _(newmat);
}
