//=============================================================================
/*! zcovector*zrovector operator */
inline _zgematrix operator*(const zcovector& covec, const zrovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zcovector&, const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(covec.L, rovec.L);
  for(long i=0; i<newmat.m; i++){
    for(long j=0; j<newmat.n; j++){
      newmat(i,j) =covec(i)*rovec(j);
    }
  }
  
  return _(newmat);
}
