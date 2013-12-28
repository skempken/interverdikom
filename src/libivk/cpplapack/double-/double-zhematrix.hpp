//=============================================================================
/*! double*zhematrix operator */
inline _zhematrix operator*(const double& d, const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zhematrix newmat(mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.Array[i] =d*mat.Array[i]; }  
  return _(newmat);
}
