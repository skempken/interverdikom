//=============================================================================
/*! _zgematrix+_zgematrix operator */
inline _zgematrix operator+(const _zgematrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zgematrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(_zgematrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matA.M*matA.N; i++){ matA.Array[i]+=matB.Array[i]; }

  matB.destroy();
  return matA;
}

//=============================================================================
/*! _zgematrix-_zgematrix operator */
inline _zgematrix operator-(const _zgematrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zgematrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator-(_zgematrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.M*matA.N; i++){ matA.Array[i]-=matB.Array[i]; }
  
  matB.destroy();
  return matA;
}

//=============================================================================
/*! _zgematrix*_zgematrix operator */
inline _zgematrix operator*(const _zgematrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgematrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(_zgematrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( matA.M, matB.N );
  zgemm_( 'N', 'N', matA.M, matB.N, matA.N, std::complex<double>(1.0,0.0),
          matA.Array, matA.M, matB.Array, matB.M, 
          std::complex<double>(0.0,0.0), newmat.array, matA.M );
  
  matA.destroy();
  matB.destroy();
  return _(newmat);
}
