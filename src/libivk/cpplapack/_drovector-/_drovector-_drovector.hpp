//=============================================================================
/*! _drovector+_drovector operator */
inline _drovector operator+(const _drovector& vecA, const _drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _drovector&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator+(const _drovector&, const _drovector&)"
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
/*! _drovector-_drovector operator */
inline _drovector operator-(const _drovector& vecA, const _drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _drovector&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator-(const _drovector&, const _drovector&)"
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
/*! _drovector^T*_drovector operator (inner product) */
inline double operator%(const _drovector& vecA, const _drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator%(const _drovector&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator%(const _drovector&, const _drovector&)"
              << std::endl
              << "These two vectors can not make a dot product." << std::endl
              << "Your input was (" << vecA.L << ") % (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  double val( ddot_( vecA.L, vecA.Array, 1, vecB.Array, 1 ) );
  
  vecA.destroy();
  vecB.destroy();
  return val;
}
