//=============================================================================
/*! zcovector=zcovector operator */
inline zcovector& zcovector::operator=(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::operator=(const zcovector&)"
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
/*! zcovector+=zcovector operator */
inline zcovector& zcovector::operator+=(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::operator+=(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] zcovector::operator+=(const zcovector&)" << std::endl
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
/*! zcovector operator-= */
inline zcovector& zcovector::operator-=(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::operator-=(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] zcovector::operator-=(const zcovector&)" << std::endl
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
/*! zcovector+zcovector operator */
inline _zcovector operator+(const zcovector& vecA, const zcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zcovector&, const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator+(const zcovector&, const zcovector&)"
              << std::endl
              << "These two vectors can not make a sumation." << std::endl
              << "Your input was (" << vecA.L << ") + (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
  
#endif//CPPL_DEBUG
  
  zcovector newvec(vecA.L);
  for(long i=0; i<newvec.L; i++){
    newvec.array[i] =vecA.Array[i]+vecB.Array[i];
  }
  
  return _(newvec);
}

//=============================================================================
/*! zcovector-zcovector operator */
inline _zcovector operator-(const zcovector& vecA, const zcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zcovector&, const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator-(const zcovector&, const zcovector&)"
              << std::endl
              << "These two vectors can not make a subtraction." << std::endl
              << "Your input was (" << vecA.L << ") - (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zcovector newvec(vecA.L);
  for(long i=0; i<newvec.L; i++){
    newvec.array[i] =vecA.Array[i]-vecB.Array[i];
  }
  
  return _(newvec);
}

//=============================================================================
/*! zcovector^T*zcovector operator (inner product) */
inline std::complex<double> operator%(const zcovector& vecA, const zcovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator%(const zcovector&, const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator%(const zcovector&, const zcovector&)"
              << std::endl
              << "These two vectors can not make a dot product." << std::endl
              << "Your input was (" << vecA.L << ") % (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  std::complex<double> val( zdotu_( vecA.L, vecA.Array, 1, vecB.Array, 1 ) );
  
  return val;
}
