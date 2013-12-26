//=============================================================================
/*! dcovector*drovector operator */
inline _dgematrix operator*(const dcovector& covec, const drovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dcovector&, const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgematrix newmat(covec.L, rovec.L);
  for(long i=0; i<newmat.m; i++){ for(long j=0; j<newmat.n; j++){
    newmat(i,j) =covec(i)*rovec(j);
  }}
  
  return _(newmat);
}
