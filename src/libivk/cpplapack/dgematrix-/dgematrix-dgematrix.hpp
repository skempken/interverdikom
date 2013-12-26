//=============================================================================
/*! dgematrix=dgematrix operator */
inline dgematrix& dgematrix::operator=(const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator=(const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  if(Array!=mat.Array){ // if it is NOT self substitution
    copy(mat);
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix+=dgematrix operator */
inline dgematrix& dgematrix::operator+=(const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator+=(const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator+=(dgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << M << "x" << N << ") += ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M*N; i++){ Array[i]+=mat.Array[i]; }
  return *this;
}

//=============================================================================
/*! dgematrix operator-= */
inline dgematrix& dgematrix::operator-=(const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator-=(const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator-=(dgematrix&)" << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << M << "x" << N << ") -= ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M*N; i++){ Array[i]-=mat.Array[i]; }
  return *this;
}

//=============================================================================
/*! dgematrix operator*= */
inline dgematrix& dgematrix::operator*=(const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator*=(const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator*=(dgematrix&)" << std::endl
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
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix+dgematrix operator */
inline _dgematrix operator+(const dgematrix& matA, const dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dgematrix&, const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(dgematrix&, dgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  dgematrix newmat(matA.M,matA.N);
  for(long i=0; i<newmat.M*newmat.N; i++){
    newmat.Array[i] =matA.Array[i]+matB.Array[i];
  }
  
  return _(newmat);
}

//=============================================================================
/*! dgematrix-dgematrix operator */
inline _dgematrix operator-(const dgematrix& matA, const dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dgematrix&, const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator-(dgematrix&, dgematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  dgematrix newmat(matA.M,matA.N);
  for(long i=0; i<newmat.M*newmat.N; i++){
    newmat.Array[i] =matA.Array[i]-matB.Array[i];
  }
  
  return _(newmat);
}

//=============================================================================
/*! dgematrix*dgematrix operator */
inline _dgematrix operator*(const dgematrix& matA, const dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dgematrix&, const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(dgematrix&, dgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat( matA.M, matB.N );
  dgemm_( 'N', 'N', matA.M, matB.N, matA.N, 1.0, matA.Array, matA.M,
          matB.Array, matB.M, 0.0, newmat.Array, matA.M );
  
  return _(newmat);
}
