//=============================================================================
/*! return transposed zgematrix */
inline _zhematrix t(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zhematrix newmat(mat.N);
  for(long i=0; i<newmat.N; i++){ for(long j=0; j<=i; j++){
    newmat(i,j) =mat(j,i);
  }}
  
  return _(newmat);
}

//=============================================================================
/*! return its inverse matrix */
inline _zgematrix i(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zhematrix mat_cp(mat);
  zgematrix mat_inv(mat.N,mat.N);
  mat_inv.identity();
  mat_cp.zhesv(mat_inv);
  
  return _(mat_inv);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! return its conjugate matrix */
inline _zhematrix conj(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zhematrix newmat(mat.N);
  for(long i=0; i<mat.N; i++){ for(long j=0; j<=i; j++){
    newmat(i,j) =std::conj(mat(i,j));
  }}
  
  return _(newmat);
}

//=============================================================================
/*! return its conjugate transposed matrix */
inline _zhematrix conjt(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "[WARNING] t(const zhematrix&)" << std::endl
            << "This function call has no effect "
            << "since the matrix is symmetric." << std::endl;
#endif//CPPL_DEBUG
  
  zhematrix newmat(mat);
  return _(newmat);
}
