//=============================================================================
/*! double*dgematrix operator */
inline _dgematrix operator*(const double& d, const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgematrix newmat(mat.M, mat.N);
  for(long i=0; i<mat.M*mat.N; i++){ newmat.Array[i] =d*mat.Array[i]; }
  return _(newmat);
}
