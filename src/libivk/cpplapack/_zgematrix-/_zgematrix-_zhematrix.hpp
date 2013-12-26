//=============================================================================
/*! _zgematrix+_zhematrix operator */
inline _zgematrix operator+(const _zgematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zgematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator+(_zgematrix&, zhematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matB.N; i++){ for(long j=0; j<matB.N; j++){
    matA(i,j)+=matB(i,j);
  }}
  
  matB.destroy();
  return matA;
}

//=============================================================================
/*! _zgematrix-_zhematrix operator */
inline _zgematrix operator-(const _zgematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zgematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator+(_zgematrix&, zhematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matB.N; i++){ for(long j=0; j<matB.N; j++){
    matA(i,j)-=matB(i,j);
  }}
  
  matB.destroy();
  return matA;
}

//=============================================================================
/*! _zgematrix*_zhematrix operator */
inline _zgematrix operator*(const _zgematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(_zgematrix&, zhematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( matA.N, matB.N );
  zhemm_( 'R', 'L', matB.N, matA.N, std::complex<double>(1.0,0.0),
          matB.Array, matB.N, matA.Array, matA.M, 
          std::complex<double>(0.0,0.0), newmat.array, newmat.m );
  
  matA.destroy();
  matB.destroy();
  return _(newmat);
}
