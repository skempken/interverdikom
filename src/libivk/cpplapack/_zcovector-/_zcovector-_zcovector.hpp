//=============================================================================
/*! _zcovector+_zcovector operator */
inline _zcovector operator+(const _zcovector& vecA, const _zcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zcovector&, const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator+(const _zcovector&, const _zcovector&)"
              << std::endl
              << "These two vectors can not make a sumation." << std::endl
              << "Your input was (" << vecA.L << ") + (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
  
#endif//CPPL_DEBUG
  
  for(long i=0; i<vecA.L; i++){ vecA.Array[i]+=vecB.Array[i]; }
  
  vecB.destroy();
  return vecA;
}

//=============================================================================
/*! _zcovector-_zcovector operator */
inline _zcovector operator-(const _zcovector& vecA, const _zcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zcovector&, const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator-(const _zcovector&, const _zcovector&)"
              << std::endl
              << "These two vectors can not make a subtraction." << std::endl
              << "Your input was (" << vecA.L << ") - (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<vecA.L; i++){ vecA.Array[i]-=vecB.Array[i]; }
  
  vecB.destroy();
  return vecA;
}

//=============================================================================
/*! _zcovector^T*_zcovector operator (inner product) */
inline std::complex<double> operator%(const _zcovector& vecA, const _zcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator%(const _zcovector&, const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator%(const _zcovector&, const _zcovector&)"
              << std::endl
              << "These two vectors can not make a dot product." << std::endl
              << "Your input was (" << vecA.L << ") % (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  std::complex<double> val( zdotu_( vecA.L, vecA.Array, 1, vecB.Array, 1 ) );
  
  vecA.destroy();
  vecB.destroy();
  return val;
}
