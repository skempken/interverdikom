//=============================================================================
/*! _zgbmatrix+zgematrix operator */
inline _zgematrix operator+(const _zgbmatrix& matA, const zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zgbmatrix&, const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(_zgbmatrix&, zgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat(matB);
  for(long i=0; i<matA.M; i++){
    for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
      newmat(i,j)+=matA(i,j);
    }
  }
  
  matA.destroy();
  return _(newmat);
}

//=============================================================================
/*! _zgbmatrix-zgematrix operator */
inline _zgematrix operator-(const _zgbmatrix& matA, const zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zgbmatrix&, const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(_zgbmatrix&, zgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat(-matB);
  for(long i=0; i<matA.M; i++){
    for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
      newmat(i,j)+=matA(i,j);
    }
  }
  
  matA.destroy();
  return _(newmat);
}

//=============================================================================
/*! _zgbmatrix*zgematrix operator */
inline _zgematrix operator*(const _zgbmatrix& matA, const zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgbmatrix&, const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(zgbmatrix&, zgematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( matA.M, matB.N );
  newmat.zero();
  
  long i, j, k;
  for(i=0; i<newmat.m; i++){
    for(j=0; j<newmat.n; j++){
      for(k=max(0,i-matA.KL); k<min(matA.N,i+matA.KU+1); k++){
        newmat(i,j)+=matA(i,k)*matB(k,j);
      }
    }
  }
  
  matA.destroy();
  return _(newmat);
}
