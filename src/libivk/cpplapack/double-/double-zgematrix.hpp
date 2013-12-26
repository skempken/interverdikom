//=============================================================================
/*! double*zgematrix operator */
inline _zgematrix operator*(const double& d, const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.M, mat.N);
  for(long i=0; i<mat.M*mat.N; i++){ newmat.Array[i] =d*mat.Array[i]; }  
  return _(newmat);
}
