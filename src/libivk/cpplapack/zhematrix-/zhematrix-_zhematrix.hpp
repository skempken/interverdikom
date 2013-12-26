//=============================================================================
/*! zhematrix=_zhematrix operator */
inline zhematrix& zhematrix::operator=(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator=(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  shallow_copy(mat);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zhematrix+=_zhematrix operator */
inline zhematrix& zhematrix::operator+=(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator+=(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] zhematrix::operator+=(_zhematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << N << "x" << N << ") += ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<N; i++){ for(long j=0; j<=i; j++){
    Array[i+N*j]+=mat.Array[i+N*j];
  }}
  
  mat.destroy();
  return *this;
}

//=============================================================================
/*! zhematrix-=_zhematrix operator */
inline zhematrix& zhematrix::operator-=(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator-=(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] zhematrix::operator-=(_zhematrix&)" << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << N << "x" << N << ") -= ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<N; i++){ for(long j=0; j<=i; j++){
    Array[i+N*j]-=mat.Array[i+N*j];
  }}
  
  mat.destroy();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zhematrix+_zhematrix operator */
inline _zhematrix operator+(const zhematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zhematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(zhematrix&, _zhematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.N; i++){ for(long j=0; j<=i; j++){
    matB.Array[i+matA.N*j]+=matA.Array[i+matA.N*j];
  }}
  
  return matB;
}

//=============================================================================
/*! zhematrix-_zhematrix operator */
inline _zhematrix operator-(const zhematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zhematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(zhematrix&, _zhematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matA.N; i++){ for(long j=0; j<=i; j++){
    matB.Array[i] =matA.Array[i]-matB.Array[i];
  }}
  
  return matB;
}

//=============================================================================
/*! zhematrix*_zhematrix operator */
inline _zgematrix operator*(const zhematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zhematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(zhematrix&, _zhematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  matB.complete();
  zgematrix newmat( matA.N, matB.N );
  
  zhemm_( 'L', 'L', matA.N, matB.N, std::complex<double>(1.0,0.0), 
          matA.Array, matA.N, matB.Array, matB.N, 
          std::complex<double>(0.0,0.0), newmat.array, newmat.m );
  
  matB.destroy();
  return _(newmat);
}
