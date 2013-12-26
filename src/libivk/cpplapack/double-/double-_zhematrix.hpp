//=============================================================================
/*! double*_zhematrix operator */
inline _zhematrix operator*(const double& d, const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.N*mat.N, d, mat.Array, 1);
  return mat;
}
