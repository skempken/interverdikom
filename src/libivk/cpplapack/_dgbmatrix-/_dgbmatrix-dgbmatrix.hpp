//=============================================================================
/*! _dgbmatrix+dgbmatrix operator */
inline _dgbmatrix operator+(const _dgbmatrix& matA, const dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dgbmatrix&, const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(_dgbmatrix&, dgbmatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if(matA.KL>=matB.KL && matA.KU>=matB.KU){
    for(long i=0; i<matB.M; i++){
      for(long j=max(0,i-matB.KL); j<min(matB.N,i+matB.KU+1); j++){
        matA(i,j)+=matB(i,j);
      }
    }
    
    return matA;
  }
  
  else{
    dgbmatrix newmat(matA.M,matA.N,max(matA.KL,matB.KL),max(matA.KU,matB.KU));
    newmat.zero();
    
    for(long i=0; i<matA.M; i++){
      for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
        newmat(i,j)+=matA(i,j);
      }
      for(long j=max(0,i-matB.KL); j<min(matB.N,i+matB.KU+1); j++){
        newmat(i,j)+=matB(i,j);
      }
    }
    
    matA.destroy();
    return _(newmat);
  }
}

//=============================================================================
/*! _dgbmatrix-dgbmatrix operator */
inline _dgbmatrix operator-(const _dgbmatrix& matA, const dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dgbmatrix&, const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator-(_dgbmatrix&, dgbmatrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if(matA.KL>=matB.KL && matA.KU>=matB.KU){
    for(long i=0; i<matB.M; i++){
      for(long j=max(0,i-matB.KL); j<min(matB.N,i+matB.KU+1); j++){
        matA(i,j)-=matB(i,j);
      }
    }
    
    return matA;
  }
  
  else{
    dgbmatrix newmat(matA.M,matA.N,max(matA.KL,matB.KL),max(matA.KU,matB.KU));
    newmat.zero();
    
    for(long i=0; i<matA.M; i++){
      for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
        newmat(i,j)+=matA(i,j);
      }
      for(long j=max(0,i-matB.KL); j<min(matB.N,i+matB.KU+1); j++){
        newmat(i,j)-=matB(i,j);
      }
    }
    
    return _(newmat);
  }
}

//=============================================================================
/*! _dgbmatrix*dgbmatrix operator */
inline _dgbmatrix operator*(const _dgbmatrix& matA, const dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dgbmatrix&, const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(_dgbmatrix&, dgbmatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgbmatrix newmat( matA.M, matB.N, matA.KU+matB.KL-1, matA.KL+matB.KU+1 );
  newmat.zero();
  
  long i, j, k;
  for(i=0; i<newmat.m; i++){
    for(j=max(0,i-newmat.kl); j<min(newmat.n,i+newmat.ku+1); j++){
      for(k=max( max(0,i-matA.KL), max(0,j-matB.KU) );
          k< min( min(matA.N,i+matA.KU+1), min(matB.M,j+matB.KL+1) ); k++){
        newmat(i,j)+= matA(i,k)*matB(k,j);
      }
    }
  }
  
  matA.destroy();
  return _(newmat);
}
