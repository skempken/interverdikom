//=============================================================================
/*! _dcovector*_drovector operator */
inline _dgematrix operator*(const _dcovector& covec, const _drovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dcovector&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(covec.L!=rovec.L){
    std::cerr << "[ERROR] operator*(const dcovector&, const drovector&)"
              << std::endl
              << "These two vectors can not make a product." << std::endl
              << "Your input was (" << covec.L << ") * (" << rovec.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(covec.L, covec.L);
  for(long i=0; i<newmat.m; i++){
    for(long j=0; j<newmat.n; j++){
      newmat(i,j) =covec(i)*rovec(j);
    }
  }
  
  covec.destroy();
  rovec.destroy();
  return _(newmat);
}
