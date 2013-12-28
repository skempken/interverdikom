//=============================================================================
/*! _zgbmatrix+_zgematrix operator */
inline _zgematrix operator+(const _zgbmatrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zgbmatrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(_zgbmatrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matA.M; i++){
    for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
      matB(i,j)+=matA(i,j);
    }
  }
  
  matA.destroy();
  return matB;
}

//=============================================================================
/*! _zgbmatrix-_zgematrix operator */
inline _zgematrix operator-(const _zgbmatrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zgbmatrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(_zgbmatrix&, _zgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matA.M; i++){
    for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
      matB(i,j) =matA(i,j)-matB(i,j);
    }
  }
  
  matA.destroy();
  return matB;
}

//=============================================================================
/*! _zgbmatrix*_zgematrix operator */
inline _zgematrix operator*(const _zgbmatrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgbmatrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(_zgbmatrix&, _zgematrix&)" << std::endl
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
  matB.destroy();
  return _(newmat);
}
