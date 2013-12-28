//=============================================================================
/*! _zssmatrix+_zssmatrix operator */
inline _zssmatrix operator+(const _zssmatrix& matA, const _zssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zssmatrix&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(const _zssmatrix&, const _zssmatrix&)"
              << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zssmatrix newmat(matA);
  
  for(long c=0; c<matB.VOL; c++){
    newmat.add(matB.Indx[c], matB.Jndx[c], matB.Array[c]);
  }
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! _zssmatrix-_zssmatrix operator */
inline _zssmatrix operator-(const _zssmatrix& matA, const _zssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zssmatrix&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator-(const _zssmatrix&, const _zssmatrix&)"
              << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zssmatrix newmat(matA);
  
  for(long c=0; c<matB.VOL; c++){
    newmat.sub(matB.Indx[c], matB.Jndx[c], matB.Array[c]);
  }
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! _zssmatrix*_zssmatrix operator */
inline _zssmatrix operator*(const _zssmatrix& matA, const _zssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zssmatrix&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(const _zssmatrix&, const _zssmatrix&)"
              << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zssmatrix newmat( matA.M, matB.N, 0 );
  
  for(long c=0; c<matA.VOL; c++){
    for(long d=0; d<matB.VOL; d++){
      if(matA.Jndx[c]==matB.Indx[d]){
        newmat.add(matA.Indx[c], matB.Jndx[d], matA.Array[c]*matB.Array[d]);
      }
    }
  }
  
  matA.destroy();
  matB.destroy();
  return _(newmat);
}
