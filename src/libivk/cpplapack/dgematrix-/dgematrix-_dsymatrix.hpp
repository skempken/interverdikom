//=============================================================================
/*! dgematrix=_dsymatrix operator */
inline dgematrix& dgematrix::operator=(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator=(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  clear();
  mat.complete();
  
  M =mat.N;
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
  mat.Array=NULL;
  mat.Darray=NULL;
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix+=_dsymatrix operator */
inline dgematrix& dgematrix::operator+=(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator+=(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.N){
    std::cerr << "[ERROR] dgematrix::operator+=(_dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << M << "x" << N << ") += ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M; i++){
    for(long j=0; j<N; j++){
      operator()(i,j) += mat(i,j);
    }
  }
  
  mat.destroy();
  return *this;
}

//=============================================================================
/*! dgematrix-=_dsymatrix operator */
inline dgematrix& dgematrix::operator-=(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator-=(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.N){
    std::cerr << "[ERROR] dgematrix::operator-=(_dsymatrix&)" << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << M << "x" << N << ") -= ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M;i++){
    for(long j=0; j<N; j++){
      operator()(i,j) -= mat(i,j);
    }
  }
  
  mat.destroy();
  return *this;
}

//=============================================================================
/*! dgematrix*=_dsymatrix operator */
inline dgematrix& dgematrix::operator*=(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator*=(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] dgematrix::operator*=(_dsymatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << M << "x" << N << ") *= ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat( M, mat.N );
  dsymm_( 'R', 'L', mat.N, N, 1.0, mat.Array, mat.N, 
          Array, M, 0.0, newmat.Array, newmat.M );
  
  swap(*this,newmat);
  mat.destroy();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix+_dsymatrix operator */
inline _dgematrix operator+(const dgematrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dgematrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator+(dgematrix&, _dgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  dgematrix newmat(matA);
  for(long i=0; i<matA.M; i++){
    for(long j=0; j<matA.N; j++){
      newmat(i,j) += matB(i,j);
    }
  }
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! dgematrix-_dsymatrix operator */
inline _dgematrix operator-(const dgematrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dgematrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator-(dgematrix&, _dgematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  dgematrix newmat(matA);
  for(long i=0; i<matA.M; i++){
    for(long j=0; j<matA.N; j++){
      newmat(i,j) -= matB(i,j);
    }
  }
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! dgematrix*_dsymatrix operator */
inline _dgematrix operator*(const dgematrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dgematrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(dgematrix&, _dgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat( matA.N, matB.N );
  dsymm_( 'R', 'L', matB.N, matA.N, 1.0, matB.Array, matB.N, 
          matA.Array, matA.M, 0.0, newmat.Array, newmat.M );
  
  matB.destroy();
  return _(newmat);
}
