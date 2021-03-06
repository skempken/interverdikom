//=============================================================================
/*! dcovector=dcovector operator */
inline dcovector& dcovector::operator=(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::operator=(const dcovector&)"
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
/*! dcovector+=dcovector operator */
inline dcovector& dcovector::operator+=(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::operator+=(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] dcovector::operator+=(const dcovector&)" << std::endl
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
/*! dcovector operator-= */
inline dcovector& dcovector::operator-=(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::operator-=(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] dcovector::operator-=(const dcovector&)" << std::endl
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
/*! dcovector+dcovector operator */
inline _dcovector operator+(const dcovector& vecA, const dcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dcovector&, const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator+(const dcovector&, const dcovector&)"
              << std::endl
              << "These two vectors can not make a sumation." << std::endl
              << "Your input was (" << vecA.L << ") + (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
  
#endif//CPPL_DEBUG
  
  dcovector newvec(vecA.L);
  for(long i=0; i<newvec.L; i++){
    newvec.array[i] =vecA.Array[i]+vecB.Array[i];
  }
  
  return _(newvec);
}

//=============================================================================
/*! dcovector-dcovector operator */
inline _dcovector operator-(const dcovector& vecA, const dcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dcovector&, const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator-(const dcovector&, const dcovector&)"
              << std::endl
              << "These two vectors can not make a subtraction." << std::endl
              << "Your input was (" << vecA.L << ") - (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dcovector newvec(vecA.L);
  for(long i=0; i<newvec.L; i++){
    newvec.array[i] =vecA.Array[i]-vecB.Array[i];
  }
  
  return _(newvec);
}

//=============================================================================
/*! dcovector^T*dcovector operator (inner product) */
inline double operator%(const dcovector& vecA, const dcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator%(const dcovector&, const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator%(const dcovector&, const dcovector&)"
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
