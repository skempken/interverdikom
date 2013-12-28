//=============================================================================
/*! dgbmatrix=_dgbmatrix operator */
inline dgbmatrix& dgbmatrix::operator=(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::operator=(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  shallow_copy(mat);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dgbmatrix+=_dgbmatrix operator\n
  If the band width of the left side matrix is narrower than the right side matrix, the band width of the left side matrix become thicker as same as the right side matrix. */
inline dgbmatrix& dgbmatrix::operator+=(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::operator+=(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] dgbmatrix::operator+=(_dgbmatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was"
              << "(" << M <<"x"<< N <<","<< KL <<":"<< KU << ") "<< "+="
              << "("<< mat.M <<"x"<< mat.N <<","<< mat.KL <<":"<< mat.KU <<") "
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if(KL>=mat.KL && KU>=mat.KU){
    for(long i=0; i<M; i++){
      for(long j=max(0,i-mat.KL); j<min(N,i+mat.KU+1); j++){
        operator()(i,j)+=mat(i,j);
      }
    }
    
    mat.destroy();
    return *this;
  }
  else{
    dgbmatrix newmat(M,N,max(KL,mat.KL),max(KU,mat.KU));
    newmat.zero();
    for(long i=0; i<M; i++){
      for(long j=max(0,i-KL); j<min(N,i+KU+1); j++){
        newmat(i,j)+=operator()(i,j);
      }
      for(long j=max(0,i-mat.KL); j<min(mat.N,i+mat.KU+1); j++){
        newmat(i,j)+=mat(i,j);
      }
    }
    
    swap(*this,newmat);
    mat.destroy();
    return *this;
  }
}

//=============================================================================
/*! dgbmatrix-=_dgbmatrix operator\n
  If the band width of the left side matrix is narrower than the right side matrix, the band width of the left side matrix become thicker as same as the right side matrix. */
inline dgbmatrix& dgbmatrix::operator-=(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::operator-=(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N || M!=mat.M){
    std::cerr << "[ERROR] dgbmatrix::operator-=(_dgbmatrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was"
              << "(" << M <<"x"<< N <<","<< KL <<":"<< KU << ") "<< "-="
              << "("<< mat.M <<"x"<< mat.N <<","<< mat.KL <<":"<< mat.KU <<") "
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if(KL>=mat.KL && KU>=mat.KU){
    for(long i=0; i<M; i++){
      for(long j=max(0,i-mat.KL); j<min(N,i+mat.KU+1); j++){
        operator()(i,j)-=mat(i,j);
      }
    }
    
    mat.destroy();
    return *this;
  }
  else{
    dgbmatrix newmat(M,N,max(KL,mat.KL),max(KU,mat.KU));
    newmat.zero();
    for(long i=0; i<M; i++){
      for(long j=max(0,i-KL); j<min(N,i+KU+1); j++){
        newmat(i,j)+=operator()(i,j);
      }
      for(long j=max(0,i-mat.KL); j<min(mat.N,i+mat.KU+1); j++){
        newmat(i,j)-=mat(i,j);
      }
    }
    
    swap(*this,newmat);
    mat.destroy();
    return *this;
  }
}

//=============================================================================
/*! dgbmatrix*=_dgbmatrix operator */
inline dgbmatrix& dgbmatrix::operator*=(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::operator*=(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.M){
    std::cerr << "[ERROR] dgbmatrix::operator*=(_dgbmatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << M << "x" << N << ") * ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgbmatrix newmat( M, mat.N, KU+mat.KL-1, KL+mat.KU+1 );
  newmat.zero();
  
  for(long i=0; i<newmat.M; i++){
    for(long j=max(0,i-newmat.KL); j<min(newmat.N,i+newmat.KU+1); j++){
      for(long k=max( max(0,i-KL), max(0,j-mat.KU) );
          k< min( min(N,i+KU+1), min(mat.M,j+mat.KL+1) ); k++){
        newmat(i,j)+= operator()(i,k)*mat(k,j);
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
/*! dgbmatrix+_dgbmatrix operator */
inline _dgbmatrix operator+(const dgbmatrix& matA, const _dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dgbmatrix&, const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator+(dgbmatrix&, _dgbmatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if(matB.KL>matA.KL && matB.KU>matA.KU){
    for(long i=0; i<matA.M; i++){
      for(long j=max(0,i-matA.KL); j<min(matA.N,i+matA.KU+1); j++){
        matB(i,j)+=matA(i,j);
      }
    }
    
    return matB;
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
    
    matB.destroy();
    return _(newmat);
  }
}

//=============================================================================
/*! dgbmatrix-_dgbmatrix operator */
inline _dgbmatrix operator-(const dgbmatrix& matA, const _dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dgbmatrix&, const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.M){
    std::cerr << "[ERROR] operator-(dgbmatrix&, _dgbmatrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") - ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
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
  
  matB.destroy();
  return _(newmat);
}

//=============================================================================
/*! dgbmatrix*_dgbmatrix operator */
inline _dgbmatrix operator*(const dgbmatrix& matA, const _dgbmatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dgbmatrix&, const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.M){
    std::cerr << "[ERROR] operator*(dgbmatrix&, _dgbmatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.M << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgbmatrix newmat( matA.M, matB.N, matA.KU+matB.KL-1, matA.KL+matB.KU+1 );
  newmat.zero();
  
  long i, j, k;
  for(i=0; i<newmat.M; i++){
    for(j=max(0,i-newmat.KL); j<min(newmat.N,i+newmat.KU+1); j++){
      for(k=max( max(0,i-matA.KL), max(0,j-matB.KU) );
          k< min( min(matA.N,i+matA.KU+1), min(matB.M,j+matB.KL+1) ); k++){
        newmat(i,j)+= matA(i,k)*matB(k,j);
      }
    }
  }
  
  matB.destroy();
  return _(newmat);
}
