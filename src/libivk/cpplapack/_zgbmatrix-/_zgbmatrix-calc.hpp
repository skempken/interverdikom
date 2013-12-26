//=============================================================================
/*! return its transposed zgbmatrix */
inline _zgbmatrix t(const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(mat.N, mat.M, mat.KU, mat.KL);
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
inline _zgematrix i(const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.M!=mat.N){
    std::cerr << "[ERROR] i(_zgbmatrix&) " << std::endl
              << "This matrix is not square and has no inverse matrix."
              << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgbmatrix mat_cp;
  mat_cp.shallow_copy(mat);
  
  zgematrix mat_inv(mat.M,mat.N);
  mat_inv.identity();
  
  mat_cp.zgbsv(mat_inv);
  
  return _(mat_inv);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! return its conjugate matrix */
inline _zgbmatrix conj(const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.M; i++){
    for(long j=max(0,i-mat.KL); j<min(mat.N,i+mat.KU+1); j++){
      mat(i,j) =std::conj(mat(i,j));
    }
  }
  
  return mat;
}

//=============================================================================
/*! return its conjugate transposed zgbmatrix */
inline _zgbmatrix conjt(const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(mat.N, mat.M, mat.KU, mat.KL);
  for(long i=0; i<newmat.m; i++){
    for(long j=max(0,i-newmat.kl); j<min(newmat.n,i+newmat.ku+1); j++){
      newmat(i,j) =std::conj(mat(j,i));
    }
  }
  
  mat.destroy();
  return _(newmat);
}
