//=============================================================================
/*! double*dsymatrix operator */
inline _dsymatrix operator*(const double& d, const dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dsymatrix newmat(mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.Array[i] =d*mat.Array[i]; }  
  return _(newmat);
}
