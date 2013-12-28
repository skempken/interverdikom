//=============================================================================
/*! drovector=drovector operator */
inline drovector& drovector::operator=(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator=(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  if(Array!=vec.Array){ // if it is NOT self substitution
    copy(vec);
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! drovector+=drovector operator */
inline drovector& drovector::operator+=(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator+=(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] drovector::operator+=(const drovector&)" << std::endl
              << "These two vectors can not make a sumation." << std::endl
              << "Your input was (" << L << ") += (" << vec.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<L; i++){ Array[i]+=vec.Array[i]; }
  
  return *this;
}

//=============================================================================
/*! drovector operator-= */
inline drovector& drovector::operator-=(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator-=(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] drovector::operator-=(const drovector&)" << std::endl
              << "These two vectors can not make a subtraction." << std::endl
              << "Your input was (" << L << ") -= (" << vec.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<L; i++){ Array[i]-=vec.Array[i]; }
  
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! drovector+drovector operator */
inline _drovector operator+(const drovector& vecA, const drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const drovector&, const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator+(const drovector&, const drovector&)"
              << std::endl
              << "These two vectors can not make a sumation." << std::endl
              << "Your input was (" << vecA.L << ") + (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
  
#endif//CPPL_DEBUG
  
  drovector newvec(vecA.L);
  for(long i=0; i<newvec.L; i++){
    newvec.array[i] =vecA.Array[i]+vecB.Array[i];
  }
  
  return _(newvec);
}

//=============================================================================
/*! drovector-drovector operator */
inline _drovector operator-(const drovector& vecA, const drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const drovector&, const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator-(const drovector&, const drovector&)"
              << std::endl
              << "These two vectors can not make a subtraction." << std::endl
              << "Your input was (" << vecA.L << ") - (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  drovector newvec(vecA.L);
  for(long i=0; i<newvec.L; i++){
    newvec.array[i] =vecA.Array[i]-vecB.Array[i];
  }
  
  return _(newvec);
}

//=============================================================================
/*! drovector^T*drovector operator (inner product) */
inline double operator%(const drovector& vecA, const drovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator%(const drovector&, const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator%(const drovector&, const drovector&)"
              << std::endl
              << "These two vectors can not make a dot product." << std::endl
              << "Your input was (" << vecA.L << ") % (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  double val( ddot_( vecA.L, vecA.Array, 1, vecB.Array, 1 ) );
  
  return val;
}
