//=============================================================================
/*! drovector=_drovector operator */
inline drovector& drovector::operator=(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator=(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::operator=(const _drovector&) was called."
            << std::endl;
#endif//CPPL_DEBUG
  
  shallow_copy(vec);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! drovector+=_drovector operator */
inline drovector& drovector::operator+=(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator+=(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] drovector::operator+=(const _drovector&)" << std::endl
              << "These two vectors can not make a sumation." << std::endl
              << "Your input was (" << L << ") += (" << vec.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<L; i++){ Array[i]+=vec.Array[i]; }
  
  vec.destroy();
  return *this;
}

//=============================================================================
/*! drovector operator-= */
inline drovector& drovector::operator-=(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator-=(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] drovector::operator-=(const _drovector&)" << std::endl
              << "These two vectors can not make a subtraction." << std::endl
              << "Your input was (" << L << ") -= (" << vec.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<L; i++){ Array[i]-=vec.Array[i]; }
  
  vec.destroy();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! drovector+drovector operator */
inline _drovector operator+(const drovector& vecA, const _drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const drovector&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator+(const drovector&, const _drovector&)"
              << std::endl
              << "These two vectors can not make a sumation." << std::endl
              << "Your input was (" << vecA.L << ") + (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
  
#endif//CPPL_DEBUG
  
  for(long i=0; i<vecA.L; i++){ vecB.Array[i]+=vecA.Array[i]; }
  
  return vecB;
}

//=============================================================================
/*! drovector-drovector operator */
inline _drovector operator-(const drovector& vecA, const _drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const drovector&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator-(const drovector&, const _drovector&)"
              << std::endl
              << "These two vectors can not make a subtraction." << std::endl
              << "Your input was (" << vecA.L << ") - (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<vecA.L; i++){
    vecB.Array[i] =vecA.Array[i]-vecB.Array[i];
  }
  
  return vecB;
}

//=============================================================================
/*! drovector^T*drovector operator (inner product) */
inline double operator%(const drovector& vecA, const _drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator%(const drovector&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator%(const drovector&, const _drovector&)"
              << std::endl
              << "These two vectors can not make a dot product." << std::endl
              << "Your input was (" << vecA.L << ") % (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  double val( ddot_( vecA.L, vecA.Array, 1, vecB.Array, 1 ) );
  
  vecB.destroy();
  return val;
}
