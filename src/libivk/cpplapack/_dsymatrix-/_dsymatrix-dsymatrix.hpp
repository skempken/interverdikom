//=============================================================================
/*! _dsymatrix+dsymatrix operator */
inline _dsymatrix operator+(const _dsymatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dsymatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(_dsymatrix&, dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matA.N*matA.N; i++){ matA.Array[i]+=matB.Array[i]; }
  
  return matA;
}

//=============================================================================
/*! _dsymatrix-dsymatrix operator */
inline _dsymatrix operator-(const _dsymatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dsymatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(_dsymatrix&, dsymatrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.N*matA.N; i++){ matA.Array[i]-=matB.Array[i]; }
  
  return matA;
}

//=============================================================================
/*! _dsymatrix*dsymatrix operator */
inline _dgematrix operator*(const _dsymatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dsymatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(_dsymatrix&, dsymatrix&)" << std::endl
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
  
  matA.destroy();
  return _(newmat);
}
