//=============================================================================
/*! zrovector*zcovector operator */
inline std::complex<double> operator*(const zrovector& rovec, const zcovector& covec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zrovector&, const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(rovec.L!=covec.L){
    std::cerr << "[ERROR] operator*(const zrovector&, const zcovector&)"
              << std::endl
              << "These two vectors can not make a product." << std::endl
              << "Your input was (" << rovec.L << ") * (" << covec.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  std::complex<double> val( zdotu_( rovec.L, rovec.Array, 1, covec.Array, 1 ) );
  
  return val;
}
