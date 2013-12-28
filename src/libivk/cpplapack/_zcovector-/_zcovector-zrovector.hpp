//=============================================================================
/*! _zcovector*zrovector operator */
inline _zgematrix operator*(const _zcovector& covec, const zrovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zcovector&, const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(covec.L!=rovec.L){
    std::cerr << "[ERROR] operator*(const _zcovector&, const zrovector&)"
              << std::endl
              << "These two vectors can not make a product." << std::endl
              << "Your input was (" << covec.L << ") * (" << rovec.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat(covec.L, covec.L);
  for(long i=0; i<newmat.m; i++){
    for(long j=0; j<newmat.n; j++){
      newmat(i,j) =covec(i)*rovec(j);
    }
  }
  
  covec.destroy();
  return _(newmat);
}
