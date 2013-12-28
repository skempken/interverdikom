//=============================================================================
/*! dcovector*_drovector operator */
inline _dgematrix operator*(const dcovector& covec, const _drovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dcovector&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgematrix newmat(covec.L, rovec.L);
  for(long i=0; i<newmat.m; i++){ for(long j=0; j<newmat.n; j++){
    newmat(i,j) =covec(i)*rovec(j);
  }}
  
  rovec.destroy();
  return _(newmat);
}
