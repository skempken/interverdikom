//=============================================================================
/*! _drovector*dcovector operator */
inline double operator*(const _drovector& rovec, const dcovector& covec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _drovector&, const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(rovec.L!=covec.L){
    std::cerr << "[ERROR] operator*(const drovector&, const dcovector&)"
              << std::endl
              << "These two vectors can not make a product." << std::endl
              << "Your input was (" << rovec.L << ") * (" << covec.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  double val( ddot_( rovec.L, rovec.Array, 1, covec.Array, 1 ) );
  
  rovec.destroy();
  return val;
}
