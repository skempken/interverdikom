//=============================================================================
/*! dgbmatrix+_dsymatrix operator */
inline _dgematrix operator+(const dgbmatrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dgbmatrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator+(dgbmatrix&, _dgematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(matB.N,matB.N);
  for(long i=0; i<matA.M; i++){
    for(long j=0; j<matB.N; j++){
      newmat(i,j) = matB(i,j);
    }
    for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
      newmat(i,j)+=matA(i,j);
    }
  }
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! dgbmatrix-_dsymatrix operator */
inline _dgematrix operator-(const dgbmatrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dgbmatrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator+(dgbmatrix&, _dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(matB.N,matB.N);
  for(long i=0; i<matA.M; i++){
    for(long j=0; j<matB.N; j++){
      newmat(i,j) = -matB(i,j);
    }
    for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
      newmat(i,j) += matA(i,j);
    }
  }
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! dgbmatrix*_dsymatrix operator */
inline _dgematrix operator*(const dgbmatrix& matA, const _dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dgbmatrix&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(dgbmatrix&, _dsymatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat( matA.M, matB.N );
  newmat.zero();
  
  long i, j, k;
  for(i=0; i<newmat.m; i++){
    for(j=0; j<newmat.n; j++){
      for(k=max(0,i-matA.KL); k<min(matA.N,i+matA.KU+1); k++){
        newmat(i,j)+=matA(i,k)*matB(k,j);
      }
    }
  }
  
  matB.destroy();
  return _(newmat);
}
