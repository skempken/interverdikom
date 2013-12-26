//=============================================================================
/*! dsymatrix=dsymatrix operator */
inline dsymatrix& dsymatrix::operator=(const dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator=(const dsymatrix&)"
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
/*! dsymatrix+=dsymatrix operator */
inline dsymatrix& dsymatrix::operator+=(const dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator+=(const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] dsymatrix::operator+=(dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << N << "x" << N << ") += ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<N*N; i++){
    Array[i]+=mat.Array[i];
  }
  return *this;
}

//=============================================================================
/*! dsymatrix operator-= */
inline dsymatrix& dsymatrix::operator-=(const dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator-=(const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] dsymatrix::operator-=(dsymatrix&)" << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << N << "x" << N << ") -= ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<N*N; i++){
    Array[i]-=mat.Array[i];
  }
  return *this;
}

//=============================================================================
/*! dsymatrix+dsymatrix operator */
inline _dsymatrix operator+(const dsymatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dsymatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(dsymatrix&, dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  long N = matA.N;
  dsymatrix newmat(N);
  for(long i=0; i<N*N; i++){
    newmat.Array[i] = matA.Array[i] + matB.Array[i];
  }
  return _(newmat);
}

//=============================================================================
/*! dsymatrix-dsymatrix operator */
inline _dsymatrix operator-(const dsymatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dsymatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(dsymatrix&, dsymatrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  long N = matA.N;
  dsymatrix newmat(N);
  for(long i=0; i<N*N; i++){
    newmat.Array[i] =matA.Array[i]-matB.Array[i];
  }
  
  return _(newmat);
}

//=============================================================================
/*! dsymatrix*dsymatrix operator */
inline _dgematrix operator*(const dsymatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dsymatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(dsymatrix&, dsymatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  matA.complete();
  matB.complete();
  dgematrix newmat(matA.N, matA.N);
  
  dgemm_( 'N', 'N', matA.N, matB.N, matA.N, 1.0, matA.Array, matA.N,
          matB.Array, matB.N, 0.0, newmat.array, matA.N );
  
  return _(newmat);
}
