//=============================================================================
/*! _zhematrix+zgbmatrix operator */
inline _zgematrix operator+(const _zhematrix& matA, const zgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zhematrix&, const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.N!=matB.M){
    std::cerr << "[ERROR] operator+(_zgematrix&, zgbmatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat(matA.N, matA.N);
  for(long i=0; i<matB.M; i++){
    for(long j=0; j<matA.N; j++){
      newmat(i,j) =matA(i,j);
    }
    for(long j=max(0,i-matB.KL); j<min(matB.N,i+matB.KU+1); j++){
      newmat(i,j)+=matB(i,j);
    }
  }
  
  matA.destroy();
  return _(newmat);
}

//=============================================================================
/*! _zhematrix-zgbmatrix operator */
inline _zgematrix operator-(const _zhematrix& matA, const zgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zhematrix&, const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.N!=matB.M){
    std::cerr << "[ERROR] operator+(_zhematrix&, zgbmatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat(matA.N, matA.N);
  for(long i=0; i<matB.M; i++){
    for(long j=0; j<matA.N; j++){
      newmat(i,j) =matA(i,j);
    }
    for(long j=max(0,i-matB.KL); j<min(matB.N,i+matB.KU+1); j++){
      newmat(i,j)-=matB(i,j);
    }
  }
  
  matA.destroy();
  return _(newmat);
}

//=============================================================================
/*! _zgematrix*zgbmatrix operator */
inline _zgematrix operator*(const _zhematrix& matA, const zgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zhematrix&, const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(_zhematrix&, zgbmatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat( matA.N, matB.N );
  newmat.zero();
  
  long i, j, k;
  for(i=0; i<newmat.m; i++){
    for(j=0; j<newmat.n; j++){
      for(k=max(0,j-matB.KU); k<min(matB.M,j+matB.KL+1); k++){
        newmat(i,j)+=matA(i,k)*matB(k,j);
      }
    }
  }
  
  matA.destroy();
  return _(newmat);
}
