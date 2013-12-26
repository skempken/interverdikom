//=============================================================================
/*! zrovector=zrovector operator */
inline zrovector& zrovector::operator=(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::operator=(const zrovector&)"
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
/*! zrovector+=zrovector operator */
inline zrovector& zrovector::operator+=(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::operator+=(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] zrovector::operator+=(const zrovector&)" << std::endl
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
/*! zrovector operator-= */
inline zrovector& zrovector::operator-=(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::operator-=(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( L!=vec.L ){
    std::cerr << "[ERROR] zrovector::operator-=(const zrovector&)" << std::endl
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
/*! zrovector+zrovector operator */
inline _zrovector operator+(const zrovector& vecA, const zrovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zrovector&, const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator+(const zrovector&, const zrovector&)"
              << std::endl
              << "These two vectors can not make a sumation." << std::endl
              << "Your input was (" << vecA.L << ") + (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
  
#endif//CPPL_DEBUG
  
  zrovector newvec(vecA.L);
  for(long i=0; i<newvec.l; i++){
    newvec.array[i] =vecA.Array[i]+vecB.Array[i];
  }
  
  return _(newvec);
}

//=============================================================================
/*! zrovector-zrovector operator */
inline _zrovector operator-(const zrovector& vecA, const zrovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zrovector&, const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator-(const zrovector&, const zrovector&)"
              << std::endl
              << "These two vectors can not make a subtraction." << std::endl
              << "Your input was (" << vecA.L << ") - (" << vecB.L << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zrovector newvec(vecA.L);
  for(long i=0; i<newvec.l; i++){
    newvec.array[i] =vecA.Array[i]-vecB.Array[i];
  }
  
  return _(newvec);
}

//=============================================================================
/*! zrovector^T*zrovector operator (inner product) */
inline std::complex<double> operator%(const zrovector& vecA, const zrovector& vecB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator%(const zrovector&, const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vecA.L!=vecB.L){
    std::cerr << "[ERROR] operator%(const zrovector&, const zrovector&)"
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
