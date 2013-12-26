//=============================================================================
/*! zgematrix=zhematrix operator */
inline zgematrix& zgematrix::operator=(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator=(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  resize(mat.N, mat.N);
  for(long i=0; i<mat.N; i++){ for(long j=0; j<mat.N; j++){
    operator()(i,j) =mat(i,j);
  }}
  
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zgematrix+=zhematrix operator */
inline zgematrix& zgematrix::operator+=(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator+=(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.N){
    std::cerr << "[ERROR] zgematrix::operator+=(zhematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << M << "x" << N << ") += ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M; i++){ for( long j=0; j<N; j++){
    operator()(i,j) += mat(i,j);
  }}
  
  return *this;
}

//=============================================================================
/*! zgematrix-=zhematrix operator */
inline zgematrix& zgematrix::operator-=(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator-=(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.N){
    std::cerr << "[ERROR] zgematrix::operator-=(zhematrix&)" << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << M << "x" << N << ") -= ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M; i++){ for(long j=0; j<N; j++){
    operator()(i,j) -= mat(i,j);
  }}
  
  return *this;
}

//=============================================================================
/*! zgematrix*=zhematrix operator */
inline zgematrix& zgematrix::operator*=(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::operator*=(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] zgematrix::operator*=(zhematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << M << "x" << N << ") *= ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( M, mat.N );
  
  zhemm_( 'R', 'L', mat.N, N, std::complex<double>(1.0,0.0), mat.Array, mat.N, 
          Array, M, std::complex<double>(0.0,0.0), newmat.array, newmat.m );
  
  swap(*this,newmat);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zgematrix+zhematrix operator */
inline _zgematrix operator+(const zgematrix& matA, const zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zgematrix&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator+(zgematrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  zgematrix newmat(matA);
  for(long i=0; i<matA.M; i++){ for(long j=0; j<matA.N; j++){
    newmat(i,j) += matB(i,j);
  }}
  
  return _(newmat);
}

//=============================================================================
/*! zgematrix-zhematrix operator */
inline _zgematrix operator-(const zgematrix& matA, const zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zgematrix&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator-(zgematrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  zgematrix newmat(matA);
  for(long i=0; i<matA.M; i++){ for(long j=0; j<matA.N; j++){
    newmat(i,j) -= matB(i,j);
  }}
  
  return _(newmat);
}

//=============================================================================
/*! zgematrix*zhematrix operator */
inline _zgematrix operator*(const zgematrix& matA, const zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zgematrix&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(zgematrix&, _zhematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( matA.M, matA.N );
  zhemm_( 'R', 'L', newmat.M, newmat.N, std::complex<double>(1.0,0.0), 
          matB.Array, newmat.N, matA.Array, newmat.M, 
          std::complex<double>(0.0,0.0), newmat.array, newmat.M );
  
  return _(newmat);
}
