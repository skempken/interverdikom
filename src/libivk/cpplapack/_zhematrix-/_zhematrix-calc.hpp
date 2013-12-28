//=============================================================================
/*! return transposed _zhematrix */
inline _zhematrix t(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "[WARNING] t(const zhematrix&)" << std::endl
            << "This function call has no effect since the matrix is symmetric." 
            << std::endl;
#endif//CPPL_DEBUG
  
  return mat;
}

//=============================================================================
/*! return its inverse matrix */
inline _zgematrix i(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] i(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zhematrix mat_cp;
  mat_cp.shallow_copy(mat);
  
  zgematrix mat_inv(mat.N,mat.N);
  mat_inv.identity();
  
  mat_cp.zhesv(mat_inv);
  
  return _(mat_inv);
}
