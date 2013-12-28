//=============================================================================
/*! zssmatrix=_zssmatrix operator */
inline zssmatrix& zssmatrix::operator=(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator=(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  shallow_copy(mat);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zssmatrix+=_zssmatrix operator */
inline zssmatrix& zssmatrix::operator+=(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator+=(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] zssmatrix::operator+=(const _zssmatrix&)"
              << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << M << "x" << N << ") += ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<mat.VOL; c++){
    add(mat.Indx[c],mat.Jndx[c], mat.Array[c]);
  }
  
  mat.destroy();
  return *this;
}

//=============================================================================
/*! zssmatrix-=_zssmatrix operator */
inline zssmatrix& zssmatrix::operator-=(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator-=(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] zssmatrix::operator-=(const _zssmatrix&)"
              << std::endl
              << "These two matrises can not make a sutraction." << std::endl
              << "Your input was (" << M << "x" << N << ") -= ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<mat.VOL; c++){
    sub(mat.Indx[c],mat.Jndx[c], mat.Array[c]);
  }
  
  mat.destroy();
  return *this;
}

//=============================================================================
/*! zssmatrix*=_zssmatrix operator */
inline zssmatrix& zssmatrix::operator*=(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator*=(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.M){
    std::cerr << "[ERROR] zssmatrix::operator*=(const _zssmatrix&)"
              << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << M << "x" << N << ") *= ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zssmatrix newmat( M, mat.N, 0 );
  
  for(long c=0; c<VOL; c++){
    for(long d=0; d<mat.VOL; d++){
      if(Jndx[c]==mat.Indx[d]){
        newmat.add(Indx[c], mat.Jndx[d], Array[c]*mat.Array[d]);
      }
    }
  }
  
  swap(*this,newmat);
  mat.destroy();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zssmatrix+_zssmatrix operator */
inline _zssmatrix operator+(const zssmatrix& matA, const _zssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zssmatrix&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(const zssmatrix&, const _zssmatrix&)"
              << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zssmatrix newmat(matB);
  
  for(long c=0; c<matA.VOL; c++){
    newmat.add(matA.Indx[c], matA.Jndx[c], matA.Array[c]);
  }
  
  return _(newmat);
}

//=============================================================================
/*! zssmatrix-_zssmatrix operator */
inline _zssmatrix operator-(const zssmatrix& matA, const _zssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zssmatrix&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator-(const zssmatrix&, const zssmatrix&)"
              << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zssmatrix newmat(matB);
  newmat.chsign();
  
  //// add ////
  for(long c=0; c<matA.VOL; c++){
    newmat.add(matA.Indx[c], matA.Jndx[c], matA.Array[c]);
  }
  
  return _(newmat);
}

//=============================================================================
/*! zssmatrix*_zssmatrix operator */
inline _zssmatrix operator*(const zssmatrix& matA, const _zssmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zssmatrix&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(const zssmatrix&, const zssmatrix&)"
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
  
  matB.destroy();
  return _(newmat);
}
