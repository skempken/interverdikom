//=============================================================================
/*! zgematrix=zgematrix operator */
inline zgematrix& zgematrix::operator=(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator=(const zgematrix&)"
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
/*! zgematrix+=zgematrix operator */
inline zgematrix& zgematrix::operator+=(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator+=(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] zgematrix::operator+=(zgematrix&)" << std::endl
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
/*! zgematrix operator-= */
inline zgematrix& zgematrix::operator-=(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator-=(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] zgematrix::operator-=(zgematrix&)" << std::endl
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
/*! zgematrix operator*= */
inline zgematrix& zgematrix::operator*=(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator*=(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.M){
    std::cerr << "[ERROR] zgematrix::operator*=(zgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << M << "x" << N << ") *= ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( M, mat.N );
  zgemm_( 'N', 'N', M, mat.N, N, std::complex<double>(1.0,0.0), Array, M,
          mat.Array, mat.M, std::complex<double>(0.0,0.0), newmat.array, M );

  swap(*this,newmat);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zgematrix+zgematrix operator */
inline _zgematrix operator+(const zgematrix& matA, const zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zgematrix&, const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(zgematrix&, zgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  zgematrix newmat(matA.M,matA.N);
  for(long i=0; i<newmat.m*newmat.n; i++){
    newmat.Array[i] =matA.Array[i]+matB.Array[i];
  }
  
  return _(newmat);
}

//=============================================================================
/*! zgematrix-zgematrix operator */
inline _zgematrix operator-(const zgematrix& matA, const zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zgematrix&, const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator-(zgematrix&, zgematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  zgematrix newmat(matA.M,matA.N);
  for(long i=0; i<newmat.m*newmat.n; i++){
    newmat.Array[i] =matA.Array[i]-matB.Array[i];
  }
  
  return _(newmat);
}

//=============================================================================
/*! zgematrix*zgematrix operator */
inline _zgematrix operator*(const zgematrix& matA, const zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zgematrix&, const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(zgematrix&, zgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( matA.M, matB.N );
  zgemm_( 'N', 'N', matA.M, matB.N, matA.N, std::complex<double>(1.0,0.0), 
          matA.Array, matA.M, matB.Array, matB.M, 
          std::complex<double>(0.0,0.0), newmat.array, matA.M );
  
  return _(newmat);
}
