//=============================================================================
/*! _zhematrix+_zhematrix operator */
inline _zhematrix operator+(const _zhematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zhematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator+(_zhematrix&, _zhematrix&)" << std::endl
              << "These two matrises can not make a summation." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") + ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<matA.N; i++){
    for(long j=0; j<matA.N; j++){
      matA.Array[i+matA.N*j]+=matB.Array[i+matA.N*j];
    }
  }

  matB.destroy();
  return matA;
}

//=============================================================================
/*! _zhematrix-_zhematrix operator */
inline _zhematrix operator-(const _zhematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zhematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator-(_zhematrix&, _zhematrix&)" << std::endl
              << "These two matrises can not make a subtraction." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") - ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  for(long i=0; i<matA.N; i++){
    for(long j=0; j<matA.N; j++){
      matA.Array[i+matA.N*j]-=matB.Array[i+matA.N*j];
    }
  }

  matB.destroy();
  return matA;
}

//=============================================================================
/*! _zhematrix*_zhematrix operator */
inline _zgematrix operator*(const _zhematrix& matA, const _zhematrix& matB)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zhematrix&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matA.N!=matB.N){
    std::cerr << "[ERROR] operator*(_zhematrix&, zhematrix&)" << std::endl
              << "These two matrises can not make a product." << std::endl
              << "Your input was (" << matA.N << "x" << matA.N << ") * ("
              << matB.N << "x" << matB.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  matB.complete();
  zgematrix newmat( matA.N, matB.N );
  
  zhemm_( 'L', 'L', matA.N, matB.N, std::complex<double>(1.0,0.0), 
          matA.Array, matA.N, matB.Array, matB.N, 
          std::complex<double>(0.0,0.0), newmat.array, newmat.m );
  
  matA.destroy();
  matB.destroy();
  return _(newmat);
}
