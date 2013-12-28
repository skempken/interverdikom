//=============================================================================
/*! dgematrix=_dgematrix operator */
inline dgematrix& dgematrix::operator=(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator=(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::operator=(const _dgematrix&) was called."
            << std::endl;
#endif//CPPL_DEBUG
  
  shallow_copy(mat);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix+=_dgematrix operator */
inline dgematrix& dgematrix::operator+=(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator+=(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator+=(_dgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << M << "x" << N << ") += ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M*N; i++){ Array[i]+=mat.Array[i]; }
  
  mat.destroy();
  return *this;
}

//=============================================================================
/*! dgematrix-=_dgematrix operator */
inline dgematrix& dgematrix::operator-=(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator-=(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator-=(_dgematrix&)" << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << M << "x" << N << ") -= ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M*N; i++){ Array[i]-=mat.Array[i]; }

  mat.destroy();
  return *this;
}

//=============================================================================
/*! dgematrix*=_dgematrix operator */
inline dgematrix& dgematrix::operator*=(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator*=(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator*=(_dgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << M << "x" << N << ") *= ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat( M, mat.N );
  dgemm_( 'N', 'N', M, mat.N, N, 1.0, Array, M,
          mat.Array, mat.M, 0.0, newmat.Array, M );
  
  swap(*this,newmat);
  mat.destroy();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix+_dgematrix operator */
inline _dgematrix operator+(const dgematrix& matA, const _dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dgematrix&, const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(dgematrix&, _dgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.M*matA.N; i++){ matB.Array[i] +=matA.Array[i]; }
  
  return matB;
}

//=============================================================================
/*! dgematrix-_dgematrix operator */
inline _dgematrix operator-(const dgematrix& matA, const _dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dgematrix&, const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator-(dgematrix&, _dgematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.M*matA.N; i++){
    matB.Array[i] =matA.Array[i]-matB.Array[i];
  }
  
  return matB;
}

//=============================================================================
/*! dgematrix*_dgematrix operator */
inline _dgematrix operator*(const dgematrix& matA, const _dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dgematrix&, const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(dgematrix&, _dgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat( matA.M, matB.N );
  dgemm_( 'N', 'N', matA.M, matB.N, matA.N, 1.0, matA.Array, matA.M,
          matB.Array, matB.M, 0.0, newmat.Array, matA.M );
  
  matB.destroy();
  return _(newmat);
}
