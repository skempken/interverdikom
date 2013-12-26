//=============================================================================
/*! return transposed zgbmatrix */
inline _zgbmatrix t(const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(mat.N, mat.M, mat.KU, mat.KL);
  for(long i=0; i<newmat.M; i++){
    for(long j=max(0,i-newmat.KL); j<min(newmat.N,i+newmat.KU+1); j++){
      newmat(i,j) =mat(j,i);
    }
  }
  
  return _(newmat);
}

//=============================================================================
/*! return its inverse matrix */
inline _zgematrix i(const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.M!=mat.N){
    std::cerr << "[ERROR] i(zgbmatrix&) " << std::endl
              << "This matrix is not square and has no inverse matrix."
              << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgbmatrix mat_cp(mat);
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
inline _zgbmatrix conj(const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const zgbmatrix& mat)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(mat.M, mat.N, mat.KL, mat.KU);
  for(long i=0; i<mat.M; i++){
    for(long j=max(0,i-mat.KL); j<min(mat.N,i+mat.KU+1); j++){
      newmat(i,j) =std::conj(mat(i,j));
    }
  }
  return _(newmat);
}

//=============================================================================
/*! return its conjugate transposed zgbmatrix */
inline _zgbmatrix conjt(const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(mat.N, mat.M, mat.KU, mat.KL);
  for(long i=0; i<newmat.m; i++){
    for(long j=max(0,i-newmat.kl); j<min(newmat.n,i+newmat.ku+1); j++){
      newmat(i,j) =std::conj(mat(j,i));
    }
  }
  return _(newmat);
}
