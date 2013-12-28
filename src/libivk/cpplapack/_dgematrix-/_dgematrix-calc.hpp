//=============================================================================
/*! return transposed dgematrix */
inline _dgematrix t(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgematrix newmat(mat.N,mat.M);
  
  for(long i=0; i<newmat.m; i++){ for(long j=0; j<newmat.n; j++){
    newmat(i,j) =mat(j,i);
  }}
  
  mat.destroy();
  return _(newmat);
}

//=============================================================================
/*! return its inverse matrix */
inline _dgematrix i(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.M!=mat.N){
    std::cerr << "[ERROR] i(_dgematrix&) " << std::endl
              << "This matrix is not square and has no inverse matrix."
              << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  dgematrix mat_cp;
  mat_cp.shallow_copy(mat);
  
  dgematrix mat_inv(mat.M,mat.N);
  mat_inv.identity();
  mat_cp.dgesv(mat_inv);
  
  return _(mat_inv);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! search the index of element having the largest absolute value
  in 0-based numbering system */
inline void idamax(long& i, long& j, const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(long&, long&, const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long index( idamax_(mat.M*mat.N, mat.Array, 1) -1 );
  i =index%mat.M;
  j =index/mat.M;
  
  mat.destroy();
}

//=============================================================================
/*! return its largest absolute value */
inline double damax(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double val( mat.Array[idamax_(mat.M*mat.N, mat.Array, 1) -1] );
  
  mat.destroy();
  return val;
}
