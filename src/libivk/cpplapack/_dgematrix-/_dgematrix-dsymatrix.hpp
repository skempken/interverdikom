//=============================================================================
/*! _dgematrix+dsymatrix operator */
inline _dgematrix operator+(const _dgematrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dgematrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator+(_dgematrix&, dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matB.N; i++){
    for(long j=0; j<matB.N; j++){
      matA(i,j)+=matB(i,j);
    }
  }
  
  return matA;
}

//=============================================================================
/*! _dgematrix-dsymatrix operator */
inline _dgematrix operator-(const _dgematrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dgematrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N || matA.M!=matB.N){
    std::cerr << "[ERROR] operator+(_dgematrix&, dsymatrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matB.N; i++){
    for(long j=0; j<matB.N; j++){
      matA(i,j)-=matB(i,j);
    }
  }
  
  return matA;
}

//=============================================================================
/*! _dgematrix*dsymatrix operator */
inline _dgematrix operator*(const _dgematrix& matA, const dsymatrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dgematrix&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(_dgematrix&, dsymatrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.M << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgematrix newmat( matA.N, matB.N );
  dsymm_( 'R', 'L', matB.N, matA.N, 1.0, matB.Array, matB.N, 
          matA.Array, matA.M, 0.0, newmat.array, newmat.m );
  
  matA.destroy();
  return _(newmat);
}
