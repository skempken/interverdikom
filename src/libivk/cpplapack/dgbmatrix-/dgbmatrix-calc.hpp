//=============================================================================
/*! return transposed dgbmatrix */
inline _dgbmatrix t(const dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgbmatrix newmat(mat.N, mat.M, mat.KU, mat.KL);
  for(long i=0; i<newmat.M; i++){
    for(long j=max(0,i-newmat.KL); j<min(newmat.N,i+newmat.KU+1); j++){
      newmat(i,j) =mat(j,i);
    }
  }
  
  return _(newmat);
}

//=============================================================================
/*! return its inverse matrix */
inline _dgematrix i(const dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.M!=mat.N){
    std::cerr << "[ERROR] i(dgbmatrix&) " << std::endl
              << "This matrix is not square and has no inverse matrix."
              << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dgbmatrix mat_cp(mat);
  dgematrix mat_inv(mat.M,mat.N);
  mat_inv.identity();
  mat_cp.dgbsv(mat_inv);
  
  return _(mat_inv);
}
