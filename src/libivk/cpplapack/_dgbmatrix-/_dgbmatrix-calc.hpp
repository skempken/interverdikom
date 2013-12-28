//=============================================================================
/*! return its transposed dgbmatrix */
inline _dgbmatrix t(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgbmatrix newmat(mat.N, mat.M, mat.KU, mat.KL);
  for(long i=0; i<newmat.m; i++){
    for(long j=max(0,i-newmat.kl); j<min(newmat.n,i+newmat.ku+1); j++){
      newmat(i,j) =mat(j,i);
    }
  }
  
  mat.destroy();
  return _(newmat);
}

//=============================================================================
/*! return its inverse matrix */
inline _dgematrix i(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.M!=mat.N){
    std::cerr << "[ERROR] i(_dgbmatrix&) " << std::endl
              << "This matrix is not square and has no inverse matrix."
              << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  dgbmatrix mat_cp;
  mat_cp.shallow_copy(mat);
  
  dgematrix mat_inv(mat.M,mat.N);
  mat_inv.identity();
  
  mat_cp.dgbsv(mat_inv);

  return _(mat_inv);
}
