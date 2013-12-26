//=============================================================================
/*! return transposed zgematrix */
inline _zgematrix t(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.N,mat.M);
  
  for(long i=0; i<newmat.m; i++){
    for(long j=0; j<newmat.n; j++){
      newmat(i,j) =mat(j,i);
    }
  }
  
  mat.destroy();
  return _(newmat);
}

//=============================================================================
/*! return its inverse matrix */
inline _zgematrix i(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.M!=mat.N){
    std::cerr << "[ERROR] t(_zgematrix&) " << std::endl
              << "This matrix is not square and has no inverse matrix."
              << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  zgematrix mat_cp;
  mat_cp.shallow_copy(mat);
  
  zgematrix mat_inv(mat.M,mat.N);
  mat_inv.identity();
  
  mat_cp.zgesv(mat_inv);
  
  return _(mat_inv);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! return its conjugate matrix */
inline _zgematrix conj(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.M; i++){ for(long j=0; j<mat.N; j++){
    mat(i,j) =std::conj(mat(i,j));
  }}
  
  return mat;
}

//=============================================================================
/*! return its conjugate transposed matrix */
inline _zgematrix conjt(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.N,mat.M);
  for(long i=0; i<newmat.m; i++){
    for(long j=0; j<newmat.n; j++){
      newmat(i,j) =std::conj(mat(j,i));
    }
  }
  
  mat.destroy();
  return _(newmat);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! search the index of element having the largest absolute value
  in 0-based numbering system */
inline void idamax(long& i, long& j, const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(long&, long&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long index( izamax_(mat.M*mat.N, mat.Array, 1) -1 );
  i =index%mat.M;
  j =index/mat.M;
  
  mat.destroy();
}

//=============================================================================
/*! return its largest absolute value */
inline std::complex<double> damax(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> val( mat.Array[izamax_(mat.M*mat.N, mat.Array, 1) -1] );
  
  mat.destroy();
  return val;
}
