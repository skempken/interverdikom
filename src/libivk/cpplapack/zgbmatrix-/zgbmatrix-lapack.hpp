//=============================================================================
/*! solve A*X=Y using zgbsv\n
  The argument is zgematrix Y. Y is overwritten and become the solution X.
  A is also overwritten. */
inline long zgbmatrix::zgbsv(zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::zgbsv(zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N || N!=mat.M){
    std::cerr << "[ERROR] zgbmatrix::zgbsv(zgematrix&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG 
  
  zgbmatrix newmat(M,N,KL,KU+KL);
  for(long i=0; i<M; i++){ for(long j=max(0,i-KL); j<min(n,i+KU+1); j++){
    newmat(i,j) =operator()(i,j);
  }}
  
  long NRHS(mat.N), LDAB(2*KL+KU+1),
    *IPIV(new long[N]), LDB(mat.M), INFO(1);
  zgbsv_(N, KL, KU, NRHS, newmat.Array, LDAB, IPIV, mat.Array, LDB, INFO);
  delete [] IPIV;
  
  swap(*this,newmat);
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgbmatrix::zgbsv(zgematrix&) "
              << "Serious trouble happend. INFO = "<< INFO << "." << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve A*x=y using zgbsv\n
  The argument is zcovector y. y is overwritten and become the solution x.
  A is also overwritten. */
inline long zgbmatrix::zgbsv(zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::zgbsv(zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N || N!=vec.L){
    std::cerr << "[ERROR] zgbmatrix::zgbsv(zcovector&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG 
  
  zgbmatrix newmat(M,N,KL,KU+KL);
  for(long i=0; i<M; i++){ for(long j=max(0,i-KL); j<min(n,i+KU+1); j++){
    newmat(i,j) =operator()(i,j);
  }}
  
  long NRHS(1), LDAB(2*KL+KU+1),
    *IPIV(new long[N]), LDB(vec.L), INFO(1);
  zgbsv_(N, KL, KU, NRHS, newmat.Array, LDAB, IPIV, vec.Array, LDB, INFO);
  delete [] IPIV;
  
  swap(*this,newmat);
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgbmatrix::zgbsv(zcovector&) "
              << "Serious trouble happend. INFO = "<< INFO << "." << std::endl;
  }
  return INFO;
}
