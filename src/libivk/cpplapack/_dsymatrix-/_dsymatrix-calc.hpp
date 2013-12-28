//=============================================================================
/*! return transposed _dsymatrix */
inline _dsymatrix t(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "[WARNING] t(const dsymatrix&)" << std::endl
            << "This function call has no effect since the matrix is symmetric." 
            << std::endl;
#endif//CPPL_DEBUG
  
  return mat;
}

//=============================================================================
/*! return its inverse matrix */
inline _dgematrix i(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dsymatrix mat_cp;
  mat_cp.shallow_copy(mat);
  
  dgematrix mat_inv(mat.N,mat.N);
  mat_inv.identity();
  
  mat_cp.dsysv(mat_inv);
  
  return _(mat_inv);
}
