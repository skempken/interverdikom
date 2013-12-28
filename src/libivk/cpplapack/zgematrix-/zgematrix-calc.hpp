//=============================================================================
/*! return transposed zgematrix */
inline _zgematrix t(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.N,mat.M);
  
  for(long i=0; i<newmat.M; i++){ for(long j=0; j<newmat.N; j++){
    newmat(i,j) =mat(j,i);
  }}
  
  return _(newmat);
}

//=============================================================================
/*! return its inverse matrix */
inline _zgematrix i(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.M!=mat.N){
    std::cerr << "[ERROR] i(zgematrix&) " << std::endl
              << "This matrix is not square and has no inverse matrix."
              << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zgematrix mat_cp(mat), mat_inv(mat.M,mat.N);
  mat_inv.identity();
  mat_cp.zgesv(mat_inv);
  
  return _(mat_inv);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! return its conjugate matrix */
inline _zgematrix conj(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.M,mat.N);
  for(long i=0; i<mat.M; i++){ for(long j=0; j<mat.N; j++){
    newmat(i,j) =std::conj(mat(i,j));
  }}
  
  return _(newmat);
}

//=============================================================================
/*! return its conjugate transposed matrix */
inline _zgematrix conjt(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat.N,mat.M);
  for(long i=0; i<newmat.M; i++){ for(long j=0; j<newmat.N; j++){
    newmat(i,j) =std::conj(mat(j,i));
  }}
  
  return _(newmat);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! search the index of element having the largest absolute value
  in 0-based numbering system */
inline void idamax(long& i, long& j, const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(long&, long&, const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long index( izamax_(mat.M*mat.N, mat.Array, 1) -1 );
  i =index%mat.M;
  j =index/mat.M;
}

//=============================================================================
/*! return its largest absolute value */
inline std::complex<double> damax(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat.Array[izamax_(mat.M*mat.N, mat.Array, 1) -1];
}
