//=============================================================================
/*! _zgematrix+zhematrix operator */
inline _zgematrix operator+(const zhematrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zhematrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.N!=matB.M){
    std::cerr << "[ERROR] operator+(zhematrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matA.N; i++){ for(long j=0; j<matA.N; j++){
    matB(i,j)+=matA(i,j);
  }}
  
  return matB;
}

//=============================================================================
/*! _zgematrix-zgematrix operator */
inline _zgematrix operator-(const zhematrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zhematrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.N!=matB.M){
    std::cerr << "[ERROR] operator-(zhematrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.N; i++){ for(long j=0; j<matA.N; j++){
    matB(i,j) =matA(i,j)-matB(i,j);
  }}
  
  return matB;
}

//=============================================================================
/*! _zgematrix*zgematrix operator */
inline _zgematrix operator*(const zhematrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zhematrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(zhematrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( matA.N, matB.N );
  zhemm_( 'L', 'L', matA.N, matB.N, std::complex<double>(1.0,0.0),
          matA.Array, matA.N, matB.Array, matB.M,
          std::complex<double>(0.0,0.0), newmat.array, newmat.m );
  
  matB.destroy();
  return _(newmat);
}
