//=============================================================================
/*! dgematrix=_dgbmatrix operator */
inline dgematrix& dgematrix::operator=(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator=(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  resize(mat.M, mat.N);
  zero();
  for(long i=0; i<mat.M; i++){
    for(long j=max(0,i-mat.KL); j<min(N,i+mat.KU+1); j++){
      operator()(i,j)=mat(i,j);
    }
  }
  
  mat.destroy();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix+=_dgbmatrix operator */
inline dgematrix& dgematrix::operator+=(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator+=(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator+=(const _dgbmatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << M << "x" << N << ") += ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<mat.M; i++){
    for(long j=max(0,i-mat.KL); j<min(N,i+mat.KU+1); j++){
      operator()(i,j)+=mat(i,j);
    }
  }
  
  mat.destroy();
  return *this;
}

//=============================================================================
/*! dgematrix-=_dgbmatrix operator */
inline dgematrix& dgematrix::operator-=(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator-=(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator-=(const _dgbmatrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << M << "x" << N << ") -= ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<mat.M; i++){
    for(long j=max(0,i-mat.KL); j<min(N,i+mat.KU+1); j++){
      operator()(i,j)-=mat(i,j);
    }
  }
  
  mat.destroy();
  return *this;
}
//=============================================================================
/*! dgematrix*=_dgbmatrix operator */
inline dgematrix& dgematrix::operator*=(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator*=(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE

#ifdef  CPPL_DEBUG
  if(N!=mat.M){
    std::cerr << "[ERROR] dgematrix::operator*=(const _dgbmatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << M << "x" << N << ") *= ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(M,mat.N);
  newmat.zero();
  
  for(long i=0; i<newmat.M; i++){ for(long j=0; j<newmat.N; j++){
    for(long k=max(0,j-mat.KU); k<min(mat.M,j+mat.KL+1); k++){
      newmat(i,j)+=operator()(i,k)*mat(k,j);
    }
  }}
  
  swap(*this, newmat);
  mat.destroy();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgematrix+_dgbmatrix operator */
inline _dgematrix operator+(const dgematrix& matA, const _dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dgematrix&, const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(dgematrix&, dgbmatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(matA);
  
  for(long i=0; i<matB.M; i++){
    for(long j=max(0,i-matB.KL); j<min(matB.N,i+matB.KU+1); j++){
      newmat(i,j)+=matB(i,j);
    }
  }
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! dgematrix-_dgbmatrix operator */
inline _dgematrix operator-(const dgematrix& matA, const _dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dgematrix&, const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(dgematrix&, _dgbmatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(matA);
  
  for(long i=0; i<matB.M; i++){
    for(long j=max(0,i-matB.KL); j<min(matB.N,i+matB.KU+1); j++){
      newmat(i,j)-=matB(i,j);
    }
  }
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! dgematrix*_dgbmatrix operator */
inline _dgematrix operator*(const dgematrix& matA, const _dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dgematrix&, const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(dgematrix&, _dgbmatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat( matA.M, matB.N );
  newmat.zero();
  
  long i, j, k;
  for(i=0; i<newmat.M; i++){
    for(j=0; j<newmat.N; j++){
      for(k=max(0,j-matB.KU); k<min(matB.M,j+matB.KL+1); k++){
        newmat(i,j)+=matA(i,k)*matB(k,j);
      }
    }
  }
  
  matB.destroy();
  return _(newmat);
}
