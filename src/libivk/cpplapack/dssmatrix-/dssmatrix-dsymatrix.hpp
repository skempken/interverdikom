//=============================================================================
/*! dssmatrix+dsymatrix operator */
inline _dgematrix operator+(const dssmatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dssmatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.M!=matB.N || matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(const dssmatrix&, const dsymatrix&)"
              << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
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
/*! dssmatrix-dsymatrix operator */
inline _dgematrix operator-(const dssmatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dssmatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.M!=matB.N || matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(const dssmatrix&, const dsymatrix&)"
              << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  //// shallow copy to dgematrix ////
  dgematrix newmat(-matB);
  
  //// add ////
  for(long c=0; c<matA.VOL; c++){
    newmat(matA.Indx[c],matA.Jndx[c]) += matA.Array[c];
  }
  
  return _(newmat);
}

//=============================================================================
/*! dssmatrix*dsymatrix operator */
inline _dgematrix operator*(const dssmatrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dssmatrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(const dssmatrix&, const dsymatrix&)"
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
    for(long i=0; i<matB.N; i++){
      newmat(matA.Indx[c],i) += matA.Array[c]*matB(matA.Jndx[c],i);
    }
  }
  
  return _(newmat);
}
