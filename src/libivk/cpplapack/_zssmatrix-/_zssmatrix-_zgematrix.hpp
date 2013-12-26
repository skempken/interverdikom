//=============================================================================
/*! _zssmatrix+_zgematrix operator */
inline _zgematrix operator+(const _zssmatrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zssmatrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.M!=matB.M || matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(const _zssmatrix&, const _zgematrix&)"
              << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<matA.VOL; c++){
    matB(matA.Indx[c],matA.Jndx[c]) += matA.Array[c];
  }
  
  matA.destroy();
  return matB;
}

//=============================================================================
/*! _zssmatrix-_zgematrix operator */
inline _zgematrix operator-(const _zssmatrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zssmatrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.M!=matB.M || matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(const _zssmatrix&, const _zgematrix&)"
              << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// change sign ////
  for(int i=0; i<matB.M*matB.N; i++){
    matB.Array[i] = -matB.Array[i];
  }
  
  for(long c=0; c<matA.VOL; c++){
    matB(matA.Indx[c],matA.Jndx[c]) += matA.Array[c];
  }
  
  matA.destroy();
  return matB;
}

//=============================================================================
/*! _zssmatrix*_zgematrix operator */
inline _zgematrix operator*(const _zssmatrix& matA, const _zgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zssmatrix&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(const _zssmatrix&, const _zgematrix&)"
              << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix newmat(matA.M, matB.N);
  newmat.zero();
  
  for(long c=0; c<matA.VOL; c++){
    for(long j=0; j<matB.N; j++){
      newmat(matA.Indx[c],j) += matA.Array[c]*matB(matA.Jndx[c],j);
    }
  }
  
  matA.destroy();
  matB.destroy();
  return _(newmat);
}
