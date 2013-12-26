//=============================================================================
/*! zhematrix=zhematrix operator */
inline zhematrix& zhematrix::operator=(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator=(const zhematrix&)"
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
/*! zhematrix+=zhematrix operator */
inline zhematrix& zhematrix::operator+=(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator+=(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] zhematrix::operator+=(zhematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << N << "x" << N << ") += ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<N; i++){ for(long j=0; j<=i; j++){
    operator()(i,j) +=mat(i,j);
  }}
  
  return *this;
}

//=============================================================================
/*! zhematrix operator-= */
inline zhematrix& zhematrix::operator-=(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator-=(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] zhematrix::operator-=(zhematrix&)" << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << N << "x" << N << ") -= ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<N; i++){ for(long j=0; j<=i; j++){
    operator()(i,j) -=mat(i,j);
  }}
  
  return *this;
}

//=============================================================================
/*! zhematrix+zhematrix operator */
inline _zhematrix operator+(const zhematrix& matA, const zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zhematrix&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(zhematrix&, zhematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  long N = matA.N;
  zhematrix newmat(N);
  for(long i=0; i<N; i++){ for(long j=0; j<=i; j++){
    newmat.Array[i+N*j] = matA.Array[i+N*j] + matB.Array[i+N*j];
  }}
  
  return _(newmat);
}

//=============================================================================
/*! zhematrix-zhematrix operator */
inline _zhematrix operator-(const zhematrix& matA, const zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zhematrix&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(zhematrix&, zhematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  long N = matA.N;
  zhematrix newmat(N);
  for(long i=0; i<N; i++){ for(long j=0; j<=i; j++){
    newmat.Array[i+N*j] =matA.Array[i+N*j]-matB.Array[i+N*j];
  }}
  
  return _(newmat);
}

//=============================================================================
/*! zhematrix*zhematrix operator */
inline _zgematrix operator*(const zhematrix& matA, const zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zhematrix&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(zhematrix&, zhematrix&)" << std::endl
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
  
  return _(newmat);
}
