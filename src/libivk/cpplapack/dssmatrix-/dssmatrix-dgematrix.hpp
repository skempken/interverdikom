//=============================================================================
/*! dssmatrix+dgematrix operator */
inline _dgematrix operator+(const dssmatrix& matA, const dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dssmatrix&, const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.M!=matB.M || matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(const dssmatrix&, const dgematrix&)"
              << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(matB);
  for(long c=0; c<matA.VOL; c++){
    newmat(matA.Indx[c],matA.Jndx[c]) += matA.Array[c];
  }
  
  return _(newmat);
}

//=============================================================================
/*! dssmatrix-dgematrix operator */
inline _dgematrix operator-(const dssmatrix& matA, const dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dssmatrix&, const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.M!=matB.M || matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(const dssmatrix&, const dgematrix&)"
              << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  dgematrix newmat(-matB);
  for(long c=0; c<matA.VOL; c++){
    newmat(matA.Indx[c],matA.Jndx[c]) += matA.Array[c];
  }
  
  return _(newmat);
}

//=============================================================================
/*! dssmatrix*dgematrix operator */
inline _dgematrix operator*(const dssmatrix& matA, const dgematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dssmatrix&, const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(const dssmatrix&, const dgematrix&)"
              << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat(matA.M, matB.N);
  newmat.zero();
  
  for(long c=0; c<matA.VOL; c++){
    for(long j=0; j<matB.N; j++){
      newmat(matA.Indx[c],j) += matA.Array[c]*matB(matA.Jndx[c],j);
    }
  }
  
  return _(newmat);
}
