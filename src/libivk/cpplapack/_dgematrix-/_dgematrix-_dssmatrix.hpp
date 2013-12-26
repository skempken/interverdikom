//=============================================================================
/*! _dgematrix+_dssmatrix operator */
inline _dgematrix operator+(const _dgematrix& matA, const _dssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dgematrix&, const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.M!=matB.M || matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(const _dgematrix&, const _dssmatrix&)"
              << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<matB.VOL; c++){
    matA(matB.Indx[c],matB.Jndx[c]) += matB.Array[c];
  }
  
  matB.destroy();
  return matA;
}

//=============================================================================
/*! _dgematrix-_dssmatrix operator */
inline _dgematrix operator-(const _dgematrix& matA, const _dssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dgematrix&, const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.M!=matB.M || matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(const _dgematrix&, const _dssmatrix&)"
              << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// change sign ////
  for(long i=0; i<matA.M*matA.N; i++){
    matA.Array[i]=-matA.Array[i];
  }
  
  //// add ////
  for(long c=0; c<matB.VOL; c++){
    matA(matB.Indx[c],matB.Jndx[c]) += matB.Array[c];
  }
  
  matB.destroy();
  return matA;
}

//=============================================================================
/*! _dgematrix*_dssmatrix operator */
inline _dgematrix operator*(const _dgematrix& matA, const _dssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dgematrix&, const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(const _dgematrix&, const _dssmatrix&)"
              << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(matA.M, matB.N);
  newmat.zero();
  
  for(long c=0; c<matB.VOL; c++){
    for(long i=0; i<matA.M; i++){
      newmat(i,matB.Jndx[c]) += matA(i,matB.Indx[c])*matB.Array[c];
    }
  }
  
  matA.destroy();
  matB.destroy();
  return _(newmat);
}
