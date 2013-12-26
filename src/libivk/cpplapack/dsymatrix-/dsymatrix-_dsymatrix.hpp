//=============================================================================
/*! dsymatrix=_dsymatrix operator */
inline dsymatrix& dsymatrix::operator=(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator=(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  shallow_copy(mat);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dsymatrix+=_dsymatrix operator */
inline dsymatrix& dsymatrix::operator+=(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator+=(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] dsymatrix::operator+=(_dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << N << "x" << N << ") += ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<N*N; i++){
    Array[i]+=mat.Array[i];
  }
  
  mat.destroy();
  return *this;
}

//=============================================================================
/*! dsymatrix-=_dsymatrix operator */
inline dsymatrix& dsymatrix::operator-=(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator-=(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] dsymatrix::operator-=(_dsymatrix&)" << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << N << "x" << N << ") -= ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<N*N; i++){
    Array[i]-=mat.Array[i];
  }
  
  mat.destroy();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dsymatrix+_dsymatrix operator */
inline _dsymatrix operator+(const dsymatrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dsymatrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(dsymatrix&, _dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.N*matA.N; i++){
    matB.Array[i]+=matA.Array[i];
  }

  return matB;
}

//=============================================================================
/*! dsymatrix-_dsymatrix operator */
inline _dsymatrix operator-(const dsymatrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dsymatrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(dsymatrix&, _dsymatrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.N*matA.N; i++){
    matB.Array[i] =matA.Array[i]-matB.Array[i];
  }
  
  return matB;
}

//=============================================================================
/*! dsymatrix*_dsymatrix operator */
inline _dgematrix operator*(const dsymatrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dsymatrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(dsymatrix&, _dsymatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  matA.complete();
  matB.complete();  
  dgematrix newmat( matA.N, matA.N );
  
  dgemm_( 'N', 'N', matA.N, matB.N, matA.N, 1.0, matA.Array, matA.N,
          matB.Array, matB.N, 0.0, newmat.array, matA.N );
  
  matB.destroy();
  return _(newmat);
}
